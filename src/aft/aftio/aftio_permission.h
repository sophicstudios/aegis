#ifndef INCLUDED_AEGIS_AFTIO_PERMISSION_H
#define INCLUDED_AEGIS_AFTIO_PERMISSION_H

#include <aftu_exception.h>
#include <string>

namespace aftio {

class Permission
{
public:
    enum Type {
        Type_READ = 0x1,
        Type_WRITE = 0x1 << 1,
        Type_EXECUTE = 0x1 << 2
    };
    
    class Read
    {
    public:
        Read(bool read);

        ~Read();

        operator bool() const;

    private:
        bool m_read;
    };

    class Write
    {
    public:
        Write(bool write);

        ~Write();

        operator bool() const;

    private:
        bool m_write;
    };

    class Execute
    {
    public:
        Execute(bool execute);

        ~Execute();

        operator bool() const;

    private:
        bool m_execute;
    };

    /**
     * Default Constructor. Creates a Permission object with read, write and
     * execute values all disabled.
     */
    Permission();

    /**
     * Constructor. Creates a Permission object with read, write and execute
     * flags set by the parameters 'flags'
     */
    Permission(int typeFlags);

    /**
     * Creates a Permission object with read, write and execute set
     * based on the boolean values of r, w, and x
     */
    Permission(Read read, Write write, Execute execute);

    /**
     * Copy Constructor
     */
    Permission(Permission const& rhs);
        
    /**
     * Destructor
     */
    ~Permission();

    /**
     * Assignment operator
     */
    Permission& operator=(Permission const& rhs);

    Permission& operator|=(Read read);

    Permission& operator|=(Write write);

    Permission& operator|=(Execute execute);

    Permission& operator|=(Permission const& permission);

    Permission& operator&=(Read read);

    Permission& operator&=(Write write);

    Permission& operator&=(Execute execute);

    Permission& operator&=(Permission const& permission);
    
    /**
     * Returns the value of the read flag
     */
    Read read() const;

    /**
     * Sets the read flag to the specfied value
     */
    void read(Read value);
    
    /**
     * Returns the value of the write flag
     */
    Write write() const;

    /**
     * Sets the write flag to the specified value
     */
    void write(Write value);

    /**
     * Returns the value of the execute flag
     */
    Execute execute() const;
    
    /**
     * Sets the execute flag to the specified value
     */
    void execute(Execute value);

private:
    bool m_read;
    bool m_write;
    bool m_execute;
};

std::ostream& operator<<(std::ostream& os, Permission const& perm);

Permission operator|(Permission const& lhs, Permission const& rhs);

Permission operator&(Permission const& lhs, Permission const& rhs);

} // namespace

#endif // INCLUDED
