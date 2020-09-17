#ifndef __LFRL_OGL_CAPACITIES_BLENDING_GUARD__
#define __LFRL_OGL_CAPACITIES_BLENDING_GUARD__

#include "HintType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Blending
{
	bool IsEnabled() noexcept;
	void Enable() noexcept;
	void Disable() noexcept;

	glm::vec4 GetColor() noexcept;
	void SetColor(glm::vec4 const& color) noexcept { SetColor(color.r, color.g, color.b, color.a); }
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept;
	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) noexcept { SetColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }

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

		Factor GetSourceRgbFactor() noexcept;
		Factor GetDestinationRgbFactor() noexcept;
		Factor GetSourceAlphaFactor() noexcept;
		Factor GetDestinationAlphaFactor() noexcept;

		void Set(Factor sfactor, Factor dfactor) noexcept;
		void SetSeparate(Factor sfactorRgb, Factor dfactorRgb, Factor sfactorAlpha, Factor dfactorAlpha) noexcept;
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

		Mode GetRbgMode() noexcept;
		Mode GetAlphaMode() noexcept;

		void Set(Mode mode) noexcept;
		void SetSeparate(Mode rgb, Mode alpha) noexcept;
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

		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		Code Get() noexcept;
		void Set(Code code) noexcept;
	}
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
