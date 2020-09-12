#ifndef __LFRL_COMMON_HASH_GUARD__
#define __LFRL_COMMON_HASH_GUARD__

#include <functional>
#include "../internal/namespace_macros.h"

namespace std {
	template <class T1, class T2>
	struct hash<std::pair<T1, T2>> {
		std::size_t operator()(std::pair<T1, T2> const& obj) const {
			return (std::hash<T1>()(obj.first) * 16777619) ^ std::hash<T2>()(obj.second);
		}
	};
}

BEGIN_LFRLCOMMON_NAMESPACE

template <class T>
struct ptr_hash {
	std::size_t operator()(T const* obj) const {
		return obj == nullptr ? 0 : std::hash<T>()(*obj);
	}
};

END_LFRLCOMMON_NAMESPACE

#endif
