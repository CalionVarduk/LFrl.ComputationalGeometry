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

		LFRL_COMMON::sz Size() const noexcept { return _map.size(); }
		bool IsEmpty() const noexcept { return Size() == 0; }
		bool Contains(GLuint id) { return Get(id) != nullptr; }
		T* Get(GLuint id) const;

		bool Add(T* obj);
		bool Delete(GLuint id);

		void Clear();

	protected:
		object_store_base() noexcept;
		object_store_base(object_store_base<Store, T>&&) = default;
		object_store_base<Store, T>& operator=(object_store_base<Store, T>&&) = default;

		bool Insert(T* obj);

	private:
		std::unordered_map<GLuint, T*> _map;
	};

	template <class Store, class T>
	T* object_store_base<Store, T>::Get(GLuint id) const
	{
		auto entry = _map.find(id);
		return entry == _map.end() ? nullptr : entry->second;
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Add(T* obj)
	{
		if (obj == nullptr)
			return false;

		if (Store::GetState(obj) != ObjectState::READY)
			return false;

		return Insert(obj);
	}

	template <class Store, class T>
	bool object_store_base<Store, T>::Delete(GLuint id)
	{
		auto obj = Get(id);
		if (obj == nullptr)
			return false;

		delete obj;
		_map.erase(id);
		return true;
	}

	template <class Store, class T>
	void object_store_base<Store, T>::Clear()
	{
		for (auto entry : _map)
			delete entry.second;

		_map.clear();
	}

	template <class Store, class T>
	object_store_base<Store, T>::object_store_base() noexcept
		: _map()
	{}

	template <class Store, class T>
	bool object_store_base<Store, T>::Insert(T* obj)
	{
		auto result = _map.insert({ Store::GetId(obj), obj });
		return result.second;
	}
}

END_LFRL_OGL_NAMESPACE

#endif