#ifndef INCLUDE_AULW_FRAME_H
#define INCLUDE_AULW_FRAME_H

#include <aulp_rectangle.h>
#include <string>

namespace aegis {
namespace aulw {

class Frame
{
public:
    enum Message {
        Message_Create,
        Message_Show,
        Message_Hide,
        Message_Destroy
    };
    
    Frame(std::string const& title, aulp::Rectangle const& rect);
    
    Frame(std::string const& title, size_t x, size_t y, size_t width, size_t height);
    
    Frame(std::string const& title, size_t width, size_t height);
    
    ~Frame();
    
    void move(aulp::Point const& position);
    
    void resize(size_t width, size_t height);
};

} // namespace
} // namespace

#endif // INCLUDE
