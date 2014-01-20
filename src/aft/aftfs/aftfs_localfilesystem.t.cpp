#include <aftfs_localfilesystem.h>
#include <aftfs_directoryentry.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace aftfs {

class TestLocalFilesystem : public aunit::TestFixture
{
public:
    TestLocalFilesystem();
    
    virtual ~TestLocalFilesystem();
    
protected:
    virtual void runTest();
    
private:
};

AUNIT_REGISTERTEST(TestLocalFilesystem);

TestLocalFilesystem::TestLocalFilesystem()
{}

TestLocalFilesystem::~TestLocalFilesystem()
{}

void TestLocalFilesystem::runTest()
{
    LocalFilesystem filesystem;
    std::vector<aftu::URL> entries;
    
    filesystem.listDirectory(entries);
    for (std::vector<aftu::URL>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        std::cout << "url: " << it->canonical() << std::endl;
        
        Filesystem::DirectoryEntryPtr entry = filesystem.directoryEntry(*it);
        std::cout << "is file: " << entry->isFile() << std::endl;;
        std::cout << "is dir: " << entry->isDirectory() << std::endl;
        std::cout << "is link: " << entry->isLink() << std::endl;
    }
}

} // namespace
