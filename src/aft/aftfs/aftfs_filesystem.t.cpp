#include <aftfs_filesystem.h>
#include <aftio_permissions.h>
#include <aunit.h>

namespace aftfs {

class TestFileSystem : public aunit::TestFixture
{
public:
    TestFileSystem() {}

    virtual ~TestFileSystem() {}

protected:
    virtual void runTest();
    
private:
    void testFileOpen();
    void testDirectoryListing();
};

AUNIT_REGISTERTEST(TestFileSystem);

void TestFileSystem::runTest()
{
/*
    FileSystem::Status result;

    // open a file
    FileHandle fileHandle;
    result = fileSystem.openFile(&fileHandle, filePath);
    AUNIT_ASSERT(result == FileSystem::Status_OK);
    AUNIT_ASSERT(fileHandle.isOpen());
    
    // close a file
    fileSystem.closeFile(file);

    // open a file readonly
    result = fileSystem.openFile(&fileHandle, filePath, Flags::READ_ONLY);
*/
}

void TestFileSystem::testFileOpen()
{
/*
    Path path("test.dat");
    ReadOnlyFile f1;
    f1.open(path);
    f1.close();
    
    FileReader file(path);
    ReadOnlyFile file;
    FileSystem::Status result = LocalFileSystem::openOrCreate(&file, path);
*/
}

void TestFileSystem::testDirectoryListing()
{
/*
    aftfs::LocalFileSystem fileSystem;
    
    std::vector<aftfs::DirectoryEntry> entries;
    aftfs::Path path("./");
    fileSystem.listDir(&entries, path);
*/
}

} // namespace
