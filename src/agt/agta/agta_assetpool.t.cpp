#include <agta_assetpool.h>
#include <aunit.h>

namespace agta {

using namespace aunit;

struct Dummy {
    size_t value;
};

Describe d("agta_assetpool", []
{
    it("Constructor", [&]
    {
        agta::AssetPool<Dummy> pool;

        // verify the AssetPool is empty and throws an exception
        // when trying to access an asset by Id.
        bool e = false;
        try {
            pool.assetForId(0);
        } catch (...) {
            e = true;
        }

        expect(e).toBeTrue();
    });

    it("Create Asset", [&]
    {
        agta::AssetPool<Dummy> pool;

        std::pair<size_t, Dummy> asset1 = pool.createAsset();
        std::pair<size_t, Dummy> asset2 = pool.createAsset();
        expect(asset2.first != asset1.first).toBeTrue();
    });

    it("Destroy Asset", [&]
    {
        agta::AssetPool<Dummy> pool;
        std::pair<size_t, Dummy> asset = pool.createAsset();
        pool.destroyAsset(asset.first);

        bool e = false;
        try {
            pool.assetForId(asset.first);
        } catch (...) {
            e = true;
        }

        expect(e).toBeTrue();
    });

    it("Get Asset", [&]
    {
        agta::AssetPool<Dummy> pool;
        std::pair<size_t, Dummy> asset = pool.createAsset();

        Dummy& dummy1 = pool.assetForId(asset.first);
        dummy1.value = 5;

        Dummy& dummy2 = pool.assetForId(asset.first);
        expect(dummy2.value).toEqual(5);
    });
});

} // namespace

