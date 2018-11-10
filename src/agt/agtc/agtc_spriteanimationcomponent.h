#ifndef INCLUDED_AEGIS_AGTC_SPRITEANIMATIONCOMPONENT_H
#define INCLUDED_AEGIS_AGTC_SPRITEANIMATIONCOMPONENT_H

#include <agtm_size2d.h>

namespace agtc {

class SpriteAnimationComponent
{
public:
    SpriteAnimationComponent();

    ~SpriteAnimationComponent();

    void update(double elapsedTime);

    void framesPerSecond(size_t value);

    void numberOfFrames(size_t value);

    size_t currentFrame() const;

private:
    size_t m_framesPerSecond;
    size_t m_numberOfFrames;
    size_t m_currentFrame;
    float m_step;
    float m_accumulator;
};

} // namespace

#endif // INCLUDED
