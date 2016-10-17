#ifndef INCLUDED_AEGIS_AGTG_RENDERINGCONTEXT_H
#define INCLUDED_AEGIS_AGTG_RENDERINGCONTEXT_H

namespace agtg {

class RenderingContext
{
public:
    RenderingContext();
    
    virtual ~RenderingContext() = 0;
    
    virtual void makeCurrent() = 0;

    virtual void preRender() = 0;
    
    virtual void postRender() = 0;
};

} // namespace

#endif // INCLUDED
