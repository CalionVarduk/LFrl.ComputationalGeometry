#ifndef __LFRL_CG_API_API_MACROS_GUARD__
#define __LFRL_CG_API_API_MACROS_GUARD__

#include <Windows.h>

#if defined(LFRL_CG_API_EXPORTS)
#define LFRL_CG_API_DECLSPEC __declspec(dllexport)
#else
#define LFRL_CG_API_DECLSPEC __declspec(dllimport)
#endif

#define LFRL_CG_API_CALLDECL __cdecl
#define LFRL_CG_API_ENTRY(RETURN_TYPE) LFRL_CG_API_DECLSPEC RETURN_TYPE LFRL_CG_API_CALLDECL

#define BEGIN_LFRL_CG_API extern "C" {
#define END_LFRL_CG_API }

#endif
