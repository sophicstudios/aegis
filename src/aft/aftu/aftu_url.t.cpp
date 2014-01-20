#include <aunit.h>
#include <aftu_url.h>
#include <iostream>

namespace aftu {

class TestUrl : public aunit::TestFixture
{
public:
    TestUrl() {}
    
    virtual ~TestUrl() {}
    
protected:
    virtual void runTest();

private:
    void testHttpConstruction();
    void testFileConstruction();
    
    void checkUrl(
        std::string const& urlStr,
        bool isValid,
        std::string const& scheme,
        std::string const& authority,
        std::string const& path,
        std::string const& query,
        std::string const& fragment);
};

AUNIT_REGISTERTEST(TestUrl);

void TestUrl::runTest()
{
    testHttpConstruction();
    testFileConstruction();
}

void TestUrl::checkUrl(
    std::string const& urlStr,
    bool isValid,
    std::string const& scheme,
    std::string const& authority,
    std::string const& path,
    std::string const& query,
    std::string const& fragment)
{
    URL url(urlStr);
    AUNIT_ASSERT(url.isValid() == isValid);
    
    if (isValid) {
        AUNIT_ASSERT(url.scheme() == scheme);
        
        AUNIT_ASSERT(url.hasAuthority() == !authority.empty());
        AUNIT_ASSERT(url.authority() == authority);
        
        AUNIT_ASSERT(url.path() == path);
        
        AUNIT_ASSERT(url.hasQuery() == !query.empty());
        AUNIT_ASSERT(url.query() == query);
        
        AUNIT_ASSERT(url.hasFragment() == !fragment.empty());
        AUNIT_ASSERT(url.fragment() == fragment);
    }
}

void TestUrl::testHttpConstruction()
{
    checkUrl("", false, "", "", "", "", "");
    checkUrl("http://www.google.com", true, "http", "www.google.com", "", "", "");
    checkUrl("http://www.google.com/", true, "http", "www.google.com", "/", "", "");
    checkUrl("http://www.google.com/search", true, "http", "www.google.com", "/search", "", "");
    checkUrl("http://www.google.com/search/", true, "http", "www.google.com", "/search/", "", "");
    checkUrl("http://www.google.com/search?term=test", true, "http", "www.google.com", "/search", "term=test", "");
    checkUrl("http://www.google.com/search?term=test#ref", true, "http", "www.google.com", "/search", "term=test", "ref");
}

void TestUrl::testFileConstruction()
{
    checkUrl("file://localhost/usr/local", true, "file", "localhost", "/usr/local", "", "");
    checkUrl("file://localhost/usr/local/", true, "file", "localhost", "/usr/local/", "", "");
    checkUrl("file:///usr/local", true, "file", "", "/usr/local", "", "");
    checkUrl("file:///local/file.txt", true, "file", "", "/local/file.txt", "", "");
    checkUrl("file.txt", true, "", "", "file.txt", "", "");
    checkUrl("./file.txt", true, "", "", "./file.txt", "", "");
}

} // namespace
