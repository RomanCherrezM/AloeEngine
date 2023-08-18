#include <Render/Shader.h>

#include <Platform/OpenGL/OpenGLShader.h>

namespace Aloe {

    std::shared_ptr<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
    {
        return std::make_shared<OpenGLShader>(vertexPath, fragmentPath);
    }

    std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

}