#ifndef INCLUDED_AEGIS_AFTS_ALIGNMENTOF_H
#define INCLUDED_AEGIS_AFTS_ALIGNMENTOF_H

#include <cstddef>

namespace afts {

template<int Size> struct AlignmentSize { static_assert(true, "Unsupported AlignmentSize"); };
template<> struct AlignmentSize<1> { typedef char Type; };
template<> struct AlignmentSize<2> { typedef short Type; };
template<> struct AlignmentSize<4> { typedef int Type; };
template<> struct AlignmentSize<8> { typedef long long Type; };
template<> struct AlignmentSize<16> { typedef long double Type; };

template<typename T>
struct AlignmentOf
{    
    struct TPlusChar { char c; T value; };
    
    enum { Size = offsetof(TPlusChar, value) };
    typedef typename AlignmentSize<Size>::Type Type;
};

} // namespace

#endif // INCLUDED
