#ifndef INCLUDED_AGTUI_SIZER_H
#define INCLUDED_AGTUI_SIZER_H

#include <agtm_size2d.h>

namespace agtui {

class Sizer
{
public:
    Sizer();
    
    virtual ~Sizer() = 0;
    
    agtm::Size2d<float> size() const;

    void size(agtm::Size2d<float> const& size);

    agtm::Size2d<float> minSize() const;

    agtm::Size2d<float> maxSize() const;

    agtm::Size2d<float> bestSize() const;

private:
    virtual agtm::Size2d<float> doSize() const = 0;

    virtual void doSize(agtm::Size2d<float> const& size) = 0;

    virtual agtm::Size2d<float> doMinSize() const = 0;

    virtual agtm::Size2d<float> doMaxSize() const = 0;

    virtual agtm::Size2d<float> doBestSize() const = 0;
};

} // namespace

#endif // INCLUDED
