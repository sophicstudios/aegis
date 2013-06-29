#include <actp_mutex.h>
#include <actp_condition.h>
#include <actp_thread.h>
#include <actp_threadutil.h>
#include <aunit.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <functional>
#include <iostream>

using namespace aegis;

class Reader
{
public:
    Reader(actp::Mutex& mutex, actp::Condition& condition)
    : m_mutex(mutex), m_condition(condition)
    {}

    ~Reader()
    {}

    void run()
    {
        m_mutex.lock();

        std::cout << "reader: start" << std::endl;
        std::cout << "reader: waiting for data..." << std::endl;

        m_condition.wait(m_mutex);

        std::cout << "reader: reading data..." << std::endl;
        std::cout << "reader: done" << std::endl;

        m_mutex.unlock();
    }

private:
    actp::Mutex& m_mutex;
    actp::Condition& m_condition;
};


class Writer
{
public:
    Writer(actp::Mutex& mutex, actp::Condition& condition)
    : m_mutex(mutex), m_condition(condition)
    {}

    ~Writer()
    {}

    void run()
    {
        aflt::Seconds interval(2);
        m_mutex.lock();
        std::cout << "writer: start" << std::endl;        
        std::cout << "writer: sleeping..." << std::endl;
        
        actp::ThreadUtil::sleep(interval);
        
        std::cout << "writer:: signalOne" << std::endl;
        
        m_condition.signalOne();
        
        std::cout << "writer:: end" << std::endl;
                
        m_mutex.unlock();
    }
    
private:
    actp::Mutex& m_mutex;
    actp::Condition& m_condition;
};

class TestCondition : public aunit::TestFixture
{
public:
    TestCondition() {}

    virtual ~TestCondition() {}

protected:
    virtual void runTest();
};

AUNIT_REGISTER_TEST(TestCondition);

void TestCondition::runTest()
{
    actp::Mutex m;
    actp::Condition c;
    
    Reader r(m, c);
    actp::Thread readerThread(boost::bind(&Reader::run, &r));

    Writer w(m, c);
    actp::Thread writerThread(boost::bind(&Writer::run, &w));
    
    readerThread.join();
    writerThread.join();
}
