#ifndef INCLUDED_AEGIS_AFTH_UUID_H
#define INCLUDED_AEGIS_AFTH_UUID_H

#include <string>
#include <vector>

namespace afth {

class UUID
{
public:
    friend bool operator==(UUID const& lhs, UUID const& rhs);
    friend bool operator!=(UUID const& lhs, UUID const& rhs);
    friend bool operator<(UUID const& lhs, UUID const& rhs);
    friend bool operator<=(UUID const& lhs, UUID const& rhs);
    friend bool operator>(UUID const& lhs, UUID const& rhs);
    friend bool operator>=(UUID const& lhs, UUID const& rhs);

    static UUID v4();

    UUID();

    ~UUID();

    std::string str() const;

    std::vector<char> bytes() const;

private:
    UUID(uint64_t a, uint64_t b);

    struct uuid_t {
        uint64_t a;
        uint64_t b;
    };

    uuid_t m_uuid;
};

bool operator==(UUID const& lhs, UUID const& rhs);

bool operator!=(UUID const& lhs, UUID const& rhs);

bool operator<(UUID const& lhs, UUID const& rhs);

bool operator<=(UUID const& lhs, UUID const& rhs);

bool operator>(UUID const& lhs, UUID const& rhs);

bool operator>=(UUID const& lhs, UUID const& rhs);

std::ostream& operator<<(std::ostream& os, UUID const& uuid);

} // namespace

#endif // INCLUDED
