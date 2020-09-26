#ifndef __LFRL_CG_API_SERVICES_GUARD__
#define __LFRL_CG_API_SERVICES_GUARD__

#include "internal/namespace_macros.h"
#include "LFrl.Common/src/collections/Store.h"
#include "LFrl.Common/src/Container.h"

BEGIN_LFRL_CG_API_NAMESPACE

namespace Services
{
	inline Common::Store* GetObjectStore()
	{
		static Common::Store store;
		return &store;
	}

	inline Common::Container* GetContainer()
	{
		static Common::Container container;
		return &container;
	}
}

END_LFRL_CG_API_NAMESPACE

#define sStore LFRL_CG_API::Services::GetObjectStore()
#define sServices LFRL_CG_API::Services::GetDynamic()

#endif
