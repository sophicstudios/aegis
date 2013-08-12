#include <aftfs_path.h>
#include <aftu_exception.h>
#include <aftu_stringutil.h>
#include <string>
#include <vector>
#include <libgen.h>

namespace aftfs {


Path::Path(std::string const& pathString)
: m_isAbsolute(false)
{
    if (pathString.empty()) {
        throw aftu::Exception() << "Empty path string ["
            << " pathString: '" << pathString << "'"
            << " ]";
    }

    // set some initial boundaries
    std::string::const_iterator beg = pathString.begin();
    std::string::const_iterator end = pathString.end();

    // The following block figures out if there if the path
    // has an entry with no trailing slash and also if it
    // has an extension
    
    // Note: because of the empty check above, begin and end are
    // guaranteed not to be the same and this is valid
    std::string::const_iterator it1 = end-1;
    std::string::const_iterator it2 = it1;
    bool foundSep = false;
    std::string pathEntry;
    while (it1 != beg) {
        if ((*it1) == '/') {
            if (it1 != it2) {
                pathEntry.assign(it1+1, it2+1);
            }
            foundSep = true;
            break;
        }
        else if ((*it1) == '.') {
            if (it1 != it2) {
                m_extension.assign(it1+1, it2+1);
                it2 = it1;
            }
        }
        
        --it1;
    }

    if (foundSep && !pathEntry.empty()) {
        m_basename = pathEntry;
    }
    else if (!foundSep) {
        // we are done
        m_basename = pathEntry;
    }
    
    end = it1;
    it1 = it2 = beg;
    // tokenize the path. Do not keep empty tokens
    // i.e.
    // '/dir1//dir2/' => 'dir1','dir2'
    //   is the same as:
    // '/dir1/dir2' => 'dir1','dir2'
    
    // first, skip over any leading '/', which also 
    // indicates this path is absolute
    while (*it2 == '/' && it2 != end) {
        m_isAbsolute = true;
        ++it2;
    }
    
    it1 = it2;
    while (it2 != end) {
        // move the 2nd iterator to the end of any directory entry
        while (*it2 != '/' && it2 != end) {
            ++it2;
        }
        
        if (it1 != it2) {
            pathEntry.assign(it1, it2);
            m_directories.push_back(pathEntry);
        }
        
        while (*it2 == '/' && it2 != end) {
            ++it2;
        }
        
        it1 = it2;
    }
}

Path::Path(Path const& path)
{
}

Path::~Path()
{
}

Path& Path::operator=(Path const& path)
{
    return *this;
}

std::string Path::nativePathString() const
{
    std::string path;
    if (m_isAbsolute) {
        path.append("/");
    }
    
    std::vector<std::string>::const_iterator it, end = m_directories.end();
    for (it = m_directories.begin(); it != end; ++it) {
        path.append(*it);
        if (it + 1 != end) {
            path.append("/");
        }
    }
    
    if (!m_basename.empty()) {
        if (!m_directories.empty()) {
            path.append("/");
        }

        path.append(m_basename);
    
        if (!m_extension.empty()) {
            path.append(".").append(m_extension);
        }
    }
        
    return path;
}

std::string Path::hostname() const
{
    return m_hostname;
}

std::string Path::dirname() const
{
    std::string dirname;
    if (m_isAbsolute) {
        dirname.append("/");
    }
    
    std::vector<std::string>::const_iterator it, end = m_directories.end();
    for (it = m_directories.begin(); it != end; ++it) {
        dirname.append(*it);
        if (it + 1 != end) {
            dirname.append("/");
        }
    }
    
    return dirname;
}

std::string Path::basename() const
{
    return m_basename;
}

std::string Path::extension() const
{
    return m_extension;
}

} // namespace
