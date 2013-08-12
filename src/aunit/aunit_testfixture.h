#ifndef INCLUDED_AEGIS_AUNIT_TESTFIXTURE_H
#define INCLUDED_AEGIS_AUNIT_TESTFIXTURE_H

namespace aunit {

class Reporter;

class TestFixture
{
public:
    TestFixture();

    virtual ~TestFixture();

    void run(Reporter& reporter);

protected:
    virtual void setup();

    virtual void runTest() = 0;

    virtual void tearDown();

    Reporter& reporter();

private:
    Reporter* m_reporter;
};

} // namespace

#endif // INCLUDED
