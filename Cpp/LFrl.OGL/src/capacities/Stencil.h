#ifndef __LFRL_OGL_CAPACITIES_STENCIL_GUARD__
#define __LFRL_OGL_CAPACITIES_STENCIL_GUARD__

#include "macros.h"
#include "FaceType.h"
#include "FuncType.h"

#define __LFRL_OGL_STENCIL_FUNC_CAPACITY_DEFAULT_VALUE { FuncType::ALWAYS, 0, std::numeric_limits<GLuint>::max() }
#define __LFRL_OGL_STENCIL_OP_CAPACITY_DEFAULT_VALUE { Type::KEEP, Type::KEEP, Type::KEEP }
#define __LFRL_OGL_STENCIL_MASK_CAPACITY_DEFAULT_VALUE std::numeric_limits<GLuint>::max()

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Stencil
{
	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(ClearValue, GLint, GL_STENCIL_CLEAR_VALUE)

	void SetClearValue(GLint value) noexcept;

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(ClearValue, GLint, 0, GetClearValue, SetClearValue);

	namespace Test
	{
		LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_STENCIL_TEST, false);
	}

	namespace Func
	{
		struct data final
		{
			FuncType func;
			GLint ref;
			GLuint valueMask;
		};

		data GetFront() noexcept;
		data GetBack() noexcept;

		void Set(FuncType func, GLint ref, GLuint mask) noexcept;
		inline void Set(data value) noexcept { Set(value.func, value.ref, value.valueMask); }
		inline void SetNever(GLint ref, GLuint mask) noexcept { Set(FuncType::NEVER, ref, mask); }
		inline void SetLt(GLint ref, GLuint mask) noexcept { Set(FuncType::LESS_THAN, ref, mask); }
		inline void SetEq(GLint ref, GLuint mask) noexcept { Set(FuncType::EQUAL_TO, ref, mask); }
		inline void SetLe(GLint ref, GLuint mask) noexcept { Set(FuncType::LESS_THAN_OR_EQUAL_TO, ref, mask); }
		inline void SetGt(GLint ref, GLuint mask) noexcept { Set(FuncType::GREATER_THAN, ref, mask); }
		inline void SetNe(GLint ref, GLuint mask) noexcept { Set(FuncType::NOT_EQUAL_TO, ref, mask); }
		inline void SetGe(GLint ref, GLuint mask) noexcept { Set(FuncType::GREATER_THAN_OR_EQUAL_TO, ref, mask); }
		inline void SetAlways(GLint ref, GLuint mask) noexcept { Set(FuncType::ALWAYS, ref, mask); }

		void SetSeparate(FaceType face, FuncType func, GLint ref, GLuint mask) noexcept;
		inline void SetSeparate(FaceType face, data value) noexcept { SetSeparate(face, value.func, value.ref, value.valueMask); }
		inline void SetSeparateNever(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::NEVER, ref, mask); }
		inline void SetSeparateLt(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::LESS_THAN, ref, mask); }
		inline void SetSeparateEq(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::EQUAL_TO, ref, mask); }
		inline void SetSeparateLe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::LESS_THAN_OR_EQUAL_TO, ref, mask); }
		inline void SetSeparateGt(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::GREATER_THAN, ref, mask); }
		inline void SetSeparateNe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::NOT_EQUAL_TO, ref, mask); }
		inline void SetSeparateGe(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::GREATER_THAN_OR_EQUAL_TO, ref, mask); }
		inline void SetSeparateAlways(FaceType face, GLint ref, GLuint mask) noexcept { SetSeparate(face, FuncType::ALWAYS, ref, mask); }

		inline void SetFront(data value) noexcept { SetSeparate(FaceType::FRONT, value); }
		inline void SetBack(data value) noexcept { SetSeparate(FaceType::BACK, value); }

		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Front, data, __LFRL_OGL_STENCIL_FUNC_CAPACITY_DEFAULT_VALUE, GetFront, SetFront);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Back, data, __LFRL_OGL_STENCIL_FUNC_CAPACITY_DEFAULT_VALUE, GetBack, SetBack);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			FrontSnapshot front;
			BackSnapshot back;);
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

		struct data final
		{
			Type stencilFail;
			Type depthFail;
			Type pass;
		};

		data GetFront() noexcept;
		data GetBack() noexcept;

		void Set(Type sfail, Type dpfail, Type dppass) noexcept;
		inline void Set(data value) noexcept { Set(value.stencilFail, value.depthFail, value.pass); }

		void SetSeparate(FaceType face, Type sfail, Type dpfail, Type dppass) noexcept;
		inline void SetSeparate(FaceType face, data value) noexcept { SetSeparate(face, value.stencilFail, value.depthFail, value.pass); }

		inline void SetFront(data value) noexcept { SetSeparate(FaceType::FRONT, value); }
		inline void SetBack(data value) noexcept { SetSeparate(FaceType::BACK, value); }

		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Front, data, __LFRL_OGL_STENCIL_OP_CAPACITY_DEFAULT_VALUE, GetFront, SetFront);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Back, data, __LFRL_OGL_STENCIL_OP_CAPACITY_DEFAULT_VALUE, GetBack, SetBack);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			FrontSnapshot front;
			BackSnapshot back;);
	}

	namespace Mask
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Front, GLuint, GL_STENCIL_WRITEMASK)
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Back, GLuint, GL_STENCIL_BACK_WRITEMASK)

		void Set(GLuint mask) noexcept;
		void SetSeparate(FaceType face, GLuint mask) noexcept;
		inline void SetFront(GLuint mask) noexcept { SetSeparate(FaceType::FRONT, mask); }
		inline void SetBack(GLuint mask) noexcept { SetSeparate(FaceType::BACK, mask); }

		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Front, GLuint, __LFRL_OGL_STENCIL_MASK_CAPACITY_DEFAULT_VALUE, GetFront, SetFront);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Back, GLuint, __LFRL_OGL_STENCIL_MASK_CAPACITY_DEFAULT_VALUE, GetBack, SetBack);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			FrontSnapshot front;
			BackSnapshot back;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ClearValueSnapshot clearValue;
		Test::Snapshot test;
		Func::Snapshot func;
		Op::Snapshot op;
		Mask::Snapshot mask;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_STENCIL_FUNC_CAPACITY_DEFAULT_VALUE
#undef __LFRL_OGL_STENCIL_OP_CAPACITY_DEFAULT_VALUE
#undef __LFRL_OGL_STENCIL_MASK_CAPACITY_DEFAULT_VALUE

#endif
