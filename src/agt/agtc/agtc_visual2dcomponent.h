#ifndef INCLUDED_AGTC_VISUAL2DCOMPONENT_H
#define INCLUDED_AGTC_VISUAL2DCOMPONENT_H

#include <agtg_renderingcontext.h>

namespace agtc {

class Visual2dComponent
{
public:
    Visual2dComponent();

    virtual ~Visual2dComponent() = 0;

    virtual void draw(agtg::RenderingContext& renderingContext) = 0;
};

} // namespace

#endif // INCLUDED
