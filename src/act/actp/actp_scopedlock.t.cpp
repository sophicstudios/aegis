#include <actp_scopedlock.h>
#include <actp_mutex.h>
#include <afte_assert.h>

using namespace aegis;

int main(int argc, char** argv)
{
    try
    {
        actp::Mutex m;
        actp::ScopedLock<actp::Mutex> lock(m);
    }
    catch (...)
    {
        return -1;
    }

    return 0;
}
