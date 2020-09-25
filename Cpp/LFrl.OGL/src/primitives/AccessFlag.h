#ifndef __LFRL_OGL_ACCESS_FLAG_GUARD__
#define __LFRL_OGL_ACCESS_FLAG_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_NAMESPACE

enum struct AccessFlag
{
	READ = GL_MAP_READ_BIT,
	WRITE = GL_MAP_WRITE_BIT,
	PERSISTENT = GL_MAP_PERSISTENT_BIT,
	COHERENT = GL_MAP_COHERENT_BIT,
	INVALIDATE_RANGE = GL_MAP_INVALIDATE_RANGE_BIT,
	INVALIDATE_BUFFER = GL_MAP_INVALIDATE_BUFFER_BIT,
	FLUSH_EXPLICIT = GL_MAP_FLUSH_EXPLICIT_BIT,
	UNSYNCHRONIZED = GL_MAP_UNSYNCHRONIZED_BIT
};

inline GLbitfield operator| (AccessFlag l, AccessFlag r) noexcept { return static_cast<GLbitfield>(l) | static_cast<GLbitfield>(r); }
inline GLbitfield operator| (AccessFlag l, GLbitfield r) noexcept { return static_cast<GLbitfield>(l) | r; }
inline GLbitfield operator| (GLbitfield l, AccessFlag r) noexcept { return l | static_cast<GLbitfield>(r); }
inline GLbitfield operator|= (GLbitfield l, AccessFlag r) noexcept { return l | static_cast<GLbitfield>(r); }

END_LFRL_OGL_NAMESPACE

#endif
