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

void Visual2dComponent::mesh(MeshPtr mesh)
{
    m_mesh = mesh;
}

Visual2dComponent::MeshPtr Visual2dComponent::mesh() const
{
    return m_mesh;
}

void Visual2dComponent::material(Sprite2dMaterialPtr material)
{
    m_material = material;
}

Visual2dComponent::Sprite2dMaterialPtr Visual2dComponent::material() const
{
    return m_material;
}

void Visual2dComponent::draw(agtg::RenderingContext& renderingContext)
{
}

} // namespace
