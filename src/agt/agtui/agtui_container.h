#ifndef INCLUDED_AGTUI_CONTAINER_H
#define INCLUDED_AGTUI_CONTAINER_H

namespace agtui {

class Widget;

class Container : public agtui::Widget
{
public:
    typedef boost::shared_ptr<Widget> WidgetPtr;
    typedef std::vector<WidgetPtr> WidgetList;
    
    Container();
    
    virtual ~Container() = 0;
    
    virtual bool add(std::string const& id, ContainerPtr child) = 0;
    
    virtual ContainerPtr remove(std::string const& id);

    virtual const ContainerPtr child(std::string const& id);
    
    virtualz   v
    
    virtual void resize(size_t width, size_t height);
};

} // namespace

#endif // INCLUDED
