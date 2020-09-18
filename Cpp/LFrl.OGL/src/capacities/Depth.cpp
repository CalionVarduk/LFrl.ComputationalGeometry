#include "Depth.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Depth::IsReadonly() noexcept
{
	GLboolean result;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &result);
	return !result;
}

void Depth::MakeWritable() noexcept
{
	glDepthMask(GL_TRUE);
}

void Depth::MakeReadonly() noexcept
{
	glDepthMask(GL_FALSE);
}

void Depth::SetClearValue(GLdouble value) noexcept
{
	glClearDepth(value);
}

Depth::Range::data Depth::Range::Get() noexcept
{
	GLdouble result[2] = { 0.0, 0.0 };
	glGetDoublev(GL_DEPTH_RANGE, result);
	return { result[0], result[1] };
}

void Depth::Range::Set(GLdouble zNear, GLdouble zFar) noexcept
{
	glDepthRange(zNear, zFar);
}

Depth::Range::Snapshot Depth::Range::Snapshot::Load() noexcept
{
	Depth::Range::Snapshot result;
	result.data = Depth::Range::Get();
	return result;
}

Depth::Range::Snapshot::Snapshot() noexcept
	: data({ 0.0, 1.0 })
{}

void Depth::Range::Snapshot::Apply() noexcept
{
	Depth::Range::Set(data);
}

void Depth::Func::Set(FuncType type) noexcept
{
	glDepthFunc((GLenum)type);
}

Depth::Func::Snapshot Depth::Func::Snapshot::Load() noexcept
{
	Depth::Func::Snapshot result;
	result.type = Depth::Func::Get();
	return result;
}

Depth::Func::Snapshot::Snapshot() noexcept
	: type(FuncType::LESS_THAN)
{}

void Depth::Func::Snapshot::Apply() noexcept
{
	Depth::Func::Set(type);
}

Depth::Snapshot Depth::Snapshot::Load() noexcept
{
	Depth::Snapshot result;
	result.readonly = Depth::ReadonlySnapshot::Load();
	result.clearValue = Depth::ClearValueSnapshot::Load();
	result.test = Depth::Test::Snapshot::Load();
	result.range = Depth::Range::Snapshot::Load();
	result.clamping = Depth::Clamping::Snapshot::Load();
	result.func = Depth::Func::Snapshot::Load();
	return result;
}

Depth::Snapshot::Snapshot() noexcept
	: readonly(),
	clearValue(),
	test(),
	range(),
	clamping(),
	func()
{}

void Depth::Snapshot::Apply() noexcept
{
	readonly.Apply();
	clearValue.Apply();
	test.Apply();
	range.Apply();
	clamping.Apply();
	func.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
