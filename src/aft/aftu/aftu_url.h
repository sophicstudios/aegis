#ifndef INCLUDED_AEGIS_AFTU_URL_H
#define INCLUDED_AEGIS_AFTU_URL_H

#include <aftu_stringref.h>
#include <string>

namespace aegis {
namespace aftu {

/// Represents a 
class Url
{
public:
    // constructs an empty and invalid URL
    Url();

    // constructs a URL from the supplied string.
    explicit Url(std::string const& urlString);
    
    Url(Url const& url);
    
    ~Url();
    
    Url& operator=(Url const& url);
    
    bool isValid();
    
    std::string scheme() const;
    
    bool hasAuthority() const;
    
    std::string authority() const;
        
    bool hasPath() const;
    
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
} // namespace

#endif // INCLUDED
