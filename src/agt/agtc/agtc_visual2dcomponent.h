#ifndef INCLUDED_AEGIS_AGTC_VISUAL2dCOMPONENT_H
#define INCLUDED_AEGIS_AGTC_VISUAL2dCOMPONENT_H

#include <afth_uuid.h>

namespace agtc {

class Visual2dComponent
{
public:
    Visual2dComponent();

    ~Visual2dComponent();

    afth::UUID const& id() const;

    void shaderId(size_t shaderId);

    size_t shaderId() const;

    void meshId(size_t meshId);

    size_t meshId() const;

    void materialId(size_t materialId);

    size_t materialId() const;
    
private:
    afth::UUID m_id;
    size_t m_shaderId;
    size_t m_meshId;
    size_t m_materialId;
};

bool operator<(Visual2dComponent const& lhs, Visual2dComponent const& rhs);

} // namespace

#endif // INCLUDED
