#include "OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>

namespace Aloe {

    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        m_shaderSourceCode[GL_VERTEX_SHADER] = ReadFile(vertexPath);
        m_shaderSourceCode[GL_FRAGMENT_SHADER] = ReadFile(fragmentPath);

        CompileShaders();

        CreateProgram();
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_name(name)
    {
        m_shaderSourceCode[GL_VERTEX_SHADER] = vertexSrc;
        m_shaderSourceCode[GL_FRAGMENT_SHADER] = fragmentSrc;

        CompileShaders();

        CreateProgram();
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_programRenderId);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream stream(filepath, std::ios::in | std::ios::binary);
        if (stream)
        {
            stream.seekg(0, std::ios::end);
            size_t size = stream.tellg();
            if (size != -1)
            {
                result.resize(size);
                stream.seekg(0, std::ios::beg);
                stream.read(&result[0], size);
            }
            else 
            {
                printf("\n Could not read file: %s", filepath.c_str());
            }
        }
        else 
        {
            printf("\n Could not open file: %s", filepath.c_str());
        }

        return result;
    }

    void OpenGLShader::CompileShaders()
    {
        for (auto&& [shaderType, shaderSource] : m_shaderSourceCode)
        {
            //Set shader data
            u32& shaderID = m_shaderRenderIds[shaderType];

            shaderID = glCreateShader(shaderType);

            const char* data = shaderSource.c_str();
            glShaderSource(shaderID, 1, &data, NULL);

            //Compile and check Error
            glCompileShader(shaderID);
            int success;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                GLint maxLength = 0;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

                printf("\n [ERROR] [SHADER] : Compile error %s", &errorLog[0]);

                // Exit with failure.
                glDeleteShader(shaderID);
            }
        }
    }

    void OpenGLShader::CreateProgram()
    {
        u32 program = glCreateProgram();

        for (auto&& [shaderType, shaderId] : m_shaderRenderIds)
        {
            glAttachShader(program, shaderId);
        }

        glLinkProgram(program);

        GLint isLinked;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
            printf("\n Shader linking failed: %s - %s", m_name.c_str(), infoLog.data());

            glDeleteProgram(program);

            for (auto&& [shaderType, shaderId] : m_shaderRenderIds)
            {
                glDeleteShader(shaderId);
            }
        }

        for (auto&& [shaderType, shaderId] : m_shaderRenderIds)
        {
            glDetachShader(program, shaderId);
            glDeleteShader(shaderId);
        }

        m_programRenderId = program;
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_programRenderId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
    }

    void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
    }
}