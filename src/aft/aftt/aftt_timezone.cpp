#include <aftt_timezone.h>
#include <ctime>

namespace aegis {
namespace aftt {

bool Timezone::isDST(Region region)
{
    return false;
}

int Timezone::currentOffset(Region region)
{
    //time_t now = std::time(NULL);
    
    return 0;
}

int Timezone::currentOffset(Region region, bool& isDST)
{
    //time_t now = std::time(NULL);
    return 0;
}

} // namespace
} // namespace
