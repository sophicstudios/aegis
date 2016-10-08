#include <actp_semaphore.h>
#include <actp_condition.h>
#include <actp_thread.h>
#include <actp_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>

namespace {

using namespace aunit;

void thread(int& i, actp::Semaphore& s1, actp::Semaphore& s2)
{
    s1.wait();

    actp::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
    
    i = 5;

    s2.signal();
}

Describe d("actp_semaphore", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("wait_signalf", [&]
    {
        int i = 0;
        actp::Semaphore s1(0);
        actp::Semaphore s2(0);

        actp::Thread t(std::bind(thread, std::ref(i), std::ref(s1), std::ref(s2)));

        expect(i).toEqual(0);

        s1.signal();
        s2.wait();

        expect(i).toEqual(5);

        t.join();
    });
});

} // namespace

