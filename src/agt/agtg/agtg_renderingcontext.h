#ifndef INCLUDED_AEGIS_AGTG_RENDERINGCONTEXT_H
#define INCLUDED_AEGIS_AGTG_RENDERINGCONTEXT_H

#include <agtg_shaderprogram.h>
#include <memory>

namespace agtg {

class RenderingContext
{
public:
    typedef std::shared_ptr<agtg::ShaderProgram> ShaderProgramPtr;

    RenderingContext();
    
    virtual ~RenderingContext() = 0;
    
    virtual void makeCurrent() = 0;

    virtual ShaderProgramPtr createShader() = 0;

    virtual void preRender() = 0;
    
    virtual void postRender() = 0;
};

} // namespace

#endif // INCLUDED
