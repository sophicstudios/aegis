#include <aftthr_semaphore.h>
#include <aftthr_condition.h>
#include <aftthr_thread.h>
#include <aftthr_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>

namespace {

using namespace aunit;

void thread(int& i, aftthr::Semaphore& s1, aftthr::Semaphore& s2)
{
    s1.wait();

    aftthr::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
    
    i = 5;

    s2.signal();
}

Describe d("aftthr_semaphore", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("wait_signal", [&]
    {
        int i = 0;
        aftthr::Semaphore s1(0);
        aftthr::Semaphore s2(0);

        aftthr::Thread t(std::bind(thread, std::ref(i), std::ref(s1), std::ref(s2)));

        expect(i).toEqual(0);

        s1.signal();
        s2.wait();

        expect(i).toEqual(5);

        t.join();
    });
});

} // namespace

