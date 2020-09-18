#ifndef __LFRL_OGL_CAPACITIES_POLYGONS_GUARD__
#define __LFRL_OGL_CAPACITIES_POLYGONS_GUARD__

#include "macros.h"
#include "HintType.h"

#define __LFRL_OGL_POLYGONS_OFFSET_CAPACITY_DEFAULT_DATA { 0.0f, 0.0f }

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Polygons
{
	enum struct Mode
	{
		LINE = GL_LINE,
		POINT = GL_POINT,
		FILL = GL_FILL
	};

	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Mode, Mode, GL_POLYGON_MODE)

	void SetMode(Mode mode) noexcept;
	void SetLineMode() noexcept { SetMode(Mode::LINE); }
	void SetPointMode() noexcept { SetMode(Mode::POINT); }
	void SetFillMode() noexcept { SetMode(Mode::FILL); }

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Mode, Mode, Mode::FILL, GetMode, SetMode);

	namespace Offset
	{
		struct data final
		{
			GLfloat factor;
			GLfloat units;
		};

		data Get() noexcept;
		void Set(GLfloat factor, GLfloat units) noexcept;
		void Set(data offset) noexcept { Set(offset.factor, offset.units); }

		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Offset, data, __LFRL_OGL_POLYGONS_OFFSET_CAPACITY_DEFAULT_DATA, Get, Set);

		namespace Line
		{
			LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_POLYGON_OFFSET_LINE, false);
		}

		namespace Point
		{
			LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_POLYGON_OFFSET_POINT, false);
		}

		namespace Fill
		{
			LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_POLYGON_OFFSET_FILL, false);
		}

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			OffsetSnapshot offset;
			Line::Snapshot line;
			Point::Snapshot point;
			Fill::Snapshot fill;);
	}

	namespace Smoothing
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Hint, HintType, GL_POLYGON_SMOOTH_HINT)

		void SetHint(HintType hint) noexcept;
		void HintFast() noexcept { SetHint(HintType::FAST); }
		void HintNice() noexcept { SetHint(HintType::NICE); }
		void HintAny() noexcept { SetHint(HintType::ANY); }

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_POLYGON_SMOOTH, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Hint, HintType, HintType::ANY, GetHint, SetHint);
		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			HintSnapshot hint;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ModeSnapshot mode;
		Offset::Snapshot offset;
		Smoothing::Snapshot smoothing;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_POLYGONS_OFFSET_CAPACITY_DEFAULT_DATA

#endif
