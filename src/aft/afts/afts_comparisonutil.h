#ifndef INCLUDED_AEGIS_AFTS_COMPARISONUTIL_H
#define INCLUDED_AEGIS_AFTS_COMPARISONUTIL_H

namespace afts {

struct ComparisonUtil
{
    static unsigned int DEFAULT_MAX_ULP;
    
    static void setDefaultMaxULP(unsigned int maxULP);
    
    /**
     * 
     */
    template<typename T>
    static bool equal(T const& lhs, T const& rhs);
    
    /**
     * Compares the first and seconds parameters using an absolute
     * epsilon value. Returns true if the numbers are equal and false if
     * they are not equal.
     */
    template<typename T>
    static bool equalAbsolute(T lhs, T rhs, T absoluteEpsilon);
    
    /**
     * Compares lhs to rhs using a relative percentage comparison, where
     * the difference between the two numbers as a percentage of the first
     * number can not be more than the error value in order for the two numbers
     * to compare as equal. Returns true if the numbers are equal and false
     * if they are not equal.
     */
    template<typename T>
    static bool equalRelative(T lhs, T rhs, T maxRelativeError);
    
    template<typename T>
    static bool equalULP(T lhs, T rhs);
    
    /**
     * Compares lhs to rhs using the Unit in Last Place (ULP). Returns true
     * if the values are equal and false if they are not equal.
     */
    template<typename T>
    static bool equalULP(T lhs, T rhs, unsigned int maxULP);
};

template<typename T>
inline bool ComparisonUtil::equal(T const& lhs, T const& rhs)
{
    return lhs == rhs;
}

template<typename T>
inline bool ComparisonUtil::equalAbsolute(T lhs, T rhs, T absoluteEpsilon)
{
    return lhs == rhs;
}

template<typename T>
inline bool ComparisonUtil::equalRelative(T lhs, T rhs, T maxRelativeError)
{
    return lhs == rhs;
}

template<typename T>
inline bool ComparisonUtil::equalULP(T lhs, T rhs)
{
    return lhs == rhs;
}

template<typename T>
inline bool ComparisonUtil::equalULP(T lhs, T rhs, unsigned int maxULP)
{
    return lhs == rhs;
}

template<>
bool ComparisonUtil::equal<float>(float const& lhs, float const& rhs);

template<>
bool ComparisonUtil::equal<double>(double const& lhs, double const& rhs);

template<>
bool ComparisonUtil::equalAbsolute<float>(float lhs, float rhs, float absoluteEpsilon);

template<>
bool ComparisonUtil::equalRelative<float>(float lhs, float rhs, float maxRelativeError);

template<>
bool ComparisonUtil::equalULP<float>(float lhs, float rhs);

template<>
bool ComparisonUtil::equalULP<float>(float lhs, float rhs, unsigned int maxULP);

template<>
bool ComparisonUtil::equalAbsolute<double>(double lhs, double rhs, double absoluteEpsilon);

template<>
bool ComparisonUtil::equalRelative<double>(double lhs, double rhs, double maxRelativeError);

template<>
bool ComparisonUtil::equalULP<double>(double lhs, double rhs);

template<>
bool ComparisonUtil::equalULP<double>(double lhs, double rhs, unsigned int maxULP);

} // namespace

#endif // INCLUDED
