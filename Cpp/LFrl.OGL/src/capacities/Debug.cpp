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
	return glGetDebugMessageLog(count, bufSize, reinterpret_cast<GLenum*>(sources), reinterpret_cast<GLenum*>(types), ids, reinterpret_cast<GLenum*>(severities), reinterpret_cast<GLsizei*>(lengths), messageLog);
}

void Debug::InsertMessage(Debug::MessageSource source, Debug::MessageType type, GLuint id, Debug::MessageSeverity severity, GLuint length, char const* message)
{
	glDebugMessageInsert(static_cast<GLenum>(source), static_cast<GLenum>(type), id, static_cast<GLenum>(severity), length, message);
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
	glDebugMessageControl(static_cast<GLenum>(source), static_cast<GLenum>(type), static_cast<GLenum>(severity), count, ids, enabled);
}

void Debug::ClearErrors() noexcept
{
	while (GetError() != Debug::ErrorType::NONE)
		;
}

Debug::ErrorType Debug::GetError() noexcept
{
	return static_cast<Debug::ErrorType>(glGetError());
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
