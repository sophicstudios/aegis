#ifndef INCLUDED_AEGIS_AFTM_ROUND_H
#define INCLUDED_AEGIS_AFTM_ROUND_H

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <limits>
#include <cmath>

// @PURPOSE
// Provides an assortment of standard rounding algorithms.
//
// @DESCRIPTION
// This component contains rounding algorithms that can be used
// with floating point types, including float, double, and long double.
// The following algorithms are included:
//
// halfUp:     0 1 2 3 4 5 6 7 8 9 0
//             |<------| |-------->|
//  
// halfDown:   0 1 2 3 4 5 6 7 8 9 0
//             |<--------| |------>|
//
// @CLASSES
// aflm_Round
//
// @AUTHOR
// Lyell Haynes

namespace aftm {

struct Round
{
    template<typename T>
    static T halfUp(T value, int decimals);

    template<typename T>
    static T halfDown(T value, int decimals);
};

template<typename T>
T Round::halfUp(T value, int decimals)
{
    //BOOST_STATIC_ASSERT(typename boost:type_traits::is_floating_point<T>::value);
    T factor = std::pow(static_cast<T>(10), decimals);
    T result = std::floor((std::fabs(value) * factor) + (static_cast<T>(0.5) + std::numeric_limits<T>::epsilon())) / factor;
    return (value < static_cast<T>(0.0) ? -result : result);
}

template<typename T>
T Round::halfDown(T value, int decimals)
{
    //BOOST_STATIC_ASSERT(typename boost::type_traits::is_floating_point<T>::value);
    T factor = std::pow(static_cast<T>(10), decimals);
    T result = std::ceil((std::fabs(value) * factor) - (static_cast<T>(0.5) + std::numeric_limits<T>::epsilon())) / factor;
    return (value < static_cast<T>(0.0) ? -result : result);
}

} // namespace

#endif // INCLUDED
