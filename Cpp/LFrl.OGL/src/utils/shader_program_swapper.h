#ifndef __LFRL_OGL_SHADER_PROGRAM_SWAPPER_GUARD__
#define __LFRL_OGL_SHADER_PROGRAM_SWAPPER_GUARD__

#include "../primitives/ShaderProgram.h"

BEGIN_LFRL_OGL_NAMESPACE

struct shader_program_swapper final
{
	shader_program_swapper(shader_program_swapper const&) = delete;
	shader_program_swapper& operator=(shader_program_swapper const&) = delete;

	shader_program_swapper();
	explicit shader_program_swapper(GLuint programId);
	explicit shader_program_swapper(ShaderProgram const& program);
	shader_program_swapper(shader_program_swapper&&) noexcept;
	shader_program_swapper& operator=(shader_program_swapper&&);
	~shader_program_swapper() { swap_back(); }

	bool swapped() const noexcept { return _swapped; }
	GLuint id() const noexcept { return _id; }
	GLuint prev_id() const noexcept { return _prev_id; }

	bool swap_back();

private:
	bool _swapped;
	GLuint _id;
	GLuint _prev_id;
};

END_LFRL_OGL_NAMESPACE

#endif
