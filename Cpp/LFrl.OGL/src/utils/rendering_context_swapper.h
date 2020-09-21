#ifndef __LFRL_OGL_RENDERING_CONTEXT_SWAPPER_GUARD__
#define __LFRL_OGL_RENDERING_CONTEXT_SWAPPER_GUARD__

#include "../context/RenderingContext.h"

BEGIN_LFRL_OGL_NAMESPACE

struct rendering_context_swapper final
{
	rendering_context_swapper(rendering_context_swapper const&) = delete;
	rendering_context_swapper& operator=(rendering_context_swapper const&) = delete;

	rendering_context_swapper();
	rendering_context_swapper(HDC hdc, HGLRC hglrc);
	explicit rendering_context_swapper(RenderingContext const& ctx);
	rendering_context_swapper(rendering_context_swapper&&) noexcept;
	rendering_context_swapper& operator=(rendering_context_swapper&&);
	~rendering_context_swapper() { swap_back(); }

	bool swapped() const noexcept { return _swapped; }
	HDC hdc() const noexcept { return _hdc; }
	HGLRC hglrc() const noexcept { return _hglrc; }
	HDC prev_hdc() const noexcept { return _prev_hdc; }
	HGLRC prev_hglrc() const noexcept { return _prev_hglrc; }

	bool swap_back();

private:
	bool _swapped;
	HDC _hdc;
	HGLRC _hglrc;
	HDC _prev_hdc;
	HGLRC _prev_hglrc;
};

END_LFRL_OGL_NAMESPACE

#endif
