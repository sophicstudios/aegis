#include <agta_material.h>

namespace agta {

Material::Material()
: m_id(afth::UUID::v4())
{
}

Material::~Material()
{}

afth::UUID const& Material::id() const
{
    return m_id;
}

} // namespace
