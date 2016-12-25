#ifndef INCLUDED_AGTG_GL_H
#define INCLUDED_AGTG_GL_H

#include <afts_platform.h>

#if defined(AFTS_OS_IPHONE)

#define RENDERER_OPENGLES
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif defined(AFTS_OS_MACOS)

#define RENDERER_OPENGL
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#endif // AFTS_OS

#endif // INCLUDED
