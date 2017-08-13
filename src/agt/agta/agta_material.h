#ifndef INCLUDED_AGTA_MATERIAL_H
#define INCLUDED_AGTA_MATERIAL_H

#include <afth_uuid.h>
#include <memory>

namespace agta {

class Material
{
public:
    Material();

    ~Material();

    afth::UUID const& id() const;

private:
    afth::UUID m_id;
};

} // namespace

#endif // INCLUDED
