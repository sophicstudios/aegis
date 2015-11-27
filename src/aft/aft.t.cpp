#include <aunit.h>

int main(int argc, char** argv)
{
    aunit::TestManager testManager;
    aunit::ConsoleReporter reporter;
    testManager.run(reporter);
    
    return 0;
}
