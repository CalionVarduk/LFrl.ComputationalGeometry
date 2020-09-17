#ifndef __LFRL_OGL_CAPACITIES_POLYGONS_GUARD__
#define __LFRL_OGL_CAPACITIES_POLYGONS_GUARD__

#include "Hint.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Polygons
{
	enum struct Mode
	{
		LINE = GL_LINE,
		POINT = GL_POINT,
		FILL = GL_FILL
	};

	Mode GetMode() noexcept;
	void SetMode(Mode mode) noexcept;
	void SetLineMode() noexcept { SetMode(Mode::LINE); }
	void SetPointMode() noexcept { SetMode(Mode::POINT); }
	void SetFillMode() noexcept { SetMode(Mode::FILL); }

	namespace Offset
	{
		struct data final
		{
			GLfloat factor;
			GLfloat units;
		};

		data Get() noexcept;
		void Set(data offset) noexcept { Set(offset.factor, offset.units); }
		void Set(GLfloat factor, GLfloat units) noexcept;

		namespace Line
		{
			bool IsEnabled() noexcept;
			void Enable() noexcept;
			void Disable() noexcept;
		}

		namespace Point
		{
			bool IsEnabled() noexcept;
			void Enable() noexcept;
			void Disable() noexcept;
		}

		namespace Fill
		{
			bool IsEnabled() noexcept;
			void Enable() noexcept;
			void Disable() noexcept;
		}
	}

	namespace Smoothing
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		Hint GetHint() noexcept;
		void SetHint(Hint hint) noexcept;
		void HintFast() noexcept { SetHint(Hint::FAST); }
		void HintNice() noexcept { SetHint(Hint::NICE); }
		void HintAny() noexcept { SetHint(Hint::ANY); }
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
