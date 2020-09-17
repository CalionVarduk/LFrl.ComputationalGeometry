#ifndef __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__
#define __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace FaceCulling
{
	bool IsEnabled() noexcept;
	void Enable() noexcept;
	void Disable() noexcept;

	namespace Front
	{
		enum struct Type
		{
			 CW = GL_CW,
			 CCW = GL_CCW
		};

		Type Get() noexcept;
		void Set(Type type) noexcept;
		void SetCw() noexcept { Set(Type::CW); }
		void SetCcw() noexcept { Set(Type::CCW); }
	}

	namespace Cull
	{
		enum struct Type
		{
			FRONT = GL_FRONT,
			BACK = GL_BACK,
			ALL = GL_FRONT_AND_BACK
		};

		Type Get() noexcept;
		void Set(Type type) noexcept;
		void SetFront() noexcept { Set(Type::FRONT); }
		void SetBack() noexcept { Set(Type::BACK); }
		void SetAll() noexcept { Set(Type::ALL); }
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
