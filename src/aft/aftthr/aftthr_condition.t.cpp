#include <aftthr_condition.h>
#include <aftthr_mutex.h>
#include <aftthr_scopedlock.h>
#include <aftthr_thread.h>
#include <aftthr_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>
#include <vector>

namespace {

using namespace aunit;

class Reader
{
public:
    Reader(std::vector<int>& input, aftthr::Mutex& mutex, aftthr::Condition& condition)
    : m_input(input),
      m_mutex(mutex),
      m_condition(condition)
    {}

    ~Reader()
    {}

    void run()
    {
        aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);

        m_condition.wait(m_mutex);

        std::copy(m_input.begin(), m_input.end(), std::back_inserter(m_output));
    }

    std::vector<int> const& output() const
    {
        aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);
        return m_output;
    }

private:
    std::vector<int>& m_input;
    std::vector<int> m_output;
    aftthr::Mutex& m_mutex;
    aftthr::Condition& m_condition;
};


class Writer
{
public:
    Writer(std::vector<int>& input, aftthr::Mutex& mutex, aftthr::Condition& condition)
    : m_input(input),
      m_mutex(mutex),
      m_condition(condition)
    {}

    ~Writer()
    {}

    void run()
    {
        aftt::DatetimeInterval interval(aftt::Seconds(1));
        aftthr::ThreadUtil::sleep(interval);

        aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);

        for (int i = 0; i < 10; ++i)
        {
            m_input.push_back(i);
        }

        m_condition.signalOne();
    }
    
private:
    std::vector<int>& m_input;
    aftthr::Mutex& m_mutex;
    aftthr::Condition& m_condition;
};


Describe d("aftthr_condition", []
{
    beforeEach([&]
    {
    });

    afterEach([&]
    {
    });

    it("wait", [&]
    {
        std::vector<int> vec;
        aftthr::Mutex m;
        aftthr::Condition c;
        
        Reader r(vec, m, c);
        aftthr::Thread readerThread(std::bind(&Reader::run, &r));

        Writer w(vec, m, c);
        aftthr::Thread writerThread(std::bind(&Writer::run, &w));

        readerThread.join();
        writerThread.join();

        expect(r.output().size()).toEqual(10);
    });
});

} // namespace

