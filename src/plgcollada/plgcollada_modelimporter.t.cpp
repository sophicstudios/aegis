#include <plgcollada_modelimporter.h>
#include <aunit.h>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>

namespace aegis {
namespace plgcollada {

class TestModelImporter : public aunit::TestFixture
{
public:
    TestModelImporter();
    
    virtual ~TestModelImporter();

protected:
    virtual void runTest();
    
private:
};

AUNIT_REGISTERTEST(TestModelImporter);

namespace {

class MyHandler : public xercesc::DefaultHandler
{
public:
    void startElement(
        XMLCh const* const uri,
        XMLCh const* const localname,
        XMLCh const* const qname,
        xercesc::Attributes const& attrs);
        
    void fatalError(xercesc::SAXParseException const& e);
};

void MyHandler::startElement(
    XMLCh const* const uri,
    XMLCh const* const localname,
    XMLCh const* const qname,
    xercesc::Attributes const& attrs)
{
    char* localnameTrans = xercesc::XMLString::transcode(localname);
    char* qnameTrans = xercesc::XMLString::transcode(qname);

    std::cout << "element ["
        << " localname: " << localnameTrans
        << " qname: " << qnameTrans
        << " ]" << std::endl;

    xercesc::XMLString::release(&localnameTrans);
    xercesc::XMLString::release(&qnameTrans);
}
    
void MyHandler::fatalError(xercesc::SAXParseException const& e)
{
    char* error = xercesc::XMLString::transcode(e.getMessage());
    std::cout << "fatalError ["
        << " error: " << error
        << " ]" << std::endl;
    xercesc::XMLString::release(&error);
}

} // namespace

TestModelImporter::TestModelImporter()
{}

TestModelImporter::~TestModelImporter()
{}

void TestModelImporter::runTest()
{
    try {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (xercesc::XMLException const& e) {
        char* error = xercesc::XMLString::transcode(e.getMessage());
        std::cout << "XMLException ["
            << " error: " << error
            << " ]" << std::endl;
        xercesc::XMLString::release(&error);
        return;
    }
    
    std::string rootPath("/Users/fizban/development/models/bloomberg_tower/models/");
    std::string modelFilename("warehouse_model.dae");
    
    xercesc::SAX2XMLReader* xmlReader = xercesc::XMLReaderFactory::createXMLReader();
    xmlReader->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
    xmlReader->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
    
    MyHandler* handler = new MyHandler();
    
    xmlReader->setContentHandler(handler);
    xmlReader->setErrorHandler(handler);
    
    try {
        std::string filePath(rootPath + modelFilename);
        xmlReader->parse(filePath.c_str());
    }
    catch (xercesc::XMLException const& e) {
        char* error = xercesc::XMLString::transcode(e.getMessage());
        std::cout << "XMLException ["
            << " error: " << error
            << " ]" << std::endl;
        xercesc::XMLString::release(&error);
        return;
    }
    catch (xercesc::SAXParseException const& e) {
        char* error = xercesc::XMLString::transcode(e.getMessage());
        std::cout << "SAXParseException ["
            << " error: " << error
            << " ]" << std::endl;
        xercesc::XMLString::release(&error);
        return;
    }
    catch (...) {
        std::cout << "Unknown Exception" << std::endl;
        return;
    }
    
    delete handler;
    delete xmlReader;
}

} // namespace
} // namespace
