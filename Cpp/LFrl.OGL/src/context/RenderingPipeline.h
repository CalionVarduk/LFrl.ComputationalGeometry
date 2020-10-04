#ifndef __LFRL_OGL_RENDERING_PIPELINE_GUARD__
#define __LFRL_OGL_RENDERING_PIPELINE_GUARD__

#include <vector>
#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

struct IRenderingAction
{
	IRenderingAction(IRenderingAction const&) = delete;
	IRenderingAction& operator=(IRenderingAction const&) = delete;

	virtual ~IRenderingAction() { Disable(); }

	bool IsEnabled() const noexcept { return _isEnabled; }
	void Enable(bool enable = true) noexcept { _isEnabled = enable; }
	void Disable(bool disable = true) noexcept { Enable(!disable); }

	void Invoke();

protected:
	IRenderingAction() noexcept;
	IRenderingAction(IRenderingAction&&) noexcept;
	IRenderingAction& operator=(IRenderingAction&&) noexcept;

	virtual void OnInvoked() = 0;

private:
	bool _isEnabled;
};

class RenderingPipeline final
{
	friend class GLCanvasContext;

	RenderingPipeline(RenderingPipeline const&) = delete;
	RenderingPipeline& operator=(RenderingPipeline const&) = delete;

public:
	RenderingPipeline();
	RenderingPipeline(RenderingPipeline&&);
	RenderingPipeline& operator=(RenderingPipeline&&);
	~RenderingPipeline() { Clear(); }

	LFRL_COMMON::sz GetActionCount() const noexcept { return _actions.size(); }
	IRenderingAction* GetActionAt(LFRL_COMMON::u32 index) { return _actions[index]; }
	IRenderingAction const* GetActionAt(LFRL_COMMON::u32 index) const { return _actions[index]; }

	void Add(IRenderingAction* action);
	bool Remove(IRenderingAction const* action);
	void Clear();

	void Run();

private:
	std::vector<IRenderingAction*> _actions;
};

END_LFRL_OGL_NAMESPACE

#endif
