#ifndef __LFRL_COMMON_CONTAINER_GUARD__
#define __LFRL_COMMON_CONTAINER_GUARD__

#include <typeindex>
#include <memory>
#include <unordered_map>
#include "utils/requires.h"
#include "utils/typedefs.h"
#include "utils/hash.h"

BEGIN_LFRL_NAMESPACE

class Container final
{
	Container(Container const&) = delete;
	Container& operator= (Container const&) = delete;

public:
	Container() noexcept;
	Container(Container&&);
	Container& operator= (Container&&);
	~Container() noexcept;

	template <class T>
	bool Contains() const;
	bool Contains(std::type_index type) const;

	template <class T>
	bool ContainsKeyed(u32 key) const;
	bool ContainsKeyed(std::type_index type, u32 key) const;
	bool ContainsKeyed(std::pair<std::type_index, u32> key) const;

	template <class T>
	T* Get() const;
	void* Get(std::type_index type) const;

	template <class T>
	T* GetKeyed(u32 key) const;
	void* GetKeyed(std::type_index type, u32 key) const;
	void* GetKeyed(std::pair<std::type_index, u32> key) const;

	template <class T>
	bool Add(T* service);

	template <class T, class U, requires<std::is_base_of<T, U>::value> = 0>
	bool AddAs(U* service);

	template <class T>
	bool AddKeyed(u32 key, T* service);

	template <class T, class U, requires<std::is_base_of<T, U>::value> = 0>
	bool AddKeyedAs(u32 key, U* service);

private:
	std::unordered_map<std::type_index, std::shared_ptr<void>> _map;
	std::unordered_map<std::pair<std::type_index, u32>, std::shared_ptr<void>> _keyedMap;
};

template <class T>
bool Container::Contains() const
{
	return Contains(std::type_index(typeid(T)));
}

template <class T>
bool Container::ContainsKeyed(u32 key) const
{
	return ContainsKeyed(std::type_index(typeid(T)), key);
}

template <class T>
T* Container::Get() const
{
	return static_cast<T*>(Get(std::type_index(typeid(T))));
}

template <class T>
T* Container::GetKeyed(u32 key) const
{
	return static_cast<T*>(GetKeyed(std::type_index(typeid(T)), key));
}

template <class T>
bool Container::Add(T* service)
{
	return AddAs<T>(service);
}

template <class T, class U, requires<std::is_base_of<T, U>::value>>
bool Container::AddAs(U* service)
{
	return service != nullptr ?
		_map.insert({ std::type_index(typeid(T)), std::shared_ptr<void>(service) }).second :
		false;
}

template <class T>
bool Container::AddKeyed(u32 key, T* service)
{
	return AddKeyedAs<T>(key, service);
}

template <class T, class U, requires<std::is_base_of<T, U>::value>>
bool Container::AddKeyedAs(u32 key, U* service)
{
	return service != nullptr ?
		_keyedMap.insert({ std::make_pair(std::type_index(typeid(T)), key), std::shared_ptr<void>(service) }).second :
		false;
}

END_LFRL_NAMESPACE

#endif
