#ifndef INCLUDED_AEGIS_AFTIO_FLAGS_H
#define INCLUDED_AEGIS_AFTIO_FLAGS_H

namespace aegis {
namespace aftio {

struct OpenFlags
{
    struct CreateOrOpen {};
    static CreateOrOpen CREATE_OR_OPEN;

    struct CreateOnly {};
    static CreateOnly CREATE_ONLY;

};

struct AccessFlags
{
    struct ReadOnly {};
    static ReadOnly READ_ONLY;

    struct ReadWrite {};
    static ReadWrite READ_WRITE;
};

} // namespace
} // namespace

#endif // INCLUDED
