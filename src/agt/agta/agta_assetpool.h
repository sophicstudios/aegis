#ifndef INCLUDED_AEGIS_AGTA_ASSETPOOL_H
#define INCLUDED_AEGIS_AGTA_ASSETPOOL_H

#include <vector>

namespace agta {

template<typename T>
class AssetPool
{
public:
    AssetPool();

    AssetPool(size_t batchSize);

    ~AssetPool();

    size_t createAsset();

    void destroyAsset(size_t id);

    T& assetForId(size_t id);

public:
    static const size_t DEFAULT_BATCH_SIZE = 500;
    typedef std::vector<std::pair<bool, T> > AssetList;
    typedef std::vector<size_t> FreeAssetIdList;

    size_t m_batchSize;
    size_t m_count;
    AssetList m_assets;
    FreeAssetIdList m_freeAssetIds;
};

template<typename T>
AssetPool<T>::AssetPool()
: m_batchSize(DEFAULT_BATCH_SIZE),
  m_count(0),
  m_assets(DEFAULT_BATCH_SIZE)
{}

template<typename T>
AssetPool<T>::AssetPool(size_t batchSize)
: m_batchSize(batchSize),
  m_count(0),
  m_assets(batchSize)
{}

template<typename T>
AssetPool<T>::~AssetPool()
{}

template<typename T>
size_t AssetPool<T>::createAsset()
{
    size_t id;

    // if there are free asset ids, allocate from one of those.
    if (!m_freeAssetIds.empty())
    {
        id = m_freeAssetIds.back();
        m_freeAssetIds.pop_back();
    }
    else
    {
        id = ++m_count;
        if (id >= m_assets.size())
        {
            // hit the limit for assets
            throw std::exception();
        }
    }

    // Get the asset info at location 'id'
    std::pair<bool, T>& p = m_assets[id - 1];

    // Mark the asset as active
    p.first = true;

    return id;
};

template<typename T>
void AssetPool<T>::destroyAsset(size_t id)
{
    if (id >= m_assets.size())
    {
        throw std::exception();
    }

    std::pair<bool, T>& p = m_assets[id - 1];
    p.first = false;
    p.second = T();

    m_freeAssetIds.push_back(id);
}

template<typename T>
T& AssetPool<T>::assetForId(size_t id)
{
    if (id >= m_assets.size())
    {
        throw std::exception();
    }

    std::pair<bool, T>& p = m_assets[id - 1];

    // Verify the asset is active
    if (!p.first)
    {
        throw std::exception();
    }

    return p.second;
}

} // namespace

#endif // INCLUDED
