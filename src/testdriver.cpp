#include <aunit.h>

using namespace aegis;

int main(int argc, char** argv)
{
    aunit::TestManager testManager;
    aunit::ConsoleReporter reporter;
    testManager.runAllTests(reporter);
    reporter.publishReport();
    
    return 0;
}
