#include "Store.h"

BEGIN_LFRL_NAMESPACE

Store::Store()
	: _map()
{}

Store::Store(Store&& other)
	: _map()
{
	std::swap(_map, other._map);
}

Store& Store::operator=(Store&& other)
{
	if (this != &other)
		std::swap(_map, other._map);

	return *this;
}

bool Store::Contains(uPtr address) const
{
	return _map.find(address) != _map.end();
}

std::type_index Store::GetType(uPtr address) const
{
	auto entry = _map.find(address);
	if (entry == _map.end())
		return std::type_index(typeid(void));

	return entry->second.first;
}

Store::ActionResult Store::Delete(uPtr address)
{
	if (address == 0)
		return ActionResult::UNSUPPORTED_NULL;

	if (_map.erase(address) == 0)
		return ActionResult::NOT_FOUND;

	return ActionResult::OK;
}

void Store::Clear()
{
	_map.clear();
}

END_LFRL_NAMESPACE
