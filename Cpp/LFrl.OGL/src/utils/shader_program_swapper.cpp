#include "shader_program_swapper.h"

BEGIN_LFRL_OGL_NAMESPACE

bool __init_prog_swapper(GLuint id, GLuint& prevId)
{
	prevId = ShaderProgram::GetUsedId();

	if (id == prevId)
		return false;

	ShaderProgram::Use(id);
	return true;
}

shader_program_swapper::shader_program_swapper() noexcept
	: _id(0), _prev_id(0), _swapped(false)
{}

shader_program_swapper::shader_program_swapper(GLuint programId)
	: _id(programId), _prev_id(0), _swapped(false)
{
	_swapped = __init_prog_swapper(_id, _prev_id);
}

shader_program_swapper::shader_program_swapper(ShaderProgram const& program)
	: _id(program.GetId()), _prev_id(0), _swapped(false)
{
	_swapped = __init_prog_swapper(_id, _prev_id);
}

shader_program_swapper::shader_program_swapper(shader_program_swapper&& other) noexcept
	: _id(other._id), _prev_id(other._prev_id), _swapped(other._swapped)
{
	other._id = 0;
	other._prev_id = 0;
	other._swapped = false;
}

shader_program_swapper& shader_program_swapper::operator=(shader_program_swapper&& other)
{
	if (this != &other)
	{
		_id = other._id;
		_prev_id = other._prev_id;
		_swapped = other._swapped;

		other._id = 0;
		other._prev_id = 0;
		other._swapped = false;

		if (_swapped)
		{
			auto currentId = ShaderProgram::GetUsedId();
			if (currentId != _id)
				ShaderProgram::Use(_id);
		}
	}
	return *this;
}

bool shader_program_swapper::swap_back()
{
	if (_swapped)
	{
		ShaderProgram::Use(_prev_id);
		_swapped = false;
		return true;
	}
	return false;
}

END_LFRL_OGL_NAMESPACE
