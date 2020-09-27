#include "PointTestContext.h"

using namespace LFRL_OGL_CAPACITIES;

BEGIN_LFRL_OGL_CG_NAMESPACE

struct PointTestRenderingAction : public IRenderingAction
{
	typedef IRenderingAction base;

	PointTestRenderingAction() noexcept : base(), vao(), vbo()
	{
		vao.Initialize();
		vbo.Initialize();
	}

	VertexArrayObject vao;
	VertexBufferObject vbo;
	ShaderProgram::Uniform uProjection;
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
		Points::ProgramSize::Enable();
		wglSwapIntervalEXT(0);

		backgroundColor->Apply();
		Buffer::Clear(*clearBuffers);

		program->Use();
		uProjection.SetMat4(projection->Get());

		vao.Bind();
		glDrawArrays(GL_POINTS, 0, 3);
		vao.Unbind();

		program->Unuse();
	}
};

PointTestContext::PointTestContext(RenderingContext& rc, ShaderStore* shaders) noexcept
	: base(rc), _shaders(shaders), _timer(), _sProgram(nullptr), _projection(), _backgroundColor(), _clearBuffers()
{}

void PointTestContext::OnInitializing()
{
	base::OnInitializing();
	_timer.Initialize();

	auto vShader = _shaders->Load(ShaderObject::Type::VERTEX, "points_v_2");
	auto vCompileResult = vShader->Compile();

	auto gShader = _shaders->Load(ShaderObject::Type::GEOMETRY, "points_g_3");
	auto gCompileResult = gShader->Compile();

	auto fShader = _shaders->Load(ShaderObject::Type::FRAGMENT, "points_f_1");
	auto fCompileResult = fShader->Compile();

	_sProgram = _shaders->GetPrograms()->GetOrCreate("points_1");
	//if (_sProgram->GetState() != ObjectState::READY)
	//{
		_sProgram->AttachShader(*vShader);
		_sProgram->AttachShader(*gShader);
		_sProgram->AttachShader(*fShader);
		auto linkResult = _sProgram->Link();
	//}

	auto attributes = _sProgram->GetAttributes();
	auto uniforms = _sProgram->GetUniforms();

	_backgroundColor.value = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	_clearBuffers = static_cast<GLbitfield>(Buffer::Type::COLOR);

	auto colorAttr = attributes[0];
	auto positionAttr = attributes[1];
	auto sizeAttr = attributes[2];

	auto uProjection = uniforms[0];

	auto action = new PointTestRenderingAction();
	action->program = _sProgram;
	action->projection = &_projection;
	action->clearBuffers = &_clearBuffers;
	action->backgroundColor = &_backgroundColor;
	action->uProjection = uProjection;

	// TODO test points setup
	std::vector<PointVertex> points;
	points.push_back({ glm::vec3(100, 50, 0), glm::vec4(1, 1, 1, 1), 7 });
	points.push_back({ glm::vec3(80, 270, 0), glm::vec4(1, 0, 0, 1), 4 });
	points.push_back({ glm::vec3(220, 140, 0), glm::vec4(0, 1, 1, 1), 12 });

	action->vao.Bind();
	action->vbo.Bind();

	action->vbo.SetData(points);

	positionAttr.Enable();
	positionAttr.Configure(sizeof(PointVertex));
	colorAttr.Enable();
	colorAttr.Configure(sizeof(PointVertex), sizeof(glm::vec3));
	sizeAttr.Enable();
	sizeAttr.Configure(sizeof(PointVertex), sizeof(glm::vec3) + sizeof(glm::vec4));

	action->vao.Unbind();

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
