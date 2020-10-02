#include "PointTestContext.h"

#include "LFrl.Common/src/QuickRng.h"

using namespace LFRL_OGL_CAPACITIES;

BEGIN_LFRL_OGL_CG_NAMESPACE

struct SetupRenderingAction : public IRenderingAction
{
	typedef IRenderingAction base;

	SetupRenderingAction() noexcept : base()
	{
	}

	Color::ClearValueSnapshot* backgroundColor;
	GLbitfield* clearBuffers;

protected:
	void OnInvoked() override
	{
		FaceCulling::Enable();
		FaceCulling::Cull::SetBack();
		Sampling::Multi::Enable();
		wglSwapIntervalEXT(0);

		backgroundColor->Apply();
		Buffer::Clear(*clearBuffers);
	}
};

struct GridTestRenderingAction : public IRenderingAction
{
	typedef IRenderingAction base;

	GridTestRenderingAction() noexcept : base(), vao(), vbo()
	{
		vao.Initialize();
		vbo.SetUsage(BufferObject::Usage::DYNAMIC_DRAW);
		vbo.Initialize();
	}

	VertexArrayObject vao;
	BufferObject vbo;
	ShaderProgram::Uniform uProjection;
	ShaderProgram::Uniform uNormalColor;
	ShaderProgram::Uniform uGroupColor;
	ShaderProgram::Uniform uAxisColor;
	ShaderProgram::Uniform uNormalHalfWidth;
	ShaderProgram::Uniform uGroupHalfWidth;
	ShaderProgram::Uniform uAxisHalfWidth;
	ShaderProgram::Uniform uGroupSize;
	ShaderProgram::Uniform uLineOffset;
	ShaderProgram* program;
	OrthogonalView* view;

protected:
	void OnInvoked() override
	{
		Depth::Test::Enable();

		program->Use();
		
		auto lineOffset = 20;
		auto bounds = view->GetBounds();
		auto scale = view->GetScale();

		vbo.Bind();
		GridLineVertex gt[2];
		gt[0].positionOffset = glm::vec2(0, bounds.GetCentreY());
		gt[0].axisDirection = glm::vec2(1, 0);
		gt[0].lineHalfLength = glm::vec2(0, bounds.GetHeight() + 1);
		gt[0].baseLineId = glm::ceil(bounds.GetLeft() / lineOffset) - 1;
		gt[1].positionOffset = glm::vec2(bounds.GetCentreX(), 0);
		gt[1].axisDirection = glm::vec2(0, 1);
		gt[1].lineHalfLength = glm::vec2(bounds.GetWidth() + 1, 0);
		gt[1].baseLineId = glm::ceil(bounds.GetBottom() / lineOffset) - 1;
		vbo.SetData(gt);
		vbo.Unbind();

		auto xCount = (int)glm::ceil(bounds.GetWidth() / lineOffset) + 2;
		auto yCount = (int)glm::ceil(bounds.GetHeight() / lineOffset) + 2;

		uProjection.SetMat4(view->GetMatrix());
		uNormalColor.SetVec4(0.09f, 0.11f, 0.13f, 1.0f);
		uGroupColor.SetVec4(0.18f, 0.21f, 0.24f, 1.0f);
		uAxisColor.SetVec4(0.25f, 0.3f, 0.4f, 1.0f);
		uGroupSize.Set(10.0f);
		uLineOffset.Set((float)lineOffset);

		vao.Bind();

		uNormalHalfWidth.Set(0.5f / scale.x);
		uGroupHalfWidth.Set(0.5f / scale.x);
		uAxisHalfWidth.Set(1.0f / scale.x);
		glDrawArraysInstanced(GL_POINTS, 0, 1, xCount);

		uNormalHalfWidth.Set(0.5f / scale.y);
		uGroupHalfWidth.Set(0.5f / scale.y);
		uAxisHalfWidth.Set(1.0f / scale.y);
		glDrawArraysInstanced(GL_POINTS, 1, 1, yCount);

		vao.Unbind();

		program->Unuse();

		Buffer::Clear(Buffer::Type::DEPTH);
	}
};

struct PointTestRenderingAction : public IRenderingAction
{
	typedef IRenderingAction base;

	PointTestRenderingAction() noexcept : base(), vao(), vbo()
	{
		vao.Initialize();
		vbo.Initialize();
	}

	VertexArrayObject vao;
	BufferObject vbo;
	ShaderProgram::Uniform uProjection;
	ShaderProgram::Uniform uScale;
	ShaderProgram* program;
	OrthogonalView* view;

protected:
	void OnInvoked() override
	{
		Depth::Test::Disable();

		program->Use();

		uProjection.SetMat4(view->GetMatrix());
		uScale.SetVec2(view->GetScale());

		vao.Bind();
		glDrawArrays(GL_POINTS, 0, 10000);
		vao.Unbind();

		program->Unuse();
	}
};

PointTestContext::PointTestContext(RenderingContext& rc, ShaderStore* shaders) noexcept
	: base(rc), _shaders(shaders), _timer(), _view(), _backgroundColor(), _clearBuffers()
{}

void PointTestContext::_init_setup_action()
{
	_backgroundColor.value = glm::vec4(0.05f, 0.05f, 0.07f, 1.0f);
	_clearBuffers = Buffer::Type::COLOR | Buffer::Type::DEPTH;

	auto action = new SetupRenderingAction();
	action->backgroundColor = &_backgroundColor;
	action->clearBuffers = &_clearBuffers;

	GetPipeline()->Add(action);
}

