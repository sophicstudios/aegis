#ifndef INCLUDED_AEGIS_AFTFS_PATH_H
#define INCLUDED_AEGIS_AFTFS_PATH_H

#include <string>
#include <vector>

namespace aegis {
namespace aftfs {

///
/// @class Path
///
/// The Path class represents the path for a directory or file
/// on a host system. It provides methods to allow the caller to
/// easily break the path apart into its constituent parts.
///
/// == Construction ==
/// A Path is constructed by either providing a path string in the native
/// format of the host, a POSIX format of the form "/directory/directory/../name"
/// or by passing a URL of the form "file://host/directory/directory/../name"
///

class Path
{
public:
    Path(std::string const& pathString);    

    Path(Path const& path);

    virtual ~Path();
    
    Path& operator=(Path const& path);
    
    // Returns a path string in the native format of the system.
    std::string nativePathString() const;
    
    // returns the hostname of the path, or blank if none exists, in which
    // case the hostname can be considered to be 'localhost'
    std::string hostname() const;
    
    std::string dirname() const;

    std::string basename() const;

    std::string extension() const;
    
private:
    std::string m_hostname;
    std::vector<std::string> m_directories;
    std::string m_basename;
    std::string m_extension;
    bool m_isAbsolute;
};

} // namespace
} // namespace

#endif // INCLUDED
