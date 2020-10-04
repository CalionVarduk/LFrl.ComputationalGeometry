#include "Container.h"

BEGIN_LFRL_COMMON_NAMESPACE

Container::Container() noexcept
	: _map(), _keyedMap()
{}

Container::Container(Container&& other)
	: _map(), _keyedMap()
{
	std::swap(_map, other._map);
	std::swap(_keyedMap, other._keyedMap);
}

Container& Container::operator= (Container&& other)
{
	if (this != &other)
	{
		std::swap(_map, other._map);
		std::swap(_keyedMap, other._keyedMap);
	}
	return *this;
}

Container::~Container() noexcept
{
	_map.clear();
	_keyedMap.clear();
}

bool Container::Contains(std::type_index type) const
{
	return _map.find(type) != _map.end();
}

bool Container::ContainsKeyed(std::type_index type, u32 key) const
{
	return ContainsKeyed(std::make_pair(type, key));
}

bool Container::ContainsKeyed(std::pair<std::type_index, u32> key) const
{
	return _keyedMap.find(key) != _keyedMap.end();
}

void* Container::Get(std::type_index type) const
{
	auto it = _map.find(type);
	return it == _map.end() ? nullptr : it->second.get();
}

void* Container::GetKeyed(std::type_index type, u32 key) const
{
	return GetKeyed(std::make_pair(type, key));
}

void* Container::GetKeyed(std::pair<std::type_index, u32> key) const
{
	auto it = _keyedMap.find(key);
	return it == _keyedMap.end() ? nullptr : it->second.get();
}

END_LFRL_COMMON_NAMESPACE
