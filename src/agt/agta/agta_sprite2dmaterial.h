#ifndef INCLUDED_AGTA_SPRITE2DMATERIAL_H
#define INCLUDED_AGTA_SPRITE2DMATERIAL_H

#include <agtg_shaderprogram.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
#include <memory>

namespace agta {

class Sprite2dMaterial
{
public:
    typedef std::shared_ptr<aftfs::FileSystem> FileSystemPtr;

    Sprite2dMaterial(FileSystemPtr fileSystem);

    ~Sprite2dMaterial();

    afth::UUID const& id() const;

private:
    afth::UUID m_id;
    std::shared_ptr<agtg::ShaderProgram> m_shaderProgram;
};

} // namespace

#endif // INCLUDED
