#include <aftu_stringref.h>
#include <aunit.h>

namespace aftu {

using namespace aunit;

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

describe("aftu_stringref", []
{
    it("Default Construction", [&]
    {
        StringRef<char> emptyref;

        expect(emptyref.isEmpty()).toBeTrue();
        expect(emptyref.size()).toEqual(0);
        expect(emptyref.begin()).toEqual(emptyref.end());
    });

    it("C string Construction", [&]
    {
        StringRef<char> cstringref(TestStrings<char>::S1);

        expect(cstringref.isEmpty()).non().toBeTrue();
        expect(cstringref.size()).toEqual(std::char_traits<char>::length(TestStrings<char>::S1));
        expect(&cstringref.begin()[0]).toEqual(&TestStrings<char>::S1[0]);
        expect(&cstringref.end()[0]).toEqual(&TestStrings<char>::S1[std::char_traits<char>::length(TestStrings<char>::S1)]);
    });

    it("basic_string Construction", [&]
    {
        StringRef<std::basic_string<char> > stlstringref(TestStrings<char>::S2);

        expect(stlstringref.isEmpty()).toBeTrue();
        expect(stlstringref.size()).toEqual(TestStrings<char>::S2.size());
        expect(&(*stlstringref.begin())).toEqual(&(*TestStrings<char>::S2.begin()));
        expect(&(*stlstringref.end())).toEqual(&(*TestStrings<char>::S2.end()));
    });

    it("Comparison", [&]
    {
        StringRef<char> cstringref(TestStrings<char>::S1);

        expect(cstringref).toEqual(TestStrings<char>::S1);
        
        StringRef<std::basic_string<char> > stlstringref(TestStrings<char>::S2);

        expect(stlstringref).toEqual(TestStrings<char>::S2);
    });
});

} // namespace
