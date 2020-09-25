#ifndef __LFRL_OGL_CAPACITIES_DEBUG_GUARD__
#define __LFRL_OGL_CAPACITIES_DEBUG_GUARD__

#include "macros.h"
#include "../internal/namespace_macros.h"

#define __LFRL_OGL_DEFINE_DEBUG_ASYNC_CAPACITY_SETTER(ASYNC)\
if (ASYNC) MakeAsync(); \
else MakeSync();

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Debug
{
	enum struct MessageSource
	{
		APPLICATION = GL_DEBUG_SOURCE_APPLICATION,
		THIRD_PARTY = GL_DEBUG_SOURCE_THIRD_PARTY
	};

	enum struct MessageType
	{
		ERRONEOUS = GL_DEBUG_TYPE_ERROR,
		DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
		UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
		PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,
		PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,
		MARKER = GL_DEBUG_TYPE_MARKER,
		PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP,
		POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,
		OTHER = GL_DEBUG_TYPE_OTHER
	};

	enum struct MessageSeverity
	{
		LOW = GL_DEBUG_SEVERITY_LOW,
		MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,
		HIGH = GL_DEBUG_SEVERITY_HIGH,
		NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION
	};

	enum struct ErrorType
	{
		NONE = GL_NO_ERROR,
		INVALID_ENUM = GL_INVALID_ENUM,
		INVALID_VALUE = GL_INVALID_VALUE,
		INVALID_OPERATION = GL_INVALID_OPERATION,
		INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
		OUT_OF_MEMORY = GL_OUT_OF_MEMORY
	};

	LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_DEBUG_OUTPUT, false);

	bool IsAsync() noexcept;
	void MakeAsync() noexcept;
	void MakeSync() noexcept;

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Async, bool, true, IsAsync, __LFRL_OGL_DEFINE_DEBUG_ASYNC_CAPACITY_SETTER);

	void RegisterCallback(GLDEBUGPROC callback, void const* userParam = NULL) noexcept;

	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(LoggedMessages, GLuint, GL_DEBUG_LOGGED_MESSAGES)
	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(NextMessageLength, GLuint, GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH)
	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(MaxLoggedMessages, GLuint, GL_MAX_DEBUG_LOGGED_MESSAGES)
	LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(MaxMessageLength, GLuint, GL_MAX_DEBUG_MESSAGE_LENGTH)

	GLuint GetMessageLog(GLuint count, GLuint bufSize, MessageSource* sources, MessageType* types, GLuint* ids, MessageSeverity* severities, GLuint* lengths, char* messageLog);
	void InsertMessage(MessageSource source, MessageType type, GLuint id, MessageSeverity severity, GLuint length, char const* message);

	void EnableMessages(MessageSource source, MessageType type, MessageSeverity severity, GLuint count, GLuint const* ids);
	void DisableMessages(MessageSource source, MessageType type, MessageSeverity severity, GLuint count, GLuint const* ids);
	void MessageControl(MessageSource source, MessageType type, MessageSeverity severity, GLuint count, GLuint const* ids, bool enabled);

	ErrorType GetError() noexcept;

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ToggleSnapshot toggle;
		AsyncSnapshot async;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_DEFINE_DEBUG_ASYNC_CAPACITY_SETTER

#endif
