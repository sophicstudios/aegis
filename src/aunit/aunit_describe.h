#ifndef INCLUDED_AUNIT_DESCRIBE_H
#define INCLUDED_AUNIT_DESCRIBE_H

#include <functional>
#include <string>

#define describe(name, func) namespace { aunit::Describe describeTest(name, func, __FILE__, __LINE__); }

#define it(name, func) aunit::doIt(name, func, __FILE__, __LINE__);

#define beforeEach(func) aunit::doBeforeEach(func, __FILE__, __LINE__);

#define afterEach(func) aunit::doAfterEach(func, __FILE__, __LINE__);

namespace aunit {

class Describe
{
public:
    Describe(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line);

    ~Describe();

private:
    Describe();
    Describe(Describe const&);
    Describe& operator=(Describe const&);
};

void doBeforeEach(std::function<void ()> const& func, std::string const& filename, int line);

void doAfterEach(std::function<void ()> const& func, std::string const& filename, int line);

void doIt(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line);

} // namespace

#endif // INCLUDED
