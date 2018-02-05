#include <aftt_timezoneutil.h>
#include <ctime>

namespace aftt {

bool TimezoneUtil::isDST(Region region)
{
    return false;
}

int TimezoneUtil::currentOffset(Region region)
{
    //time_t now = std::time(NULL);
    
    return 0;
}

int TimezoneUtil::currentOffset(Region region, bool& isDST)
{
    //time_t now = std::time(NULL);
    return 0;
}

} // namespace
