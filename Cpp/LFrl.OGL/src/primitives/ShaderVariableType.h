#ifndef __LFRL_OGL_SHADER_VARIABLE_TYPE_GUARD__
#define __LFRL_OGL_SHADER_VARIABLE_TYPE_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_NAMESPACE

struct ShaderVariableType final
{
	enum struct Code
	{
		UNDEFINED = 0,
		FLOAT = GL_FLOAT,
		FLOAT_VEC2 = GL_FLOAT_VEC2,
		FLOAT_VEC3 = GL_FLOAT_VEC3,
		FLOAT_VEC4 = GL_FLOAT_VEC4,
		FLOAT_MAT2 = GL_FLOAT_MAT2,
		FLOAT_MAT3 = GL_FLOAT_MAT3,
		FLOAT_MAT4 = GL_FLOAT_MAT4,
		FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
		FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
		FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
		FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
		FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
		FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,
		INT = GL_INT,
		INT_VEC2 = GL_INT_VEC2,
		INT_VEC3 = GL_INT_VEC3,
		INT_VEC4 = GL_INT_VEC4,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
		UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
		UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,
		DOUBLE = GL_DOUBLE,
		DOUBLE_VEC2 = GL_DOUBLE_VEC2,
		DOUBLE_VEC3 = GL_DOUBLE_VEC3,
		DOUBLE_VEC4 = GL_DOUBLE_VEC4,
		DOUBLE_MAT2 = GL_DOUBLE_MAT2,
		DOUBLE_MAT3 = GL_DOUBLE_MAT3,
		DOUBLE_MAT4 = GL_DOUBLE_MAT4,
		DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
		DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
		DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
		DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
		DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
		DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3
	};

	static constexpr GLuint GetColumnCount(ShaderVariableType::Code code) noexcept;
	static constexpr GLuint GetRowCount(ShaderVariableType::Code code) noexcept;
	static constexpr GLuint GetScalarCount(ShaderVariableType::Code code) noexcept;
	static constexpr ShaderVariableType::Code GetScalarTypeCode(ShaderVariableType::Code code) noexcept;
	static constexpr GLuint GetScalarSize(ShaderVariableType::Code code) noexcept;
	static constexpr GLuint GetColumnSize(ShaderVariableType::Code code) noexcept { return GetRowCount(code) * GetScalarSize(code); }
	static constexpr GLuint GetRowSize(ShaderVariableType::Code code) noexcept { return GetColumnCount(code) * GetScalarSize(code); }
	static constexpr GLuint GetSize(ShaderVariableType::Code code) noexcept { return GetScalarCount(code) * GetScalarSize(code); }

	static constexpr ShaderVariableType Create(ShaderVariableType::Code code) noexcept;

	template <ShaderVariableType::Code code>
	static constexpr ShaderVariableType Create() noexcept { return Create(code); }

	constexpr ShaderVariableType::Code GetCode() const noexcept { return _code; }
	constexpr GLuint GetColumnCount() const noexcept { return _columnCount; }
	constexpr GLuint GetRowCount() const noexcept { return _rowCount; }
	constexpr GLuint GetScalarCount() const noexcept { return _scalarCount; }
	constexpr ShaderVariableType::Code GetScalarTypeCode() const noexcept { return _scalarTypeCode; }
	constexpr GLuint GetScalarSize() const noexcept { return _scalarSize; }
	constexpr GLuint GetColumnSize() const noexcept { return _columnSize; }
	constexpr GLuint GetRowSize() const noexcept { return _rowSize; }
	constexpr GLuint GetSize() const noexcept { return _size; }

	constexpr ShaderVariableType() noexcept;

private:
	ShaderVariableType::Code _code;
	GLuint _columnCount;
	GLuint _rowCount;
	GLuint _scalarCount;
	ShaderVariableType::Code _scalarTypeCode;
	GLuint _scalarSize;
	GLuint _columnSize;
	GLuint _rowSize;
	GLuint _size;
};

END_LFRL_OGL_NAMESPACE

#endif
