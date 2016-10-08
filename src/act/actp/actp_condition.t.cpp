#include <actp_condition.h>
#include <actp_mutex.h>
#include <actp_scopedlock.h>
#include <actp_thread.h>
#include <actp_threadutil.h>
#include <aftt_seconds.h>
#include <aunit.h>
#include <functional>
#include <iostream>
#include <vector>

namespace {

using namespace aunit;

class Reader
{
public:
    Reader(std::vector<int>& input, actp::Mutex& mutex, actp::Condition& condition)
    : m_input(input),
      m_mutex(mutex),
      m_condition(condition)
    {}

    ~Reader()
    {}

    void run()
    {
        actp::ScopedLock<actp::Mutex> l(m_mutex);

        m_condition.wait(m_mutex);

        std::copy(m_input.begin(), m_input.end(), std::back_inserter(m_output));
    }

    std::vector<int> const& output() const
    {
        actp::ScopedLock<actp::Mutex> l(m_mutex);
        return m_output;
    }

private:
    std::vector<int>& m_input;
    std::vector<int> m_output;
    actp::Mutex& m_mutex;
    actp::Condition& m_condition;
};


class Writer
{
public:
    Writer(std::vector<int>& input, actp::Mutex& mutex, actp::Condition& condition)
    : m_input(input),
      m_mutex(mutex),
      m_condition(condition)
    {}

    ~Writer()
    {}

    void run()
    {
        aftt::DatetimeInterval interval(aftt::Seconds(1));
        actp::ThreadUtil::sleep(interval);

        actp::ScopedLock<actp::Mutex> l(m_mutex);

        for (int i = 0; i < 10; ++i)
        {
            m_input.push_back(i);
        }

        m_condition.signalOne();
    }
    
private:
    std::vector<int>& m_input;
    actp::Mutex& m_mutex;
    actp::Condition& m_condition;
};


Describe d("actp_condition", []
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
        actp::Mutex m;
        actp::Condition c;
        
        Reader r(vec, m, c);
        actp::Thread readerThread(std::bind(&Reader::run, &r));

        Writer w(vec, m, c);
        actp::Thread writerThread(std::bind(&Writer::run, &w));

        readerThread.join();
        writerThread.join();

        expect(r.output().size()).toEqual(10);
    });
});

} // namespace

