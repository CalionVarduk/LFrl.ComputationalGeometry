#include "rendering_context_swapper.h"

BEGIN_LFRL_OGL_NAMESPACE

bool __init_ctx_swapper(HDC hdc, HGLRC hglrc, HDC& prevHdc, HGLRC& prevHglrc)
{
	prevHglrc = wglGetCurrentContext();
	
	if (hglrc == prevHglrc)
	{
		prevHdc = hdc;
		return false;
	}

	prevHdc = wglGetCurrentDC();
	return wglMakeCurrent(hdc, hglrc);
}

rendering_context_swapper::rendering_context_swapper()
	: _hdc(NULL), _hglrc(NULL), _prev_hdc(NULL), _prev_hglrc(NULL), _swapped(false)
{}

rendering_context_swapper::rendering_context_swapper(HDC hdc, HGLRC hglrc)
	: _hdc(hdc), _hglrc(hglrc), _prev_hdc(NULL), _prev_hglrc(NULL), _swapped(false)
{
	_swapped = __init_ctx_swapper(_hdc, _hglrc, _prev_hdc, _prev_hglrc);
}

rendering_context_swapper::rendering_context_swapper(RenderingContext const& ctx)
	: _hdc(ctx.GetDeviceContext()->GetHdc()), _hglrc(ctx.GetHglrc()), _prev_hdc(NULL), _prev_hglrc(NULL), _swapped(false)
{
	_swapped = __init_ctx_swapper(_hdc, _hglrc, _prev_hdc, _prev_hglrc);
}

rendering_context_swapper::rendering_context_swapper(rendering_context_swapper&& other) noexcept
	: _hdc(other._hdc), _hglrc(other._hglrc), _prev_hdc(other._prev_hdc), _prev_hglrc(other._prev_hglrc), _swapped(other._swapped)
{
	other._hdc = NULL;
	other._hglrc = NULL;
	other._prev_hdc = NULL;
	other._prev_hglrc = NULL;
	other._swapped = false;
}

rendering_context_swapper& rendering_context_swapper::operator=(rendering_context_swapper&& other)
{
	if (this != &other)
	{
		_hdc = other._hdc;
		_hglrc = other._hglrc;
		_prev_hdc = other._hdc;
		_prev_hglrc = other._prev_hglrc;
		_swapped = other._swapped;

		other._hdc = NULL;
		other._hglrc = NULL;
		other._prev_hdc = NULL;
		other._prev_hglrc = NULL;
		other._swapped = false;

		if (_swapped)
		{
			auto currentHglrc = wglGetCurrentContext();
			if (currentHglrc != _hglrc && !wglMakeCurrent(_hdc, _hglrc))
			{
				if (currentHglrc != _prev_hglrc)
					wglMakeCurrent(_prev_hdc, _prev_hglrc);

				_swapped = false;
			}
		}		
	}
	return *this;
}

bool rendering_context_swapper::swap_back()
{
	if (_swapped)
	{
		auto result = _prev_hglrc == NULL ?
			wglMakeCurrent(NULL, NULL) :
			wglMakeCurrent(_prev_hdc, _prev_hglrc);

		_swapped = false;
		return result;
	}
	return false;
}

END_LFRL_OGL_NAMESPACE
