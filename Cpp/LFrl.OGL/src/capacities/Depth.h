#ifndef __LFRL_OGL_CAPACITIES_DEPTH_GUARD__
#define __LFRL_OGL_CAPACITIES_DEPTH_GUARD__

#include "macros.h"
#include "FuncType.h"

#define __LFRL_OGL_DEFINE_DEPTH_READONLY_CAPACITY_SETTER(READONLY)\
if (READONLY) MakeReadonly(); \
else MakeWritable();

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Depth
{
	bool IsReadonly() noexcept;
	void MakeWritable() noexcept;
	void MakeReadonly() noexcept;

	LFRL_OGL_DEFINE_CAPACITY_GETTER_F64(ClearValue, GLdouble, GL_DEPTH_CLEAR_VALUE)

	void SetClearValue(GLdouble value) noexcept;

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Readonly, bool, false, IsReadonly, __LFRL_OGL_DEFINE_DEPTH_READONLY_CAPACITY_SETTER);
	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(ClearValue, GLdouble, 1.0, GetClearValue, SetClearValue);

	namespace Test
	{
		LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_DEPTH_TEST, false);
	}

	namespace Range
	{
		struct data final
		{
			GLdouble zNear;
			GLdouble zFar;
		};

		data Get() noexcept;
		void Set(GLdouble zNear, GLdouble zFar) noexcept;
		inline void Set(data value) noexcept { Set(value.zNear, value.zFar); }

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			data data;);
	}

	namespace Clamping
	{
		LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_DEPTH_TEST, false);
	}

	namespace Func
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(, FuncType, GL_DEPTH_FUNC)

		void Set(FuncType func) noexcept;
		inline void SetNever() noexcept { Set(FuncType::NEVER); }
		inline void SetLt() noexcept { Set(FuncType::LESS_THAN); }
		inline void SetEq() noexcept { Set(FuncType::EQUAL_TO); }
		inline void SetLe() noexcept { Set(FuncType::LESS_THAN_OR_EQUAL_TO); }
		inline void SetGt() noexcept { Set(FuncType::GREATER_THAN); }
		inline void SetNe() noexcept { Set(FuncType::NOT_EQUAL_TO); }
		inline void SetGe() noexcept { Set(FuncType::GREATER_THAN_OR_EQUAL_TO); }
		inline void SetAlways() noexcept { Set(FuncType::ALWAYS); }

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			FuncType type;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ReadonlySnapshot readonly;
		ClearValueSnapshot clearValue;
		Test::Snapshot test;
		Range::Snapshot range;
		Clamping::Snapshot clamping;
		Func::Snapshot func;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_DEFINE_DEPTH_READONLY_CAPACITY_SETTER

#endif
