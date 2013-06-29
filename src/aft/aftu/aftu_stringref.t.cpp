#include <aftu_stringref.h>
#include <aunit.h>

namespace aegis {
namespace aftu {

template<typename T>
struct TestStrings;

template<>
struct TestStrings<char>
{
    static const char* S1;
    static const std::string S2;
};

const char* TestStrings<char>::S1 = "Test C String";
const std::string TestStrings<char>::S2("Test std::string");

template<>
struct TestStrings<wchar_t>
{
    static const wchar_t* S1;
    static const std::wstring S2;
};

const wchar_t* TestStrings<wchar_t>::S1 = L"Test C String";
const std::wstring TestStrings<wchar_t>::S2(L"Test std::wstring");

class TestStringRef : public aunit::TestFixture
{
public:
    TestStringRef() {}
    
    virtual ~TestStringRef() {}
    
protected:
    virtual void runTest();

private:
    template<typename T>
    void testConstruction(TestStrings<T> const& testStrings);
    
    template<typename T>
    void testComparison(TestStrings<T> const& testStrings);
};

AUNIT_REGISTERTEST(TestStringRef);

void TestStringRef::runTest()
{
    testConstruction(TestStrings<char>());
    testConstruction(TestStrings<wchar_t>());
    testComparison(TestStrings<char>());
    testComparison(TestStrings<wchar_t>());
}

template<typename T>
void TestStringRef::testConstruction(TestStrings<T> const& testStrings)
{
    StringRef<T> emptyref;
    AUNIT_ASSERT(emptyref.isEmpty());
    AUNIT_ASSERT(emptyref.size() == 0);
    AUNIT_ASSERT(emptyref.begin() == emptyref.end());

    StringRef<T> cstringref(TestStrings<T>::S1);
    AUNIT_ASSERT(!cstringref.isEmpty());
    AUNIT_ASSERT(cstringref.size() == std::char_traits<T>::length(TestStrings<T>::S1));
    AUNIT_ASSERT(&cstringref.begin()[0] == &TestStrings<T>::S1[0]
        && &cstringref.end()[0] == &TestStrings<T>::S1[std::char_traits<T>::length(TestStrings<T>::S1)]);
    
    StringRef<std::basic_string<T> > stlstringref(TestStrings<T>::S2);
    AUNIT_ASSERT(!stlstringref.isEmpty());
    AUNIT_ASSERT(stlstringref.size() == TestStrings<T>::S2.size());
    AUNIT_ASSERT(&(*stlstringref.begin()) == &(*TestStrings<T>::S2.begin())
        && &(*stlstringref.end()) == &(*TestStrings<T>::S2.end()));
}

template<typename T>
void TestStringRef::testComparison(TestStrings<T> const& testStrings)
{
    StringRef<T> cstringref(TestStrings<T>::S1);
    AUNIT_ASSERT(cstringref == TestStrings<T>::S1);
    
    StringRef<std::basic_string<T> > stlstringref(TestStrings<T>::S2);
    AUNIT_ASSERT(stlstringref == TestStrings<T>::S2);
}

} // namespace
} // namespace
