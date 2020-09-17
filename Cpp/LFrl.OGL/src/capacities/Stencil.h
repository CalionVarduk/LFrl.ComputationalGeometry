#ifndef __LFRL_OGL_CAPACITIES_STENCIL_GUARD__
#define __LFRL_OGL_CAPACITIES_STENCIL_GUARD__

#include "FaceType.h"
#include "FuncType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Stencil
{
	GLint GetClearValue() noexcept;
	void SetClearValue(GLint value) noexcept;

	namespace Test
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;
	}

	namespace Func
	{
		FuncType GetFront() noexcept;
		GLint GetFrontRef() noexcept;
		GLuint GetFrontValueMask() noexcept;
		FuncType GetBack() noexcept;
		GLint GetBackRef() noexcept;
		GLuint GetBackValueMask() noexcept;

		void Set(FuncType func, GLint ref, GLuint mask) noexcept;
		void SetNever(GLint ref, GLuint mask) noexcept { Set(FuncType::NEVER, ref, mask); }
		void SetLt(GLint ref, GLuint mask) noexcept { Set(FuncType::LESS_THAN, ref, mask); }
		void SetEq(GLint ref, GLuint mask) noexcept { Set(FuncType::EQUAL_TO, ref, mask); }
		void SetLe(GLint ref, GLuint mask) noexcept { Set(FuncType::LESS_THAN_OR_EQUAL_TO, ref, mask); }
		void SetGt(GLint ref, GLuint mask) noexcept { Set(FuncType::GREATER_THAN, ref, mask); }
		void SetNe(GLint ref, GLuint mask) noexcept { Set(FuncType::NOT_EQUAL_TO, ref, mask); }
		void SetGe(GLint ref, GLuint mask) noexcept { Set(FuncType::GREATER_THAN_OR_EQUAL_TO, ref, mask); }
		void SetAlways(GLint ref, GLuint mask) noexcept { Set(FuncType::ALWAYS, ref, mask); }

		void SetSeparate(FaceType face, FuncType func, GLint ref, GLuint mask) noexcept;
		void SetSeparateNever(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::NEVER, ref, mask); }
		void SetSeparateLt(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::LESS_THAN, ref, mask); }
		void SetSeparateEq(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::EQUAL_TO, ref, mask); }
		void SetSeparateLe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::LESS_THAN_OR_EQUAL_TO, ref, mask); }
		void SetSeparateGt(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::GREATER_THAN, ref, mask); }
		void SetSeparateNe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::NOT_EQUAL_TO, ref, mask); }
		void SetSeparateGe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::GREATER_THAN_OR_EQUAL_TO, ref, mask); }
		void SetSeparateAlways(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::ALWAYS, ref, mask); }
	}

	namespace Op
	{
		enum struct Type
		{
			KEEP = GL_KEEP,
			ZERO = GL_ZERO,
			REPLACE = GL_REPLACE,
			INCR = GL_INCR,
			INCR_WRAP = GL_INCR_WRAP,
			DECR = GL_DECR,
			DECR_WRAP = GL_DECR_WRAP,
			INVERT = GL_INVERT
		};

		Type GetFrontStencilFail() noexcept;
		Type GetFrontDepthFail() noexcept;
		Type GetFrontPass() noexcept;
		Type GetBackStencilFail() noexcept;
		Type GetBackDepthFail() noexcept;
		Type GetBackPass() noexcept;

		void Set(Type sfail, Type dpfail, Type dppass) noexcept;
		void SetSeparate(FaceType face, Type sfail, Type dpfail, Type dppass) noexcept;
	}

	namespace Mask
	{
		GLuint GetFront() noexcept;
		GLuint GetBack() noexcept;

		void Set(GLuint mask) noexcept;
		void SetSeparate(FaceType face, GLuint mask) noexcept;
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
