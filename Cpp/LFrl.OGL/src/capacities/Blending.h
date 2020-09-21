#ifndef __LFRL_OGL_CAPACITIES_BLENDING_GUARD__
#define __LFRL_OGL_CAPACITIES_BLENDING_GUARD__

#include "macros.h"
#include "HintType.h"

#define __LFRL_OGL_BLENDING_CAPACITY_DEFAULT_COLOR glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Blending
{
	glm::vec4 GetColor() noexcept;
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept;
	inline void SetColor(glm::vec4 const& color) noexcept { SetColor(color.r, color.g, color.b, color.a); }
	inline void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) noexcept { SetColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }

	LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_BLEND, false);
	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Color, glm::vec4, __LFRL_OGL_BLENDING_CAPACITY_DEFAULT_COLOR, GetColor, SetColor);

	namespace Func
	{
		enum struct Factor
		{
			ZERO = GL_ZERO,
			ONE = GL_ONE,
			SRC_COLOR = GL_SRC_COLOR,
			ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
			DST_COLOR = GL_DST_COLOR,
			ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
			SRC_ALPHA = GL_SRC_ALPHA,
			ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
			DST_ALPHA = GL_DST_ALPHA,
			ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
			CONSTANT_COLOR = GL_CONSTANT_COLOR,
			ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
			CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
			ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA
		};

		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(SourceRgbFactor, Factor, GL_BLEND_SRC_RGB)
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(DestinationRgbFactor, Factor, GL_BLEND_DST_RGB)
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(SourceAlphaFactor, Factor, GL_BLEND_SRC_ALPHA)
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(DestinationAlphaFactor, Factor, GL_BLEND_DST_ALPHA)

		void Set(Factor sfactor, Factor dfactor) noexcept;
		void SetSeparate(Factor sfactorRgb, Factor dfactorRgb, Factor sfactorAlpha, Factor dfactorAlpha) noexcept;

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			Factor sourceRgbFactor;
			Factor destinationRgbFactor;
			Factor sourceAlphaFactor;
			Factor destinationAlphaFactor;);
	}

	namespace Equation
	{
		enum struct Mode
		{
			FUNC_ADD = GL_FUNC_ADD,
			FUNC_SUBTRACT = GL_FUNC_SUBTRACT,
			FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
			MIN = GL_MIN,
			MAX = GL_MAX
		};

		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(RbgMode, Mode, GL_BLEND_EQUATION_RGB)
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(AlphaMode, Mode, GL_BLEND_EQUATION_ALPHA)

		void Set(Mode mode) noexcept;
		void SetSeparate(Mode rgb, Mode alpha) noexcept;

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			Mode rgbMode;
			Mode alphaMode;);
	}

	namespace LogicOp
	{
		enum struct Code
		{
			CLEAR = GL_CLEAR,
			SET = GL_SET,
			COPY = GL_COPY,
			COPY_INVERTED = GL_COPY_INVERTED,
			NOOP = GL_NOOP,
			INVERT = GL_INVERT,
			AND = GL_AND,
			NAND = GL_NAND,
			OR = GL_OR,
			NOR = GL_NOR,
			XOR = GL_XOR,
			EQUIV = GL_EQUIV,
			AND_REVERSE = GL_AND_REVERSE,
			AND_INVERTED = GL_AND_INVERTED,
			OR_REVERSE = GL_OR_REVERSE,
			OR_INVERTED = GL_OR_INVERTED
		};

		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(, Code, GL_LOGIC_OP_MODE)

		void Set(Code code) noexcept;

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_COLOR_LOGIC_OP, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Code, Code, Code::COPY, Get, Set);

		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			CodeSnapshot code;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ToggleSnapshot toggle;
		ColorSnapshot color;
		Func::Snapshot func;
		Equation::Snapshot equation;
		LogicOp::Snapshot logicOp;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_BLENDING_CAPACITY_DEFAULT_COLOR

#endif
