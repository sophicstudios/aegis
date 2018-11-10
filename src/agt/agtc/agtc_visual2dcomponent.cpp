#include <agtc_visual2dcomponent.h>
#include <aftu_url.h>
#include <string>

namespace agtc {

namespace {

} // namespace

Visual2dComponent::Visual2dComponent()
{}

Visual2dComponent::~Visual2dComponent()
{}

void Visual2dComponent::shaderId(size_t shaderId)
{
    m_shaderId = shaderId;
}

size_t Visual2dComponent::shaderId() const
{
    return m_shaderId;
}

void Visual2dComponent::meshId(size_t meshId)
{
    m_meshId = meshId;
}

size_t Visual2dComponent::meshId() const
{
    return m_meshId;
}

void Visual2dComponent::materialId(size_t materialId)
{
    m_materialId = materialId;
}

size_t Visual2dComponent::materialId() const
{
    return m_materialId;
}

void Visual2dComponent::spriteSize(agtm::Size2d<float> const& size)
{
    m_spriteSize = size;
}

agtm::Size2d<float> Visual2dComponent::spriteSize() const
{
    return m_spriteSize;
}

void Visual2dComponent::spriteOffset(agtm::Vector2<float> const& offset)
{
    m_spriteOffset = offset;
}

agtm::Vector2<float> Visual2dComponent::spriteOffset() const
{
    return m_spriteOffset;
}

} // namespace
