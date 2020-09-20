#include "ShaderVariableType.h"

BEGIN_LFRL_OGL_NAMESPACE

constexpr GLuint ShaderVariableType::GetColumnCount(ShaderVariableType::Code code) noexcept
{
	switch (code)
	{
	case ShaderVariableType::Code::FLOAT:
	case ShaderVariableType::Code::FLOAT_VEC2:
	case ShaderVariableType::Code::FLOAT_VEC3:
	case ShaderVariableType::Code::FLOAT_VEC4:
	case ShaderVariableType::Code::INT:
	case ShaderVariableType::Code::INT_VEC2:
	case ShaderVariableType::Code::INT_VEC3:
	case ShaderVariableType::Code::INT_VEC4:
	case ShaderVariableType::Code::UNSIGNED_INT:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC2:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC3:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC4:
	case ShaderVariableType::Code::DOUBLE:
	case ShaderVariableType::Code::DOUBLE_VEC2:
	case ShaderVariableType::Code::DOUBLE_VEC3:
	case ShaderVariableType::Code::DOUBLE_VEC4:
		return 1;
	case ShaderVariableType::Code::FLOAT_MAT2:
	case ShaderVariableType::Code::FLOAT_MAT2x3:
	case ShaderVariableType::Code::FLOAT_MAT2x4:
	case ShaderVariableType::Code::DOUBLE_MAT2:
	case ShaderVariableType::Code::DOUBLE_MAT2x3:
	case ShaderVariableType::Code::DOUBLE_MAT2x4:
		return 2;
	case ShaderVariableType::Code::FLOAT_MAT3:
	case ShaderVariableType::Code::FLOAT_MAT3x2:
	case ShaderVariableType::Code::FLOAT_MAT3x4:
	case ShaderVariableType::Code::DOUBLE_MAT3:
	case ShaderVariableType::Code::DOUBLE_MAT3x2:
	case ShaderVariableType::Code::DOUBLE_MAT3x4:
		return 3;
	case ShaderVariableType::Code::FLOAT_MAT4:
	case ShaderVariableType::Code::FLOAT_MAT4x2:
	case ShaderVariableType::Code::FLOAT_MAT4x3:
	case ShaderVariableType::Code::DOUBLE_MAT4:
	case ShaderVariableType::Code::DOUBLE_MAT4x2:
	case ShaderVariableType::Code::DOUBLE_MAT4x3:
		return 4;
	}
	return 0;
}

constexpr GLuint ShaderVariableType::GetRowCount(ShaderVariableType::Code code) noexcept
{
	auto columnCount = GetColumnCount(code);
	return columnCount == 0 ? 0 : GetScalarCount(code) / columnCount;
}

constexpr GLuint ShaderVariableType::GetScalarCount(ShaderVariableType::Code code) noexcept
{
	switch (code)
	{
	case ShaderVariableType::Code::FLOAT:
	case ShaderVariableType::Code::INT:
	case ShaderVariableType::Code::UNSIGNED_INT:
	case ShaderVariableType::Code::DOUBLE:
		return 1;
	case ShaderVariableType::Code::FLOAT_VEC2:
	case ShaderVariableType::Code::INT_VEC2:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC2:
	case ShaderVariableType::Code::DOUBLE_VEC2:
		return 2;
	case ShaderVariableType::Code::FLOAT_VEC3:
	case ShaderVariableType::Code::INT_VEC3:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC3:
	case ShaderVariableType::Code::DOUBLE_VEC3:
		return 3;
	case ShaderVariableType::Code::FLOAT_VEC4:
	case ShaderVariableType::Code::FLOAT_MAT2:
	case ShaderVariableType::Code::INT_VEC4:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC4:
	case ShaderVariableType::Code::DOUBLE_VEC4:
	case ShaderVariableType::Code::DOUBLE_MAT2:
		return 4;
	case ShaderVariableType::Code::FLOAT_MAT2x3:
	case ShaderVariableType::Code::FLOAT_MAT3x2:
	case ShaderVariableType::Code::DOUBLE_MAT2x3:
	case ShaderVariableType::Code::DOUBLE_MAT3x2:
		return 6;
	case ShaderVariableType::Code::FLOAT_MAT2x4:
	case ShaderVariableType::Code::FLOAT_MAT4x2:
	case ShaderVariableType::Code::DOUBLE_MAT2x4:
	case ShaderVariableType::Code::DOUBLE_MAT4x2:
		return 8;
	case ShaderVariableType::Code::FLOAT_MAT3:
	case ShaderVariableType::Code::DOUBLE_MAT3:
		return 9;
	case ShaderVariableType::Code::FLOAT_MAT3x4:
	case ShaderVariableType::Code::FLOAT_MAT4x3:
	case ShaderVariableType::Code::DOUBLE_MAT3x4:
	case ShaderVariableType::Code::DOUBLE_MAT4x3:
		return 12;
	case ShaderVariableType::Code::FLOAT_MAT4:
	case ShaderVariableType::Code::DOUBLE_MAT4:
		return 16;
	}
	return 0;
}

