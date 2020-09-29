#include "PointTestContext.h"

using namespace LFRL_OGL_CAPACITIES;

BEGIN_LFRL_OGL_CG_NAMESPACE

struct gridtest
{
	glm::vec2 positionOffset;
	glm::vec2 axisDirection;
	glm::float32 baseLineId;
};

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
		FaceCulling::Disable();
		//FaceCulling::Cull::SetBack();
		Sampling::Multi::Enable();
		Points::SetSize(4);
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
	std::vector<GridLineVertex>* gridLines;

protected:
	void OnInvoked() override
	{
		Depth::Test::Enable();

		program->Use();
		
		auto lineOffset = 10;

		uProjection.SetMat4(view->GetMatrix());
		uNormalColor.SetVec4(0.0f, 0.0f, 1.0f, 1.0f);
		uGroupColor.SetVec4(0.0f, 1.0f, 0.0f, 1.0f);
		uAxisColor.SetVec4(1.0f, 0.0f, 0.0f, 1.0f);
		//uNormalHalfWidth.Set(0.5f);
		//uGroupHalfWidth.Set(0.5f);
		//uAxisHalfWidth.Set(1.0f);
		uGroupSize.Set(5.0f);
		uLineOffset.Set((float)lineOffset);

		auto bounds = view->GetBounds();

		vbo.Bind();
		gridtest gt[2];
		gt[0].positionOffset = glm::vec2(0, bounds.GetCentreY());
		gt[0].axisDirection = glm::vec2(1, 0);
		gt[0].baseLineId = glm::ceil(bounds.GetLeft() / lineOffset) - 1;
		gt[1].positionOffset = glm::vec2(bounds.GetCentreX(), 0);
		gt[1].axisDirection = glm::vec2(0, 1);
		gt[1].baseLineId = glm::ceil(bounds.GetBottom() / lineOffset) - 1;
		vbo.SetData(gt);
		vbo.Unbind();

		auto xCount = (int)glm::ceil(bounds.GetWidth() / lineOffset) + 2;
		auto yCount = (int)glm::ceil(bounds.GetHeight() / lineOffset) + 2;

		vao.Bind();
		glDrawArraysInstanced(GL_POINTS, 0, 1, xCount);
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
	ShaderProgram* program;
	OrthogonalView* view;

protected:
	void OnInvoked() override
	{
		Depth::Test::Disable();

		program->Use();
		uProjection.SetMat4(view->GetMatrix());

		vao.Bind();
		glDrawArrays(GL_POINTS, 0, 3);
		vao.Unbind();

		program->Unuse();
	}
};

PointTestContext::PointTestContext(RenderingContext& rc, ShaderStore* shaders) noexcept
	: base(rc), _shaders(shaders), _timer(), _view(), _backgroundColor(), _clearBuffers(), _gridLines()
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
	//program->AttachShader(*gShader);
	program->AttachShader(*fShader);
	auto linkResult = program->Link();

	auto attributes = program->GetAttributesMap();
	auto uniforms = program->GetUniformsMap();

	auto aPositionOffset = attributes["aPositionOffset"];
	auto aAxisDirection = attributes["aAxisDirection"];
	//auto aLineHalfLength = attributes["aLineHalfLength"];
	auto aBaseLineId = attributes["aBaseLineId"];

	auto action = new GridTestRenderingAction();
	action->program = program;
	action->view = &_view;
	action->uProjection = uniforms["uProjection"];
	action->uNormalColor = uniforms["uNormalColor"];
	action->uGroupColor = uniforms["uGroupColor"];
	action->uAxisColor = uniforms["uAxisColor"];
	//action->uNormalHalfWidth = uniforms["uNormalHalfWidth"];
	//action->uGroupHalfWidth = uniforms["uGroupHalfWidth"];
	//action->uAxisHalfWidth = uniforms["uAxisHalfWidth"];
	action->uGroupSize = uniforms["uGroupSize"];
	action->uLineOffset = uniforms["uLineOffset"];
	action->view = &_view;
	action->gridLines = &_gridLines;

	_gridLines.push_back({ glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), 0 });
	//_gridLines.push_back({ glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 0), 0 });

	action->vao.Bind();
	action->vbo.Bind();

	aPositionOffset.Enable();
	aPositionOffset.Configure(sizeof(gridtest));
	aAxisDirection.Enable();
	aAxisDirection.Configure(sizeof(gridtest), sizeof(glm::vec2));
	//aLineHalfLength.Enable();
	//aLineHalfLength.Configure(sizeof(GridLineVertex), 2 * sizeof(glm::vec2));
	aBaseLineId.Enable();
	aBaseLineId.Configure(sizeof(gridtest), 2 * sizeof(glm::vec2));

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
	action->view = &_view;

	std::vector<PointVertex> points;
	points.push_back({ glm::vec3(100, 50, 0), glm::vec4(1, 1, 1, 1), 7 });
	points.push_back({ glm::vec3(80, 270, 0), glm::vec4(1, 0, 0, 1), 4 });
	points.push_back({ glm::vec3(220, 140, 0), glm::vec4(0, 1, 1, 1), 12 });

	action->vao.Bind();
	action->vbo.Bind();

	action->vbo.SetData(points);

	aPosition.Enable();
	aPosition.Configure(sizeof(PointVertex));
	aColor.Enable();
	aColor.Configure(sizeof(PointVertex), sizeof(glm::vec3));
	aSize.Enable();
	aSize.Configure(sizeof(PointVertex), sizeof(glm::vec3) + sizeof(glm::vec4));

	action->vao.Unbind();

	GetPipeline()->Add(action);
}

void PointTestContext::OnInitializing()
{
	base::OnInitializing();
	_timer.Initialize();
	_view.Translate(70, 0);
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
	_view.MoveTo(-50.0f, -120.0f, 0.5f, 0.5f);
	base::OnBoundsChanged(position, size);
}

END_LFRL_OGL_CG_NAMESPACE
