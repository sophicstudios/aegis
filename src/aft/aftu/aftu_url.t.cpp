#include <aunit.h>
#include <aftu_url.h>
#include <iostream>

namespace aftu {

using namespace aunit;

namespace {

void checkUrl(
    std::string const& urlStr,
    bool isValid,
    std::string const& scheme,
    std::string const& authority,
    std::string const& path,
    std::string const& query,
    std::string const& fragment)
{
    URL url(urlStr);
    expect(url.isValid()).toEqual(isValid);
    
    if (isValid) {
        expect(url.scheme()).toEqual(scheme);
        
        expect(url.hasAuthority()).toEqual(!authority.empty());
        expect(url.authority()).toEqual(authority);
        
        expect(url.path()).toEqual(path);
        
        expect(url.hasQuery()).toEqual(!query.empty());
        expect(url.query()).toEqual(query);
        
        expect(url.hasFragment()).toEqual(!fragment.empty());
        expect(url.fragment()).toEqual(fragment);
    }
}

}

describe("aftu_url", []
{
    it("Empty Construction", [&]
    {
        checkUrl("", false, "", "", "", "", "");
        checkUrl("http://www.google.com", true, "http", "www.google.com", "", "", "");
        checkUrl("http://www.google.com/", true, "http", "www.google.com", "/", "", "");
        checkUrl("http://www.google.com/search", true, "http", "www.google.com", "/search", "", "");
        checkUrl("http://www.google.com/search/", true, "http", "www.google.com", "/search/", "", "");
        checkUrl("http://www.google.com/search?term=test", true, "http", "www.google.com", "/search", "term=test", "");
        checkUrl("http://www.google.com/search?term=test#ref", true, "http", "www.google.com", "/search", "term=test", "ref");
    });

    it("File Construction", [&]
    {
        checkUrl("file://localhost/usr/local", true, "file", "localhost", "/usr/local", "", "");
        checkUrl("file://localhost/usr/local/", true, "file", "localhost", "/usr/local/", "", "");
        checkUrl("file:///usr/local", true, "file", "", "/usr/local", "", "");
        checkUrl("file:///local/file.txt", true, "file", "", "/local/file.txt", "", "");
        checkUrl("file.txt", true, "", "", "file.txt", "", "");
        checkUrl("./file.txt", true, "", "", "./file.txt", "", "");
    });

    it("Relative/Absolute", [&]
    {
        URL relative1("~user/dir1");

        expect(relative1.isRelative()).toBeTrue();
        expect(relative1.isAbsolute()).non().toBeTrue();

        URL relative2("file.txt");
        
        expect(relative2.isRelative()).toBeTrue();
        expect(relative2.isAbsolute()).non().toBeTrue();
        
        URL absolute1("file:///~user/dir1");
        
        expect(absolute1.isAbsolute()).toBeTrue();
        expect(absolute1.isRelative()).non().toBeTrue();

        URL absolute2("file:///file.txt");
        
        expect(absolute2.isAbsolute()).toBeTrue();
        expect(absolute2.isRelative()).non().toBeTrue();
    });
});

} // namespace
