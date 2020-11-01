#ifndef __LFRL_OGL_OBJECT_STORE_BASE_GUARD__
#define __LFRL_OGL_OBJECT_STORE_BASE_GUARD__

#include <unordered_map>
#include "../primitives/ShaderObject.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace __detail
{
	template <class Store, class T>
	class object_store_base
	{
		// TODO: look into why this isn't working
		//static_assert(std::is_base_of<object_store_base<Store, T>, Store>::value, "object_store_base<Store, T>: Store must inherit from object_store_base<Store, T>.");

		object_store_base(object_store_base<Store, T> const&) = delete;
		object_store_base<Store, T>& operator=(object_store_base<Store, T> const&) = delete;

	public:
		typedef T object_type;

		~object_store_base() { Clear(); }

		LFRL::sz Size() const noexcept { return _map.size(); }
		bool IsEmpty() const noexcept { return Size() == 0; }
		bool Contains(GLuint id) const { return Get(id) != nullptr; }
		bool Contains(std::string const& name) const { return Get(name) != nullptr; }
		T* Get(GLuint id) const;
		T* Get(std::string const& name) const;

		std::string GetName(GLuint id) const;
		std::string GetName(T const& obj) const { return GetName(Store::GetId(&obj)); }

		bool Add(std::string const& name, T* obj);
		bool Delete(GLuint id);
		bool Delete(std::string const& name);

		void Clear();

		T* operator[] (GLuint id) const { return Get(id); }
		T* operator[] (std::string const& name) const { return Get(name); }

	protected:
		object_store_base();
		object_store_base(object_store_base<Store, T>&&);
		object_store_base<Store, T>& operator=(object_store_base<Store, T>&&);

		bool Insert(std::string const& name, T* obj);

	private:
		struct _named_object final
		{
			T* const object;
			std::string const* const name;
		};

		std::unordered_map<GLuint, _named_object> _map;
		std::unordered_map<std::string, T*> _nameIndex;
	};

	template <class Store, class T>
	T* object_store_base<Store, T>::Get(GLuint id) const
	{
		auto entry = _map.find(id);
		return entry == _map.end() ? nullptr : entry->second.object;
	}

	template <class Store, class T>
	T* object_store_base<Store, T>::Get(std::string const& name) const
	{
		auto entry = _nameIndex.find(name);
		return entry == _nameIndex.end() ? nullptr : entry->second;
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Add(std::string const& name, T* obj)
	{
		if (obj == nullptr)
			return false;

		if (Store::GetState(obj) != ObjectState::READY)
			return false;

		return Insert(name, obj);
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Delete(GLuint id)
	{
		auto entry = _map.find(id);
		if (entry == _map.end())
			return false;

		delete entry->second.object;
		_nameIndex.erase(*entry->second.name);
		_map.erase(id);
		return true;
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Delete(std::string const& name)
	{
		auto entry = _nameIndex.find(name);
		if (entry == _nameIndex.end())
			return false;

		auto id = Store::GetId(entry->second);
		delete entry->second;
		_nameIndex.erase(name);
		_map.erase(id);
		return true;
	}

	template <class Store, class T>
	void object_store_base<Store, T>::Clear()
	{
		for (auto entry : _map)
			delete entry.second.object;

		_nameIndex.clear();
		_map.clear();
	}

	template <class Store, class T>
	object_store_base<Store, T>::object_store_base()
		: _map(), _nameIndex()
	{}

	template <class Store, class T>
	object_store_base<Store, T>::object_store_base(object_store_base<Store, T>&& other)
		: _map(), _nameIndex()
	{
		std::swap(_map, other._map);
		std::swap(_nameIndex, other._nameIndex);
	}

	template <class Store, class T>
	object_store_base<Store, T>& object_store_base<Store, T>::operator= (object_store_base<Store, T>&& other)
	{
		if (this != &other)
		{
			std::swap(_map, other._map);
			std::swap(_nameIndex, other._nameIndex);
		}
		return *this;
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Insert(std::string const& name, T* obj)
	{
		auto id = Store::GetId(obj);
		if (_map.find(id) != _map.end())
			return false;

		auto indexResult = _nameIndex.insert({ name, obj });
		if (!indexResult.second)
			return false;

		_map.insert({ id, { obj, &indexResult.first->first } });
		return true;
	}
}

END_LFRL_OGL_NAMESPACE

#endif
