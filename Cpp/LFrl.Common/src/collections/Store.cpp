#include "Store.h"

BEGIN_LFRLCOMMON_NAMESPACE

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

END_LFRLCOMMON_NAMESPACE
