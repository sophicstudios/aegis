#include <aunit.h>

int main(int argc, char** argv)
{
    aunit::TestManager testManager;
    aunit::ConsoleReporter reporter;
    return testManager.run(reporter) == aunit::TestManager::Result_OK ? 0 : -1;
}
