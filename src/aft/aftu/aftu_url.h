#ifndef INCLUDED_AEGIS_AFTU_URL_H
#define INCLUDED_AEGIS_AFTU_URL_H

#include <aftu_stringref.h>
#include <string>

namespace aftu {

/**
 * Represents a Uniform Resource Locator (URL), which takes the form
 * scheme://[ user-info "@" ][<domain>][:<port>]/[<path>][?<query_string>][#<fragment_id>]
 * Examples:
 *   http://www.google.com/
 *   http://yahoo.com:8080/
 *   file://localhost/usr/bin
 *   file:///usr/bin
 *   ssh://user@domain.com:22/
 */
class URL
{
public:
    // constructs an empty and invalid URL
    URL();

    // constructs a URL from the supplied string.
    explicit URL(std::string const& urlString);
    
    URL(URL const& url);
    
    ~URL();
    
    URL& operator=(URL const& url);
    
    /**
     * Returns whether the URL is well-formed. This does not indicate
     * whether the resource identified by the URL actually exists or is
     * valid, just that the URL is structured correctly
     */
    bool isValid();
    
    /**
     * Returns the scheme portion of the URL, i.e. http, file, ssh
     */
    std::string scheme() const;
    
    /**
     * Indicates whether the authority section of the URL exists
     */
    bool hasAuthority() const;
    
    /**
     * Returns the authority portion of the URL. If it does not exist, then
     * the result string is empty
     */
    std::string authority() const;
    
    /**
     * Indicates whether the path section of the URL exists
     */
    bool hasPath() const;
    
    /**
     * Returns the path portion of the URL. If it does not exists, then
     * the result string is empty
     */
    std::string path() const;
    
    bool hasQuery() const;
    
    std::string query() const;
    
    bool hasFragment() const;
    
    std::string fragment() const;
    
private:
    class Impl;
    Impl* m_impl;
};

} // namespace

#endif // INCLUDED