constexpr ShaderVariableType::Code ShaderVariableType::GetScalarTypeCode(ShaderVariableType::Code code) noexcept
{
	switch (code)
	{
	case ShaderVariableType::Code::FLOAT:
	case ShaderVariableType::Code::FLOAT_VEC2:
	case ShaderVariableType::Code::FLOAT_VEC3:
	case ShaderVariableType::Code::FLOAT_VEC4:
	case ShaderVariableType::Code::FLOAT_MAT2:
	case ShaderVariableType::Code::FLOAT_MAT3:
	case ShaderVariableType::Code::FLOAT_MAT4:
	case ShaderVariableType::Code::FLOAT_MAT2x3:
	case ShaderVariableType::Code::FLOAT_MAT2x4:
	case ShaderVariableType::Code::FLOAT_MAT3x2:
	case ShaderVariableType::Code::FLOAT_MAT3x4:
	case ShaderVariableType::Code::FLOAT_MAT4x2:
	case ShaderVariableType::Code::FLOAT_MAT4x3:
		return ShaderVariableType::Code::FLOAT;
	case ShaderVariableType::Code::INT:
	case ShaderVariableType::Code::INT_VEC2:
	case ShaderVariableType::Code::INT_VEC3:
	case ShaderVariableType::Code::INT_VEC4:
		return ShaderVariableType::Code::INT;
	case ShaderVariableType::Code::UNSIGNED_INT:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC2:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC3:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC4:
		return ShaderVariableType::Code::UNSIGNED_INT;
	case ShaderVariableType::Code::DOUBLE:
	case ShaderVariableType::Code::DOUBLE_VEC2:
	case ShaderVariableType::Code::DOUBLE_VEC3:
	case ShaderVariableType::Code::DOUBLE_VEC4:
	case ShaderVariableType::Code::DOUBLE_MAT2:
	case ShaderVariableType::Code::DOUBLE_MAT3:
	case ShaderVariableType::Code::DOUBLE_MAT4:
	case ShaderVariableType::Code::DOUBLE_MAT2x3:
	case ShaderVariableType::Code::DOUBLE_MAT2x4:
	case ShaderVariableType::Code::DOUBLE_MAT3x2:
	case ShaderVariableType::Code::DOUBLE_MAT3x4:
	case ShaderVariableType::Code::DOUBLE_MAT4x2:
	case ShaderVariableType::Code::DOUBLE_MAT4x3:
		return ShaderVariableType::Code::DOUBLE;
	}
	return ShaderVariableType::Code::UNDEFINED;
}

constexpr GLuint ShaderVariableType::GetScalarSize(ShaderVariableType::Code code) noexcept
{
	switch (code)
	{
	case ShaderVariableType::Code::FLOAT:
	case ShaderVariableType::Code::FLOAT_VEC2:
	case ShaderVariableType::Code::FLOAT_VEC3:
	case ShaderVariableType::Code::FLOAT_VEC4:
	case ShaderVariableType::Code::FLOAT_MAT2:
	case ShaderVariableType::Code::FLOAT_MAT3:
	case ShaderVariableType::Code::FLOAT_MAT4:
	case ShaderVariableType::Code::FLOAT_MAT2x3:
	case ShaderVariableType::Code::FLOAT_MAT2x4:
	case ShaderVariableType::Code::FLOAT_MAT3x2:
	case ShaderVariableType::Code::FLOAT_MAT3x4:
	case ShaderVariableType::Code::FLOAT_MAT4x2:
	case ShaderVariableType::Code::FLOAT_MAT4x3:
		return sizeof(GLfloat);
	case ShaderVariableType::Code::INT:
	case ShaderVariableType::Code::INT_VEC2:
	case ShaderVariableType::Code::INT_VEC3:
	case ShaderVariableType::Code::INT_VEC4:
		return sizeof(GLint);
	case ShaderVariableType::Code::UNSIGNED_INT:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC2:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC3:
	case ShaderVariableType::Code::UNSIGNED_INT_VEC4:
		return sizeof(GLuint);
	case ShaderVariableType::Code::DOUBLE:
	case ShaderVariableType::Code::DOUBLE_VEC2:
	case ShaderVariableType::Code::DOUBLE_VEC3:
	case ShaderVariableType::Code::DOUBLE_VEC4:
	case ShaderVariableType::Code::DOUBLE_MAT2:
	case ShaderVariableType::Code::DOUBLE_MAT3:
	case ShaderVariableType::Code::DOUBLE_MAT4:
	case ShaderVariableType::Code::DOUBLE_MAT2x3:
	case ShaderVariableType::Code::DOUBLE_MAT2x4:
	case ShaderVariableType::Code::DOUBLE_MAT3x2:
	case ShaderVariableType::Code::DOUBLE_MAT3x4:
	case ShaderVariableType::Code::DOUBLE_MAT4x2:
	case ShaderVariableType::Code::DOUBLE_MAT4x3:
		return sizeof(GLdouble);
	}
	return 0;
}

constexpr ShaderVariableType ShaderVariableType::Create(ShaderVariableType::Code code) noexcept
{
	ShaderVariableType result;
	result._code = code;
	result._columnCount = GetColumnCount(code);
	result._rowCount = GetRowCount(code);
	result._scalarCount = GetScalarCount(code);
	result._scalarTypeCode = GetScalarTypeCode(code);
	result._scalarSize = GetScalarSize(code);
	result._columnSize = GetColumnSize(code);
	result._rowSize = GetRowSize(code);
	result._size = GetSize(code);
	return result;
}

constexpr ShaderVariableType::ShaderVariableType() noexcept
	: _code(Code::UNDEFINED), _columnCount(0), _rowCount(0), _scalarCount(0), _scalarTypeCode(Code::UNDEFINED), _scalarSize(0), _columnSize(0), _rowSize(0), _size(0)
{}

END_LFRL_OGL_NAMESPACE
