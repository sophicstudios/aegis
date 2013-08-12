#include <aftfs_localfilesystem.h>
#include <aftfs_directoryentry.h>
#include <aunit.h>
#include <vector>

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
    std::vector<aftfs::DirectoryEntry> entries;
    
    filesystem.listDirectory(entries);
}

} // namespace
