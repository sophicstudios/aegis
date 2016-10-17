#include <afts_comparisonutil.h>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>

namespace afts {

namespace {

union FloatInt
{
    float f;
    int32_t i;
};

union DoubleInt
{
    double d;
    struct {
        int32_t hi;
        int32_t lo;
    } i;
};

double ulp(double x)
{
    int exp;
    std::frexp(x, &exp);
    return ldexp(0.5, exp-52);
}

inline bool equalULPImp(float lhs, float rhs, unsigned int maxULP)
{
    assert(sizeof(int32_t) == sizeof(float));
    
    // make sure maxULP is small enough so that the default NaN won't compare to anything
    assert(maxULP < 4 * 1024 * 1024);

    if (lhs == rhs) {
        return true;
    }
    
    FloatInt fi1, fi2;
    fi1.f = lhs;
    fi2.f = rhs;
    
    if (fi1.i < 0) {
        fi1.i = fi1.i - 0x80000000;
    }
    
    if (fi2.i < 0) {
        fi2.i = fi2.i - 0x80000000;
    }
    
    unsigned int intDiff = std::abs(fi1.i - fi2.i);
    if (intDiff <= maxULP) {
        return true;
    }
    
    return false;
}

bool equalULPImp(double lhs, double rhs, unsigned int maxULP)
{
    assert(sizeof(int32_t) == sizeof(float));

    if (lhs == rhs) {
        return true;
    }
    
    return lhs - rhs <= maxULP * ulp(lhs);
/*    
    DoubleInt fi1, fi2;
    fi1.d = lhs;
    fi2.d = rhs;
    
    unsigned int hiDiff = std::abs(fi1.i.hi - fi2.i.hi);
    unsigned int loDiff = std::abs(fi1.i.lo - fi2.i.lo);
    if (hiDiff <= maxULP && loDiff <= maxULP) {
        return true;
    }
    
    return false;
*/
}

} // namespace


unsigned int ComparisonUtil::DEFAULT_MAX_ULP = 2;

void ComparisonUtil::setDefaultMaxULP(unsigned int maxULP)
{
    ComparisonUtil::DEFAULT_MAX_ULP = maxULP;
}

template<>
bool ComparisonUtil::equal<float>(float const& lhs, float const& rhs)
{
    return lhs == rhs;
}

template<>
bool ComparisonUtil::equal<double>(double const& lhs, double const& rhs)
{
    return lhs == rhs;
}

template<>
bool ComparisonUtil::equalAbsolute<float>(float lhs, float rhs, float absoluteEpsilon)
{
    if (lhs == rhs) {
        return true;
    }
    
    return std::fabs(lhs - rhs) < absoluteEpsilon;
}

template<>
bool ComparisonUtil::equalAbsolute<double>(double lhs, double rhs, double absoluteEpsilon)
{
    if (lhs == rhs) {
        return true;
    }

    return std::fabs(lhs - rhs) < absoluteEpsilon;
}

template<>
bool ComparisonUtil::equalRelative<float>(float lhs, float rhs, float maxRelativeError)
{
    if (lhs == rhs) {
        return true;
    }
    
    return std::fabs(lhs - rhs) / (std::fabs(lhs) + std::fabs(rhs)) < maxRelativeError;
}

template<>
bool ComparisonUtil::equalRelative<double>(double lhs, double rhs, double maxRelativeError)
{
    if (lhs == rhs) {
        return true;
    }
    
    return std::fabs(lhs - rhs) / (std::fabs(lhs) + std::fabs(rhs)) < maxRelativeError;
}

template<>
bool ComparisonUtil::equalULP<float>(float lhs, float rhs)
{
    return equalULPImp(lhs, rhs, ComparisonUtil::DEFAULT_MAX_ULP);
}

template<>
bool ComparisonUtil::equalULP<float>(float lhs, float rhs, unsigned int maxULP)
{
    return equalULPImp(lhs, rhs, maxULP);
}

template<>
bool ComparisonUtil::equalULP<double>(double lhs,double rhs)
{
    return equalULPImp(lhs, rhs, ComparisonUtil::DEFAULT_MAX_ULP);
}

template<>
bool ComparisonUtil::equalULP<double>(double lhs, double rhs, unsigned int maxULP)
{
    return equalULPImp(lhs, rhs, maxULP);
}

} // namespace
