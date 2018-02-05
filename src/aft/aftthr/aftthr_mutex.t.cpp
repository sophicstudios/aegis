#include <aftthr_mutex.h>
#include <aftthr_condition.h>
#include <aftthr_thread.h>
#include <aftthr_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>

namespace {

using namespace aunit;

void thread(int& i, aftthr::Mutex& m1, aftthr::Condition& c)
{
    m1.lock();

    c.signalOne();

    aftthr::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
    
    i = 5;

    m1.unlock();
}

Describe d("aftthr_mutex", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("lock_unlock", [&]
    {
        aftthr::Mutex m;

        aftthr::Mutex::Result result;

        result = m.lock();
        expect(result).toEqual(aftthr::Mutex::Result_OK);

        result = m.unlock();
        expect(result).toEqual(aftthr::Mutex::Result_OK);
    });

    it("mutal exclusion", [&]
    {
        int i = 0;
        aftthr::Mutex m1;
        aftthr::Condition c;

        m1.lock();

        aftthr::Thread t(std::bind(thread, std::ref(i), std::ref(m1), std::ref(c)));

        expect(i).toEqual(0);

        c.wait(m1);

        expect(i).toEqual(5);

        m1.unlock();

        t.join();
    });
});

} // namespace

