#include <actp_mutex.h>
#include <actp_condition.h>
#include <actp_thread.h>
#include <actp_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>

namespace {

using namespace aunit;

void thread(int& i, actp::Mutex& m1, actp::Condition& c)
{
    m1.lock();

    c.signalOne();

    actp::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
    
    i = 5;

    m1.unlock();
}

Describe d("actp_mutex", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("lock_unlock", [&]
    {
        actp::Mutex m;

        actp::Mutex::Result result;

        result = m.lock();
        expect(result).toEqual(actp::Mutex::Result_OK);

        result = m.unlock();
        expect(result).toEqual(actp::Mutex::Result_OK);
    });

    it("mutal exclusion", [&]
    {
        int i = 0;
        actp::Mutex m1;
        actp::Condition c;

        m1.lock();

        actp::Thread t(std::bind(thread, std::ref(i), std::ref(m1), std::ref(c)));

        expect(i).toEqual(0);

        c.wait(m1);

        expect(i).toEqual(5);

        m1.unlock();

        t.join();
    });
});

} // namespace

