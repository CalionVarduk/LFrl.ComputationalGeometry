#ifndef __LFRL_COMMON_STORE_GUARD__
#define __LFRL_COMMON_STORE_GUARD__

#include <unordered_map>
#include <memory>
#include <typeindex>
#include <vector>
#include "../utils/typedefs.h"

BEGIN_LFRLCOMMON_NAMESPACE

class Store final
{
	Store(Store const&) = delete;

public:
	enum struct ActionResult
	{
		OK = 0,
		NOT_FOUND = 1,
		ALREADY_EXISTS = 2,
		INVALID_TYPE = 3,
		UNSUPPORTED_NULL = 4
	};

	Store() = default;
	Store(Store&&) = default;
	Store& operator=(Store const&) = delete;
	Store& operator=(Store&&) = default;

	~Store() { Clear(); }

	u32 GetSize() const noexcept { return (u32)_map.size(); }
	bool IsEmpty() const noexcept { return GetSize() == 0; }

	bool Contains(uPtr address) const;
	bool Contains(void const* obj) const { return Contains((uPtr)obj); }

	std::type_index GetType(uPtr address) const;
	std::type_index GetType(void const* obj) const { return GetType((uPtr)obj); }
	void* Get(uPtr address) const;

	template <class T>
	std::pair<ActionResult, T*> Get(uPtr address) const;

	ActionResult Delete(uPtr address);
	ActionResult Delete(void const* obj) { return Delete((uPtr)obj); }
	void Clear();

	template <class T>
	ActionResult Add(T* obj);

	template <class T, class... TArgs>
	T* Create(TArgs&&... args);

private:
	std::unordered_map<uPtr, std::pair<std::type_index, std::shared_ptr<void>>> _map;
};

template <class T>
std::pair<Store::ActionResult, T*> Store::Get(uPtr address) const
{
	if (address == 0)
		return std::make_pair(ActionResult::UNSUPPORTED_NULL, (T*)nullptr);

	auto entry = _map.find(address);
	if (entry == _map.end())
		return std::make_pair(ActionResult::NOT_FOUND, (T*)nullptr);

	auto type = entry->second.first;
	if (type != std::type_index(typeid(T)))
		return std::make_pair(ActionResult::INVALID_TYPE, (T*)nullptr);

	return std::make_pair(ActionResult::OK, static_cast<T*>(entry->second.second.get()));
}

template <class T>
Store::ActionResult Store::Add(T* obj)
{
	if (obj == nullptr)
		return ActionResult::UNSUPPORTED_NULL;

	if (Contains(obj))
		return ActionResult::ALREADY_EXISTS;

	_map.insert({
		(uPtr)obj,
		std::make_pair(std::type_index(typeid(T)), std::shared_ptr<void>(obj))
	});
	return ActionResult::OK;
}

template <class T, class... TArgs>
T* Store::Create(TArgs&&... args)
{
	auto obj = new T(std::forward<TArgs>(args)...);
	_map.insert({
		(uPtr)obj,
		std::make_pair(std::type_index(typeid(T)), std::shared_ptr<void>(obj))
	});
	return obj;
}

END_LFRLCOMMON_NAMESPACE

#endif
