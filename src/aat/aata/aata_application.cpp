#include <aata_application.h>
#include <aata_commandline.h>

namespace aegis {
namespace aata {

Application::Application()
{
}

Application::~Application()
{
}

int Application::run(aata::CommandLine const& commandLine)
{
    preRun();
    onRun(commandLine);
    postRun();
}

} // namespace
} // namespace
