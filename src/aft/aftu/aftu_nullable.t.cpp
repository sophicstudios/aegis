#include <aftu_nullable.h>
#include <aunit.h>
#include <algorithm>
#include <cstring>

namespace aftu {

class MyString
{
public:
    MyString(char const* const str)
    {
        m_length = std::strlen(str);
        m_str = new char[m_length + 1];
        std::strncpy(m_str, str, m_length);
        m_str[m_length] = 0;
    }
    
    MyString(MyString const& rhs)
    : m_length(rhs.m_length)
    {
        m_str = new char[m_length + 1];
        std::strncpy(m_str, rhs.m_str, m_length);
        m_str[m_length] = 0;
    }
    
    ~MyString()
    {
        delete [] m_str;
        m_str = NULL;
        m_length = 0;
    }
    
    MyString& operator=(MyString const& rhs)
    {
        // if no memory is available, this will throw and the
        // original string will remain unchanged
        char* tmpStr = new char[rhs.m_length + 1];

        if (m_str) {
            delete [] m_str;
        }
        
        m_length = rhs.m_length;
        m_str = tmpStr;
        std::strncpy(m_str, rhs.m_str, m_length);
        m_str[m_length] = 0;
        
        return *this;
    }
    
    bool operator==(MyString const& rhs)
    {
        return std::strcmp(m_str, rhs.m_str) == 0;
    }
    
private:
    char* m_str;
    size_t m_length;
};

class TestNullable : public aunit::TestFixture
{
public:
    TestNullable();

    virtual ~TestNullable();

    virtual void runTest();
};

AUNIT_REGISTERTEST(TestNullable);

TestNullable::TestNullable()
{}

TestNullable::~TestNullable()
{}

void TestNullable::runTest()
{
    aftu::Nullable<MyString> nullable;
    AUNIT_ASSERT(nullable.isNull());
    
    MyString myString("myString");

    nullable = myString;
    AUNIT_ASSERT(!nullable.isNull());
    AUNIT_ASSERT(nullable.value() == myString);
    
    nullable.makeNull();
    AUNIT_ASSERT(nullable.isNull());
}

} // namespace
