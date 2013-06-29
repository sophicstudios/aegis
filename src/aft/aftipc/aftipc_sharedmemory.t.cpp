#include <aftipc_sharedmemory.h>
#include <aftipc_mappedregion.h>
#include <aftio_flags.h>
#include <afth_crc32.h>
#include <aftu_hexprinter.h>
#include <aunit.h>
#include <iostream>

namespace aegis {
namespace aftipc {

class TestSharedMemory : public aunit::TestFixture
{
public:
    TestSharedMemory() {}

    virtual ~TestSharedMemory() {}

protected:
    virtual void runTest();
    
private:
    void loadMemory();
    void readMemory();
};

AUNIT_REGISTERTEST(TestSharedMemory);

void TestSharedMemory::runTest()
{
    loadMemory();
    readMemory();
}

static const size_t MAJOR_VERSION=1;
static const size_t MINOR_VERSION=0;

struct CountryHeader
{
    uint32_t crc;
    uint32_t majorVersion;
    uint32_t minorVersion;
    uint32_t count;
    char extra[32];
};

struct Country
{
    char isoCountryCode[3];
    char isoCurrencyCode[4];
    char enName[64];
};

static const Country COUNTRY_DATA[] = {
    {"US", "USD", "United States"},
    {"CA", "CAD", "Canada"},
    {"MX", "MXN", "Mexico"},
    {"EU", "EUR", "European Union"},
};

static const size_t COUNTRY_COUNT = sizeof(COUNTRY_DATA) / sizeof(Country);

uint32_t computeCrc(Country* countryArray, size_t countryCount)
{
    size_t length = countryCount * sizeof(Country);
    uint32_t crc = afth::Crc32::compute(reinterpret_cast<char*>(countryArray), length);
    return crc;
}

void TestSharedMemory::loadMemory()
{    
    // the unique key to our shared memory segment
    std::string key = "/mem1";

    // destroy any existing segment with the same name
    aftipc::SharedMemory::destroy(key);
    
    // calculate how much memory we need to store the data
    size_t countryDataSize = COUNTRY_COUNT * sizeof(Country);
    size_t totalSize = sizeof(CountryHeader) + countryDataSize;

    // create the shared memory segment with enough room for the initial header
    // plus all the country data.
    aftipc::SharedMemory mem(
        aftio::OpenFlags::CREATE_ONLY, // fail if already exists
        aftio::AccessFlags::READ_WRITE, // open for reading and writing
        key, // the unique key of the shared memory segment
        totalSize); // the size of the memory in bytes
    
    // Create a mapped region of the shared memory segment to hold the
    // header information.
    size_t offset = 0;
    aftipc::MappedRegion headerRegion(mem, offset, sizeof(CountryHeader));

    // Fill in the initial details of the header
    CountryHeader* header = reinterpret_cast<CountryHeader*>(headerRegion.data());
    //std::memset(header, 0, sizeof(CountryHeader));

    header->majorVersion = MAJOR_VERSION;
    header->minorVersion = MINOR_VERSION;

    // Create a mapped region of the shared memory segment to hold the
    // data for all the countries in the array.
    aftipc::MappedRegion countryRegion(mem, sizeof(CountryHeader), countryDataSize);
    Country* countryArray = reinterpret_cast<Country*>(countryRegion.data());

    // Copy the country data into the mapped region
    for (size_t i = 0; i < COUNTRY_COUNT; ++i, ++header->count) {
        std::memcpy(countryArray + i, &COUNTRY_DATA[i], sizeof(Country));
    }
    
    header->crc = computeCrc(countryArray, header->count);
    
    // At the end of this block, the mapped region and shared memory segments
    // go out of scope, but the shared memory and its data continue to live.
}

void TestSharedMemory::readMemory()
{
    // The unique key to the shared memory segment
    std::string key = "/mem1";
    
    // Create a shared memory segment, with read only privileges. If the segment
    // doesn't exist, this will throw an exception.
    aftipc::SharedMemory mem(
        aftio::AccessFlags::READ_ONLY, // open for reading (no writing)
        key); // the unique key of the shared memory segment

    // Create a mapped region of the shared memory segment that contains
    // the header information.
    size_t offset = 0;
    aftipc::MappedRegion headerRegion(mem, offset, sizeof(CountryHeader));
    
    CountryHeader* header = reinterpret_cast<CountryHeader*>(headerRegion.data());
    AUNIT_ASSERT(header->majorVersion == MAJOR_VERSION);
    AUNIT_ASSERT(header->minorVersion == MINOR_VERSION);
    AUNIT_ASSERT(header->count == COUNTRY_COUNT);
    
    aftipc::MappedRegion countryRegion(mem, sizeof(CountryHeader), header->count * sizeof(Country));
    Country* countryArray = reinterpret_cast<Country*>(countryRegion.data());
    
    for (size_t i = 0; i < header->count; ++i) {
        AUNIT_ASSERT(0 == strcmp(countryArray[i].isoCountryCode, COUNTRY_DATA[i].isoCountryCode));
        AUNIT_ASSERT(0 == strcmp(countryArray[i].isoCurrencyCode, COUNTRY_DATA[i].isoCurrencyCode));
        AUNIT_ASSERT(0 == strcmp(countryArray[i].enName, COUNTRY_DATA[i].enName));
    }
}

} // namespace
} // namespace
