#include <aftfs_localfilesystem.h>
#include <aftfs_directoryentry.h>
#include <aunit.h>
#include <vector>

namespace {

using namespace aunit;
using namespace aftfs;

Describe d("aftfs_localfilesystem", []
{
    it("List Directory", [&]
    {
        LocalFileSystem fileSystem;

        std::vector<aftu::URL> entries;

        fileSystem.listCurrentDirectory(entries);
    });
});

} // namespace