void PointTestContext::_init_grid_action()
{
	auto vShader = _shaders->Load(ShaderObject::Type::VERTEX, "grid_v_2");
	auto vCompileResult = vShader->Compile();
	auto info = vShader->GetInfoLog();

	auto gShader = _shaders->Load(ShaderObject::Type::GEOMETRY, "grid_g_1");
	auto gCompileResult = gShader->Compile();

	auto fShader = _shaders->Load(ShaderObject::Type::FRAGMENT, "grid_f_1");
	auto fCompileResult = fShader->Compile();

	auto program = _shaders->GetPrograms()->GetOrCreate("grid");
	program->AttachShader(*vShader);
	program->AttachShader(*gShader);
	program->AttachShader(*fShader);
	auto linkResult = program->Link();

	auto attributes = program->GetAttributesMap();
	auto uniforms = program->GetUniformsMap();

	auto aPositionOffset = attributes["aPositionOffset"];
	auto aAxisDirection = attributes["aAxisDirection"];
	auto aLineHalfLength = attributes["aLineHalfLength"];
	auto aBaseLineId = attributes["aBaseLineId"];

	auto action = new GridTestRenderingAction();
	action->program = program;
	action->view = &_view;
	action->uProjection = uniforms["uProjection"];
	action->uNormalColor = uniforms["uNormalColor"];
	action->uGroupColor = uniforms["uGroupColor"];
	action->uAxisColor = uniforms["uAxisColor"];
	action->uNormalHalfWidth = uniforms["uNormalHalfWidth"];
	action->uGroupHalfWidth = uniforms["uGroupHalfWidth"];
	action->uAxisHalfWidth = uniforms["uAxisHalfWidth"];
	action->uGroupSize = uniforms["uGroupSize"];
	action->uLineOffset = uniforms["uLineOffset"];
	action->view = &_view;

	action->vao.Bind();
	action->vbo.Bind();

	aPositionOffset.Enable();
	aPositionOffset.Configure(&GridLineVertex::positionOffset);
	aAxisDirection.Enable();
	aAxisDirection.Configure(&GridLineVertex::axisDirection);
	aLineHalfLength.Enable();
	aLineHalfLength.Configure(&GridLineVertex::lineHalfLength);
	aBaseLineId.Enable();
	aBaseLineId.Configure(&GridLineVertex::baseLineId);

	action->vao.Unbind();

	GetPipeline()->Add(action);
}

void PointTestContext::_init_points_action()
{
	auto vShader = _shaders->Load(ShaderObject::Type::VERTEX, "points_v_2");
	auto vCompileResult = vShader->Compile();

	auto gShader = _shaders->Load(ShaderObject::Type::GEOMETRY, "points_g_3");
	auto gCompileResult = gShader->Compile();

	auto fShader = _shaders->Load(ShaderObject::Type::FRAGMENT, "points_f_1");
	auto fCompileResult = fShader->Compile();

	auto program = _shaders->GetPrograms()->GetOrCreate("points");
	//if (_sProgram->GetState() != ObjectState::READY)
	//{
	program->AttachShader(*vShader);
	program->AttachShader(*gShader);
	program->AttachShader(*fShader);
	auto linkResult = program->Link();
	//}

	auto attributes = program->GetAttributesMap();
	auto uniforms = program->GetUniformsMap();

	auto aColor = attributes["aColor"];
	auto aPosition = attributes["aPosition"];
	auto aSize = attributes["aSize"];

	auto action = new PointTestRenderingAction();
	action->program = program;
	action->view = &_view;
	action->uProjection = uniforms["uProjection"];
	action->uScale = uniforms["uScale"];
	action->view = &_view;

	std::vector<PointVertex> points;

	LFRL_COMMON::QuickRng rng;

	for (int i = 0; i < 10000; ++i)
	{
		auto sizeRand = rng.NextInt32(0, 3);
		auto size = sizeRand == 0 ? 3 : sizeRand == 1 ? 5 : 7;

		auto x = rng.NextFloat() * 200000.0f - 100000.0f;
		auto y = rng.NextFloat() * 200000.0f - 100000.0f;

		auto r = rng.NextFloat() * 0.4f;
		auto g = rng.NextFloat() * 0.4f;
		auto b = rng.NextFloat() * 0.4f;

		points.push_back({ glm::vec3(x, y, 0.0f), glm::vec4(0.5f + r, 0.5f + g, 0.5f + b, 1.0f), (float)size });
	}

	action->vao.Bind();
	action->vbo.Bind();

	action->vbo.SetData(points);

	aPosition.Enable();
	aPosition.Configure(&PointVertex::position);
	aColor.Enable();
	aColor.Configure(&PointVertex::color);
	aSize.Enable();
	aSize.Configure(&PointVertex::size);

	action->vao.Unbind();

	GetPipeline()->Add(action);
}

void PointTestContext::OnInitializing()
{
	base::OnInitializing();
	_timer.Initialize();
	_init_setup_action();
	_init_grid_action();
	_init_points_action();
}

void PointTestContext::OnDisposing()
{
	_timer.Dispose();
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
	_view.SetProjection(static_cast<GLfloat>(size.x), static_cast<GLfloat>(size.y));
	base::OnBoundsChanged(position, size);
}

END_LFRL_OGL_CG_NAMESPACE
