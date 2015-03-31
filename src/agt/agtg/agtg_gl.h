#ifndef INCLUDED_AGTG_GL_H
#define INCLUDED_AGTG_GL_H

#include <afts_platform.h>

#if defined(AFTS_OS_IPHONE)

#define RENDERER_OPENGLES
#include <OpenGLES/ES2/gl.h>

#elif defined(AFTS_OS_MACOS)

#define RENDERER_OPENGL
#include <OpenGL/gl.h>

#endif // AFTS_OS

namespace agtg {

} // namespace

#endif // INCLUDED
