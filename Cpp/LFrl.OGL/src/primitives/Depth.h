#ifndef __LFRL_OGL_DEPTH_GUARD__
#define __LFRL_OGL_DEPTH_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace Depth
{
	bool IsReadonly() noexcept;
	void MakeWritable() noexcept;
	void MakeReadonly() noexcept;

	GLdouble GetClearValue() noexcept;
	void SetClearValue(GLdouble value) noexcept;

	namespace Test
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;
	}

	namespace Range
	{
		struct value final
		{
			GLdouble zNear;
			GLdouble zFar;
		};

		value Get() noexcept;
		void Set(value val) noexcept { Set(val.zNear, val.zFar); }
		void Set(GLdouble zNear, GLdouble zFar) noexcept;
	}

	namespace Clamping
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;
	}

	namespace Func
	{
		GLenum Get() noexcept;
		void SetNever() noexcept;
		void SetLt() noexcept;
		void SetEq() noexcept;
		void SetLe() noexcept;
		void SetGt() noexcept;
		void SetNe() noexcept;
		void SetGe() noexcept;
		void SetAlways() noexcept;
	}
}

END_LFRL_OGL_NAMESPACE

#endif
