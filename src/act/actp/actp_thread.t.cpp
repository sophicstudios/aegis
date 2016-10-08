#include <actp_thread.h>
#include <actp_mutex.h>
#include <actp_threadutil.h>
#include <aftt_datetimeinterval.h>
#include <aunit.h>

namespace {

using namespace aunit;

void thread()
{
    actp::ThreadUtil::sleep(aftt::DatetimeInterval(aftt::Seconds(1)));
}

Describe d("actp_thread", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("join", [&]
    {
        actp::ThreadAttributes threadAttributes;
        threadAttributes.createType(actp::ThreadAttributes::CreateType_DETACHED);

        actp::Thread t1(thread, threadAttributes);

        expect(t1.join()).non().toBeTrue();

        actp::Thread t2(thread);

        expect(t2.join()).toBeTrue();
    });
});

} // namespace
