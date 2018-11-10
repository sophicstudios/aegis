#include <agtc_spriteanimationcomponent.h>

namespace agtc {

SpriteAnimationComponent::SpriteAnimationComponent()
: m_framesPerSecond(30),
  m_numberOfFrames(0),
  m_currentFrame(0),
  m_step(1.0f / static_cast<float>(m_framesPerSecond)),
  m_accumulator(0.0f)
{}

SpriteAnimationComponent::~SpriteAnimationComponent()
{}

void SpriteAnimationComponent::update(double elapsedTime)
{
    // feed the accumulator
    m_accumulator += elapsedTime;

    // drain the accumulator until <= 0 and advance the animation frame
    while (m_accumulator >= m_step) {
        m_accumulator -= m_step;
        m_currentFrame += 1;
    }

    // Loop back to the beginning if necessary
    m_currentFrame %= m_numberOfFrames;
}

void SpriteAnimationComponent::framesPerSecond(size_t value)
{
    m_framesPerSecond = value;
    m_step = 1.0f / static_cast<float>(m_framesPerSecond);
}

void SpriteAnimationComponent::numberOfFrames(size_t value)
{
    m_numberOfFrames = value;
}

size_t SpriteAnimationComponent::currentFrame() const
{
    return m_currentFrame;
}

} // namespace
