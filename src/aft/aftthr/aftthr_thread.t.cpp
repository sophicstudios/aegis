#include <aftthr_thread.h>
#include <aftthr_mutex.h>
#include <aftthr_threadutil.h>
#include <aftt_datetimeinterval.h>
#include <aunit.h>

namespace {

using namespace aunit;

void thread()
{
    aftthr::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
}

Describe d("aftthr_thread", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("join", [&]
    {
        aftthr::ThreadAttributes threadAttributes;
        threadAttributes.createType(aftthr::ThreadAttributes::CreateType_DETACHED);

        aftthr::Thread t1(thread, threadAttributes);

        expect(t1.join()).non().toBeTrue();

        aftthr::Thread t2(thread);

        expect(t2.join()).toBeTrue();
    });
});

} // namespace
