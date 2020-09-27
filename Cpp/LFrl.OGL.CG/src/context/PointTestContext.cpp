#include "PointTestContext.h"

using namespace LFRL_OGL_CAPACITIES;

BEGIN_LFRL_OGL_CG_NAMESPACE

struct PointTestRenderingAction : public IRenderingAction
{
	typedef IRenderingAction base;

	PointTestRenderingAction() noexcept : base() {}

	ShaderProgram* program;
	Projection* projection;
	Color::ClearValueSnapshot* backgroundColor;
	GLbitfield* clearBuffers;

protected:
	void OnInvoked() override
	{
		Depth::Test::Disable();
		FaceCulling::Enable();
		FaceCulling::Cull::SetBack();
		Sampling::Multi::Enable();
		Points::SetSize(5);
		wglSwapIntervalEXT(0);

		backgroundColor->Apply();
		Buffer::Clear(*clearBuffers);
	}
};

PointTestContext::PointTestContext(RenderingContext& rc, ShaderStore* shaders) noexcept
	: base(rc), _shaders(shaders), _timer(), _sProgram(nullptr), _projection(), _backgroundColor(), _clearBuffers()
{}

void PointTestContext::OnInitializing()
{
	base::OnInitializing();
	_timer.Initialize();

	auto vShader = _shaders->Load(ShaderObject::Type::VERTEX, "points_v_1");
	auto vCompileResult = vShader->Compile();

	auto fShader = _shaders->Load(ShaderObject::Type::FRAGMENT, "points_f_1");
	auto fCompileResult = fShader->Compile();

	_sProgram = _shaders->GetPrograms()->GetOrCreate("points_1");
	if (_sProgram->GetState() != ObjectState::READY)
	{
		_sProgram->AttachShader(*vShader);
		_sProgram->AttachShader(*fShader);
		auto linkResult = _sProgram->Link();
	}

	auto attributes = _sProgram->GetAttributes();
	auto uniforms = _sProgram->GetUniforms();

	_backgroundColor.value = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	_clearBuffers = static_cast<GLbitfield>(Buffer::Type::COLOR);

	auto action = new PointTestRenderingAction();
	action->program = _sProgram;
	action->projection = &_projection;
	action->clearBuffers = &_clearBuffers;
	action->backgroundColor = &_backgroundColor;

	GetPipeline()->Add(action);
}

void PointTestContext::OnDisposing()
{
	_timer.Dispose();
	_sProgram = nullptr;
	base::OnDisposing();
}

void PointTestContext::OnStartDrawing()
{
	base::OnStartDrawing();
	_timer.Begin();
}

void PointTestContext::OnFinishDrawing()
{
	_timer.End();
	base::OnFinishDrawing();
}

void PointTestContext::OnBoundsChanged(glm::ivec2 const& position, glm::ivec2 const& size)
{
	_projection.SetOrthogonal(static_cast<GLfloat>(size.x), static_cast<GLfloat>(size.y));
	base::OnBoundsChanged(position, size);
}

END_LFRL_OGL_CG_NAMESPACE
