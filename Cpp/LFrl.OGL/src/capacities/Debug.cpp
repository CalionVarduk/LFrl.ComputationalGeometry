#include "Debug.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Debug::IsAsync() noexcept
{
	return !glIsEnabled(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debug::MakeAsync() noexcept
{
	glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debug::MakeSync() noexcept
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debug::RegisterCallback(GLDEBUGPROC callback, void const* userParam) noexcept
{
	glDebugMessageCallback(callback, userParam);
}

GLuint Debug::GetMessageLog(GLuint count, GLuint bufSize, Debug::MessageSource* sources, Debug::MessageType* types, GLuint* ids, Debug::MessageSeverity* severities, GLuint* lengths, char* messageLog)
{
	return glGetDebugMessageLog(count, bufSize, (GLenum*)sources, (GLenum*)types, ids, (GLenum*)severities, (GLsizei*)lengths, messageLog);
}

void Debug::InsertMessage(Debug::MessageSource source, Debug::MessageType type, GLuint id, Debug::MessageSeverity severity, GLuint length, char const* message)
{
	glDebugMessageInsert((GLenum)source, (GLenum)type, id, (GLenum)severity, length, message);
}

void Debug::EnableMessages(Debug::MessageSource source, Debug::MessageType type, Debug::MessageSeverity severity, GLuint count, GLuint const* ids)
{
	Debug::MessageControl(source, type, severity, count, ids, true);
}

void Debug::DisableMessages(Debug::MessageSource source, Debug::MessageType type, Debug::MessageSeverity severity, GLuint count, GLuint const* ids)
{
	Debug::MessageControl(source, type, severity, count, ids, false);
}

void Debug::MessageControl(Debug::MessageSource source, Debug::MessageType type, Debug::MessageSeverity severity, GLuint count, GLuint const* ids, bool enabled)
{
	glDebugMessageControl((GLenum)source, (GLenum)type, (GLenum)severity, count, ids, enabled);
}

Debug::ErrorType Debug::GetError() noexcept
{
	return (Debug::ErrorType)glGetError();
}

Debug::Snapshot Debug::Snapshot::Load() noexcept
{
	Debug::Snapshot result;
	result.toggle = Debug::ToggleSnapshot::Load();
	result.async = Debug::AsyncSnapshot::Load();
	return result;
}

Debug::Snapshot::Snapshot() noexcept
	: toggle(),
	async()
{}

void Debug::Snapshot::Apply() noexcept
{
	toggle.Apply();
	async.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
