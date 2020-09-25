#include "RenderingPipeline.h"

BEGIN_LFRL_OGL_NAMESPACE

void IRenderingAction::Invoke()
{
	if (!_isEnabled)
		return;

	OnInvoked();
}

IRenderingAction::IRenderingAction() noexcept
	: _isEnabled(true)
{}

RenderingPipeline::RenderingPipeline()
	: _actions()
{}

void RenderingPipeline::Add(IRenderingAction* action)
{
	if (action == nullptr)
		return;

	_actions.push_back(action);
}

bool RenderingPipeline::Remove(IRenderingAction const* action)
{
	auto size = GetActionCount();
	for (LFRL_COMMON::sz i = 0; i < size; ++i)
	{
		if (_actions[i] == action)
		{
			delete action;
			_actions.erase(_actions.begin() + i);
			return true;
		}
	}
	return false;
}

void RenderingPipeline::Clear()
{
	for (auto action : _actions)
		delete action;

	_actions.clear();
}

void RenderingPipeline::Run()
{
	for (auto action : _actions)
		action->Invoke();
}

END_LFRL_OGL_NAMESPACE
