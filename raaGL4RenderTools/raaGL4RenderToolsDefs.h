#pragma once
#ifndef RAAGL4RENDERTOOLSDEFS
#define RAAGL4RENDERTOOLSDEFS

#ifdef _WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAAGL4RENDERTOOLS
#define RAAGL4RENDERTOOLS_DLL_DEF
#else
#ifdef RAAGL4RENDERTOOLS_EXPORTS
#define RAAGL4RENDERTOOLS_DLL_DEF __declspec(dllexport)
#else
#define RAAGL4RENDERTOOLS_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaGL4RenderToolsD")
#else
#pragma comment(lib,"raaGL4RenderToolsR")
#endif
#endif 
#endif
#else
#define RAAGL4RENDERTOOLS_DLL_DEF
#endif

#endif