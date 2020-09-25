#ifndef __LFRL_OGL_CAPACITIES_SAMPLING_GUARD__
#define __LFRL_OGL_CAPACITIES_SAMPLING_GUARD__

#include "macros.h"
#include "../internal/namespace_macros.h"

#define __LFRL_OGL_SAMPLING_COVERAGE_CAPACITY_DEFAULT_DATA { 1.0f, false }
#define __LFRL_OGL_SAMPLING_MASK_CAPACITY_DEFAULT_VALUE std::numeric_limits<GLbitfield>::max()

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Sampling
{
	namespace Multi
	{
		LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_MULTISAMPLE, false);
	}

	namespace Alpha
	{
		namespace ToCoverage
		{
			LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_SAMPLE_ALPHA_TO_COVERAGE, false);
		}

		namespace ToOne
		{
			LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_SAMPLE_ALPHA_TO_ONE, false);
		}
	}

	namespace Coverage
	{
		struct data final
		{
			GLfloat value;
			bool isInverted;
		};

		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Size, GLint, GL_SAMPLES)

		data GetValue() noexcept;
		void SetValue(GLfloat value, bool isInverted = false) noexcept;
		inline void SetValue(data value) noexcept { SetValue(value.value, value.isInverted); }
		inline void SetValueInverted(GLfloat value) noexcept { SetValue(value, true); }

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_SAMPLE_COVERAGE, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Value, data, __LFRL_OGL_SAMPLING_COVERAGE_CAPACITY_DEFAULT_DATA, GetValue, SetValue);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			ValueSnapshot value;);
	}

	namespace Mask
	{
		GLbitfield GetMask() noexcept;
		void SetMask(GLbitfield value) noexcept;

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_SAMPLE_MASK, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Value, GLbitfield, __LFRL_OGL_SAMPLING_MASK_CAPACITY_DEFAULT_VALUE, GetMask, SetMask);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			ValueSnapshot value;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		Multi::Snapshot multi;
		Alpha::ToCoverage::Snapshot alphaToCoverage;
		Alpha::ToOne::Snapshot alphaToOne;
		Coverage::Snapshot coverage;
		Mask::Snapshot mask;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_SAMPLING_COVERAGE_CAPACITY_DEFAULT_DATA
#undef __LFRL_OGL_SAMPLING_MASK_CAPACITY_DEFAULT_VALUE

#endif
