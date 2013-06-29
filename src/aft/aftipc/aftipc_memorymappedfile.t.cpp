#include <aftipc_memorymappedfile.h>
#include <aftipc_mappedregion.h>
#include <afth_crc32.h>
#include <aftu_hexprinter.h>
#include <aunit.h>
#include <iostream>

namespace aegis {
namespace aftipc {

namespace {

static const size_t MAJOR_VERSION=1;
static const size_t MINOR_VERSION=0;
static const char* FILENAME="./shared_file.dat";

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

} // namespace

class TestMemoryMappedFile : public aunit::TestFixture
{
public:
    TestMemoryMappedFile() {}

    virtual ~TestMemoryMappedFile() {}

protected:
    virtual void runTest();
    
private:
    void loadFile();
    void readFile();
};

AUNIT_REGISTERTEST(TestMemoryMappedFile);

void TestMemoryMappedFile::runTest()
{
    loadFile();
    readFile();
}

void TestMemoryMappedFile::loadFile()
{    
    std::string filename = FILENAME;

    // calculate how much memory we need to store the data
    size_t countryDataSize = COUNTRY_COUNT * sizeof(Country);
    size_t totalSize = sizeof(CountryHeader) + countryDataSize;

    // create the memory mapped file with enough room for the initial header
    // plus all the country data.
    aftipc::MemoryMappedFile file(
        aftio::OpenFlags::CREATE_OR_OPEN, // open file or create if doesn't exist
        aftio::AccessFlags::READ_WRITE, // open for reading and writing
        filename, // the file name
        totalSize); // the size of the file in bytes
    
    // Create a mapped region of the memory mapped file to hold the
    // header information.
    size_t offset = 0;
    aftipc::MappedRegion headerRegion(file, offset, sizeof(CountryHeader));

    // Fill in the initial details of the header
    CountryHeader* header = reinterpret_cast<CountryHeader*>(headerRegion.data());
    std::memset(header, 0, sizeof(CountryHeader));

    header->majorVersion = MAJOR_VERSION;
    header->minorVersion = MINOR_VERSION;

    // Create a mapped region of the memory mapped file to hold the
    // data for all the countries in the array.
    aftipc::MappedRegion countryRegion(file, sizeof(CountryHeader), countryDataSize);
    Country* countryArray = reinterpret_cast<Country*>(countryRegion.data());

    // Copy the country data into the mapped region
    for (size_t i = 0; i < COUNTRY_COUNT; ++i, ++header->count) {
        std::memcpy(countryArray + i, &COUNTRY_DATA[i], sizeof(Country));
    }
    
    header->crc = computeCrc(countryArray, header->count);
    
    // At the end of this block, the mapped region and memory mapped file
    // go out of scope, but the shared memory and its data continues to live.
}

void TestMemoryMappedFile::readFile()
{
    std::string filename = FILENAME;
    
    aftipc::MemoryMappedFile file(
        aftio::AccessFlags::READ_ONLY,
        filename);
    
    size_t offset = 0;
    aftipc::MappedRegion headerRegion(file, offset, sizeof(CountryHeader));
    
    const CountryHeader* header = reinterpret_cast<const CountryHeader*>(headerRegion.data());
    AUNIT_ASSERT(header->majorVersion == MAJOR_VERSION);
    AUNIT_ASSERT(header->minorVersion == MINOR_VERSION);
    AUNIT_ASSERT(header->count == COUNTRY_COUNT);
    
    size_t countryDataSize = header->count * sizeof(Country);
    aftipc::MappedRegion countryRegion(file, sizeof(CountryHeader), countryDataSize);
    Country* countryArray = reinterpret_cast<Country*>(countryRegion.data());
    
    for (size_t i = 0; i < header->count; ++i) {
        AUNIT_ASSERT(0 == strcmp(countryArray[i].isoCountryCode, COUNTRY_DATA[i].isoCountryCode));
        AUNIT_ASSERT(0 == strcmp(countryArray[i].isoCurrencyCode, COUNTRY_DATA[i].isoCurrencyCode));
        AUNIT_ASSERT(0 == strcmp(countryArray[i].enName, COUNTRY_DATA[i].enName));        
    }
    
}

} // namespace
} // namespace
