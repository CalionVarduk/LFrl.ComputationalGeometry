#ifndef __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__
#define __LFRL_OGL_CAPACITIES_FACE_CULLING_GUARD__

#include "macros.h"
#include "FaceType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace FaceCulling
{
	LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_CULL_FACE, false);

	namespace FrontOrientation
	{
		enum struct Type
		{
			 CW = GL_CW,
			 CCW = GL_CCW
		};

		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(, Type, GL_FRONT_FACE)

		void Set(Type type) noexcept;
		void SetCw() noexcept { Set(Type::CW); }
		void SetCcw() noexcept { Set(Type::CCW); }

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			Type type;);
	}

	namespace Cull
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(, FaceType, GL_CULL_FACE_MODE)

		void Set(FaceType face) noexcept;
		void SetFront() noexcept { Set(FaceType::FRONT); }
		void SetBack() noexcept { Set(FaceType::BACK); }
		void SetAll() noexcept { Set(FaceType::ALL); }

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			FaceType type;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ToggleSnapshot toggle;
		FrontOrientation::Snapshot frontOrientation;
		Cull::Snapshot cull;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
