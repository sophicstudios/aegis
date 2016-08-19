#include <aftu_stringutil.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace aftu;

Describe d("aftu_stringutil", []
{
    it("trimLeft", [&]
    {
        std::string s1("xxxmy string");
        std::string s2("my string");

        aftu::StringUtil::trimLeft(&s1, 'x');
        aftu::StringUtil::trimLeft(&s2, 'x');

        expect(s1).toEqual(s2);
    });

    it("trimRight", [&]
    {
        std::string s1("my stringxxx");
        std::string s2("my string");

        aftu::StringUtil::trimRight(&s1, 'x');
        aftu::StringUtil::trimRight(&s2, 'x');

        expect(s1).toEqual(s2);
    });

    it("trim", [&]
    {
        std::string s1("xxxmy stringxxx");
        std::string s2("my string");

        aftu::StringUtil::trim(&s1, 'x');
        aftu::StringUtil::trim(&s2, 'x');

        expect(s1).toEqual(s2);
    });

    it("tokenize", [&]
    {
        std::vector<std::string> tokenList1;
        std::vector<std::string> tokenList2;

        std::string s1("0");
        aftu::StringUtil::tokenize(&tokenList1, s1);

        expect(tokenList1.size()).toEqual(1);
        expect(tokenList1[0]).toEqual("0");

        tokenList1.clear();
        
        std::string s2("0 1");
        aftu::StringUtil::tokenize(&tokenList1, s2);

        expect(tokenList1.size()).toEqual(2);
        expect(tokenList1[0]).toEqual("0");
        expect(tokenList1[1]).toEqual("1");

        tokenList1.clear();
        
        std::string s3("0;1");
        aftu::StringUtil::tokenize(&tokenList1, s3, ';');

        expect(tokenList1.size()).toEqual(2);
        expect(tokenList1[0]).toEqual("0");
        expect(tokenList1[1]).toEqual("1");
        
        tokenList1.clear();

        std::string s4("0;;2");
        aftu::StringUtil::tokenize(&tokenList1, s4, ';', true);

        expect(tokenList1.size()).toEqual(3);
        expect(tokenList1[0]).toEqual("0");
        expect(tokenList1[1]).toEqual("");
        expect(tokenList1[2]).toEqual("2");
        
        tokenList1.clear();
        
        std::string s5(";1;;3;");
        aftu::StringUtil::tokenize(&tokenList1, s5, ';', true);

        expect(tokenList1.size()).toEqual(5);
        expect(tokenList1[0]).toEqual("");
        expect(tokenList1[1]).toEqual("1");
        expect(tokenList1[2]).toEqual("");
        expect(tokenList1[3]).toEqual("3");
        expect(tokenList1[4]).toEqual("");
    });
});

} // namespace
