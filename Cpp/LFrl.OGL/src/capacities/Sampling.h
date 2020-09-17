#ifndef __LFRL_OGL_CAPACITIES_SAMPLING_GUARD__
#define __LFRL_OGL_CAPACITIES_SAMPLING_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Sampling
{
	namespace Multi
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;
	}

	namespace Alpha
	{
		namespace ToCoverage
		{
			bool IsEnabled() noexcept;
			void Enable() noexcept;
			void Disable() noexcept;
		}

		namespace ToOne
		{
			bool IsEnabled() noexcept;
			void Enable() noexcept;
			void Disable() noexcept;
		}
	}

	namespace Coverage
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		GLint GetSize() noexcept;
		GLfloat GetValue() noexcept;
		bool IsValueInverted() noexcept;
		void SetValue(GLfloat value) noexcept;
		void SetValueInverted(GLfloat value) noexcept;
	}

	namespace Mask
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		GLbitfield GetMasks() noexcept;
		void SetMasks(GLbitfield value) noexcept;
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
