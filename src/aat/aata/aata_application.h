#ifndef INCLUDE_AEGIS_AATA_APPLICATION_H
#define INCLUDE_AEGIS_AATA_APPLICATION_H

namespace aegis {
namespace aata {

class CommandLine;

class Application
{
public:
    Application();
    
    virtual ~Application();
    
    int run(aata::CommandLine const& commandLine);

protected:
    virtual void preRun();
    
    virtual int onRun(aata::CommandLine const& commandLine);

    virtual void postRun();
    
private:
};

} // namespace
} // namespace

#endif // INCLUDE
