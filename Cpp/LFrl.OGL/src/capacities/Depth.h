#ifndef __LFRL_OGL_CAPACITIES_DEPTH_GUARD__
#define __LFRL_OGL_CAPACITIES_DEPTH_GUARD__

#include "FuncType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

// TODO: add Debug (might be a struct? include getting errors)
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
		FuncType Get() noexcept;
		void Set(FuncType func) noexcept;
		void SetNever() noexcept { Set(FuncType::NEVER); }
		void SetLt() noexcept { Set(FuncType::LESS_THAN); }
		void SetEq() noexcept { Set(FuncType::EQUAL_TO); }
		void SetLe() noexcept { Set(FuncType::LESS_THAN_OR_EQUAL_TO); }
		void SetGt() noexcept { Set(FuncType::GREATER_THAN); }
		void SetNe() noexcept { Set(FuncType::NOT_EQUAL_TO); }
		void SetGe() noexcept { Set(FuncType::GREATER_THAN_OR_EQUAL_TO); }
		void SetAlways() noexcept { Set(FuncType::ALWAYS); }
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
