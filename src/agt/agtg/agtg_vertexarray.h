#ifndef INCLUDED_AGTG_MESHBINDING_H
#define INCLUDED_AGTG_MESHBINDING_H

#include <agtg_shaderprogram.h>
#include <memory>

namespace agtg {

class VertexArray
{
public:
    typedef std::shared_ptr<agtg::ShaderProgram> ShaderProgramPtr;

    VertexArray(ShaderProgramPtr shaderProgram);

    ~VertexArray();

    void addMesh();

    void bind();
};

}
#endif // INCLUDED
