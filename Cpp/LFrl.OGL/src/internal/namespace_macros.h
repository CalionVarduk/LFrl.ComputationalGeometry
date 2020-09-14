#ifndef __LFRL_OGL_NAMESPACE_MACROS_GUARD__
#define __LFRL_OGL_NAMESPACE_MACROS_GUARD__

#include "include/glew/src/glew.h"
#include "include/glew/src/wglew.h"
#include "include/glm/src/glm.hpp"
#include "include/glm/src/gtc/type_ptr.hpp"
#include "LFrl.Common/src/internal/namespace_macros.h"

#define BEGIN_LFRL_OGL_NAMESPACE BEGIN_LFRL_NAMESPACE namespace OGL {
#define END_LFRL_OGL_NAMESPACE }END_LFRL_NAMESPACE
#define LFRL_OGL LFRL::OGL

#define BEGIN_LFRL_OGL_WND_NAMESPACE BEGIN_LFRL_OGL_NAMESPACE namespace Wnd {
#define END_LFRL_OGL_WND_NAMESPACE }END_LFRL_OGL_NAMESPACE
#define LFRL_OGL_WND LFRL_OGL::Wnd

#endif
