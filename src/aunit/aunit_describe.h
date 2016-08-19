#ifndef INCLUDED_AUNIT_DESCRIBE_H
#define INCLUDED_AUNIT_DESCRIBE_H

#include <functional>
#include <string>

namespace aunit {

class Describe
{
public:
    Describe(std::string const& name, std::function<void ()> const& func);

    ~Describe();

private:
    Describe();
    Describe(Describe const&);
    Describe& operator=(Describe const&);
};

void beforeEach(std::function<void ()> const& func);

void afterEach(std::function<void ()> const& func);

void it(std::string const& name, std::function<void ()> const& func);

} // namespace

#endif // INCLUDED
