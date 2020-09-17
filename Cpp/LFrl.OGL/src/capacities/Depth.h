#ifndef __LFRL_OGL_CAPACITIES_DEPTH_GUARD__
#define __LFRL_OGL_CAPACITIES_DEPTH_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

// TODO: add Debug (might be a struct? include getting errors), Sampling, Stencil
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
		struct data final
		{
			GLdouble zNear;
			GLdouble zFar;
		};

		data Get() noexcept;
		void Set(data value) noexcept { Set(value.zNear, value.zFar); }
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
		enum struct Type
		{
			NEVER = GL_NEVER,
			LESS_THAN = GL_LESS,
			EQUAL_TO = GL_EQUAL,
			LESS_THAN_OR_EQUAL_TO = GL_LEQUAL,
			GREATER_THAN = GL_GREATER,
			NOT_EQUAL_TO = GL_NOTEQUAL,
			GREATER_THAN_OR_EQUAL_TO = GL_GEQUAL,
			ALWAYS = GL_ALWAYS
		};

		Type Get() noexcept;
		void Set(Type type) noexcept;
		void SetNever() noexcept { Set(Type::NEVER); }
		void SetLt() noexcept { Set(Type::LESS_THAN); }
		void SetEq() noexcept { Set(Type::EQUAL_TO); }
		void SetLe() noexcept { Set(Type::LESS_THAN_OR_EQUAL_TO); }
		void SetGt() noexcept { Set(Type::GREATER_THAN); }
		void SetNe() noexcept { Set(Type::NOT_EQUAL_TO); }
		void SetGe() noexcept { Set(Type::GREATER_THAN_OR_EQUAL_TO); }
		void SetAlways() noexcept { Set(Type::ALWAYS); }
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
