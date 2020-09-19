#include "FaceCulling.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

void FaceCulling::FrontOrientation::Set(FaceCulling::FrontOrientation::Type type) noexcept
{
	glFrontFace(static_cast<GLenum>(type));
}

FaceCulling::FrontOrientation::Snapshot FaceCulling::FrontOrientation::Snapshot::Load() noexcept
{
	FaceCulling::FrontOrientation::Snapshot result;
	result.type = FaceCulling::FrontOrientation::Get();
	return result;
}

FaceCulling::FrontOrientation::Snapshot::Snapshot() noexcept
	: type(FaceCulling::FrontOrientation::Type::CCW)
{}

void FaceCulling::FrontOrientation::Snapshot::Apply() noexcept
{
	FaceCulling::FrontOrientation::Set(type);
}

void FaceCulling::Cull::Set(FaceType face) noexcept
{
	glCullFace(static_cast<GLenum>(face));
}

FaceCulling::Cull::Snapshot FaceCulling::Cull::Snapshot::Load() noexcept
{
	FaceCulling::Cull::Snapshot result;
	result.type = FaceCulling::Cull::Get();
	return result;
}

FaceCulling::Cull::Snapshot::Snapshot() noexcept
	: type(FaceType::BACK)
{}

void FaceCulling::Cull::Snapshot::Apply() noexcept
{
	FaceCulling::Cull::Set(type);
}

FaceCulling::Snapshot FaceCulling::Snapshot::Load() noexcept
{
	FaceCulling::Snapshot result;
	result.toggle = FaceCulling::ToggleSnapshot::Load();
	result.frontOrientation = FaceCulling::FrontOrientation::Snapshot::Load();
	result.cull = FaceCulling::Cull::Snapshot::Load();
	return result;
}

FaceCulling::Snapshot::Snapshot() noexcept
	: toggle(),
	frontOrientation(),
	cull()
{}

void FaceCulling::Snapshot::Apply() noexcept
{
	toggle.Apply();
	frontOrientation.Apply();
	cull.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
