#include <aftfs_localfilesystem.h>
#include <aftfs_directoryentry.h>
#include <aunit.h>
#include <vector>
#include <iostream>

namespace aftfs {

describe("aftfs_localfilesystem", []
{
    it("List Directory", [&]
    {
        LocalFilesystem filesystem;

        std::vector<aftu::URL> entries;

        filesystem.listCurrentDirectory(entries);
    });
});

} // namespace
