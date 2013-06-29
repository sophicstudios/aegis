#ifndef INCLUDED_AEGIS_AFTIO_PERMISSION_H
#define INCLUDED_AEGIS_AFTIO_PERMISSION_H

#include <aftu_exception.h>
#include <string>

namespace aegis {
namespace aftio {

class Permission
{
public:
    enum Type {
        Type_READ = 0x1,
        Type_WRITE = 0x1 << 1,
        Type_EXECUTE = 0x1 << 2
    };
    
    /**
     * Default Constructor. Creates a Permission object with read, write and
     * execute values all enabled.
     */
    Permission();

    /**
     * Constructor. Creates a Permission object with read, write and execute
     * flags set by the parameters 'flags'
     */
    Permission(int typeFlags);
    
    /**
     * Constructor. Creates a Permission object with read, write and execute
     * set by the parameter 'flagString', which follows the regular
     * expression: "r{0,1}w{0,1}x{0,1}" (ex. "rwx", "w", "r", "rx", etc.)
     * If the string is invalid, i.e. does not contain any of these characters,
     * or the wrong number of flags, an exception will be thrown
     */
    Permission(std::string const& flagString) throw (aftu::Exception);
    
    /**
     * Creates a Permission object with read, write and execute set
     * based on the boolean values of r, w, and x
     */
    Permission(bool r, bool w, bool x);

    /**
     * Copy Constructor
     */
    Permission(Permission const& rhs);
        
    /**
     * Destructor
     */
    ~Permission();

    Permission& operator=(Permission const& rhs);

    Permission& operator+=(Permission const& rhs);
    
    Permission& operator-=(Permission const& rhs);
    
    /**
     * Returns the value of the read flag
     */
    bool hasRead() const;

    /**
     * Sets the read flag to the specfied value
     */
    void setRead(bool value);
    
    void enableRead();
    
    void disableRead();
    
    /**
     * Returns the value of the write flag
     */
    bool hasWrite() const;

    /**
     * Sets the write flag to the specified value
     */
    void setWrite(bool value);

    void enableWrite();
    
    void disableWrite();

    /**
     * Returns the value of the execute flag
     */
    bool hasExecute() const;
    
    /**
     * Sets the execute flag to the specified value
     */
    void setExecute(bool x);

    void enableExecute();
    
    void disableExecute();
    
private:
    bool m_read;
    bool m_write;
    bool m_execute;
};

std::ostream& operator<<(std::ostream& os, Permission const& perm);

Permission unionOF(Permission const& lhs, Permission const& rhs);

Permission intersectionOf(Permission const& lhs, Permission const& rhs);

} // namespace
} // namespace

#endif // INCLUDED
