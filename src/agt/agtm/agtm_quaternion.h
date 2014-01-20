#ifndef INCLUDED_AEGIS_AGTM_QUATERNION_H
#define INCLUDED_AEGIS_AGTM_QUATERNION_H

#include <afts_comparisonutil.h>
#include <algorithm>
#include <ostream>

namespace agtm {

template<typename T>
class Quaternion
{
public:
    Quaternion();
    
    Quaternion(T const& a, T const& b, T const& c, T const& d);
    
    Quaternion(T const* const arr, size_t length);
    
    Quaternion(Quaternion<T> const& q);

    ~Quaternion();

    Quaternion<T>& operator=(Quaternion const& q);
    
    void assign(T const& a, T const& b, T const& c, T const& d);
    
    void assign(T const* const arr, size_t length);

private:
    union {
        T m_arr[4];
        struct {
            T m_a;
            T m_b;
            T m_c;
            T m_d;
        };
    };
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Quaternion<T> const& quaternion);

} // namespace

#endif // INCLUDED
