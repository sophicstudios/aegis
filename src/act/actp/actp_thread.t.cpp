#include <actp_thread.h>
#include <actp_mutex.h>
#include <aftt_timeinterval.h>
#include <aunit.h>
#include <iomanip>
#include <iostream>

using namespace aegis;

class ThreadFunc
{
public:
    ThreadFunc(actp::Mutex& mutex, aftt::TimeInterval const& sleepTime)
    : m_mutex(mutex),
      m_sleepTime(sleepTime)
    {}

    void operator()()
    {
        m_mutex.lock();
        std::cout << "threadFunc (0x"
            << std::hex << actp::ThreadUtil::currentThreadId() << ") start"
            << std::endl;

        std::cout << "threadFunc (0x"
            << std::hex << actp::ThreadUtil::currentThreadId() << ") sleeping..."
            << std::endl;
        m_mutex.unlock();

        actp::ThreadUtil::sleep(m_sleepTime);

        m_mutex.lock();
        std::cout << "threadFunc (0x"
            << std::hex << aclp::ThreadUtil::currentThreadId() << ") end"
            << std::endl;
        m_mutex.unlock();
    }

private:
    actp::Mutex& m_mutex;
    aftt::TimeInterval m_sleepTime;
};

int main(int argc, char** argv)
{
    boost::shared_ptr<aunit::ConsoleReporter> reporter(new aunit::ConsoleReporter());
    aunit::TestManager::initialize(reporter);

    try
    {
        std::cout << "main: begin" << std::endl;

        std::cout << "main: creating mutex" << std::endl;
        actp::Mutex mutex;

        std::cout << "main: creating thread" << std::endl;
        ThreadFunc threadFunc1(mutex, aflt::Seconds(3));
        actp::ThreadAttributes threadAttributes;
        threadAttributes.setCreateType(actp::ThreadAttributes::CreateType_DETACHED);
        actp::Thread t1(threadFunc1, threadAttributes);
        
        mutex.lock();
        std::cout << "main: thread: 0x" << std::hex << t1.id() << std::endl;
        std::cout << "main: joining..." << std::endl;
        mutex.unlock();

        bool joinResult = t1.join();
        AUNIT_ASSERT_REPORT(false == joinResult);

        ThreadFunc threadFunc2(mutex, aftt::Seconds(2));
        actp::Thread t2(threadFunc2);

        mutex.lock();
        std::cout << "main: thread: 0x" << std::hex << t2.id() << std::endl;
        std::cout << "main: joining..." << std::endl;
        mutex.unlock();

        joinResult = t2.join();
        AUNIT_ASSERT_REPORT(true == joinResult);

        std::cout << "main: end" << std::endl;
    }
    catch (...)
    {
        return -1;
    }

    return 0;
}
