#ifndef __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__
#define __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__

#include "FaceType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace FaceCulling
{
	bool IsEnabled() noexcept;
	void Enable() noexcept;
	void Disable() noexcept;

	namespace FrontOrientation
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
		FaceType Get() noexcept;
		void Set(FaceType face) noexcept;
		void SetFront() noexcept { Set(FaceType::FRONT); }
		void SetBack() noexcept { Set(FaceType::BACK); }
		void SetAll() noexcept { Set(FaceType::ALL); }
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
