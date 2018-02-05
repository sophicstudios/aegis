#include <agtc_visual2dcomponent.h>
#include <aftu_url.h>
#include <string>

namespace agtc {

namespace {

} // namespace

Visual2dComponent::Visual2dComponent()
: m_id(afth::UUID::v4())
{
}

Visual2dComponent::~Visual2dComponent()
{}

afth::UUID const& Visual2dComponent::id() const
{
    return m_id;
}

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

} // namespace
