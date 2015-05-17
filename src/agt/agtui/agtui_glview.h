#ifndef INCLUDED_AGTUI_GLVIEW_H
#define INCLUDED_AGTUI_GLVIEW_H

#include <agtui_widget.h>

namespace agtui {

class GLView : public agtui::Widget
{
public:
    GLView();

    virtual ~GLView();

protected:
    virtual agtm::Size2d<float> doMinSize() const;

    virtual agtm::Size2d<float> doMaxSize() const;

    virtual agtm::Size2d<float> doPreferredSize() const;

private:
};

} // namespace

#endif // INCLUDED
