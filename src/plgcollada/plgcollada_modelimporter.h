#ifndef INCLUDED_AEGIS_PLGCOLLADA_MODELIMPORTER_H
#define INCLUDED_AEGIS_PLGCOLLADA_MODELIMPORTER_H

#include <agtg_model.h>

namespace aegis {
namespace plgcollada {

class ModelImporter
{
public:
    ModelImporter();
    
    virtual ~ModelImporter();
    
    bool loadModel(
        agtg::Model* model,
        aftio::InputSource& source);
};

} // namespace
} // namespace

#endif // INCLUDED
