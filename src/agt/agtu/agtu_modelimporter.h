#ifndef INCLUDED_AEGIS_AGTU_MODELIMPORTER_H
#define INCLUDED_AEGIS_AGTU_MODELIMPORTER_H

namespace aegis {
namespace agtu {

class ModelImporter
{
public:
    ModelImporter();
    
    virtual ~ModelImporter();
    
    bool load(
        agtg::Model* model,
        aftio::InputStream const& inputStream);
};

} // namespace
} // namespace

#endif // INCLUDED_AEGIS_AGTU_MODELIMPORTER_H
