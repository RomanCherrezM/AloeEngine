#ifndef ALOE_GL_SHADER_H
#define ALOE_GL_SHADER_H 1

#include <glad/glad.h>

#include <Render/Shader.h>

namespace Aloe {

    class OpenGLShader : public Shader {
    public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_name; }

	private:
		std::string ReadFile(const std::string& filepath);
		void CompileShaders();
		void CreateProgram();

		std::string m_name;
		u32 m_programRenderId;

		std::unordered_map<GLenum, u32> m_shaderRenderIds;
		std::unordered_map<GLenum, std::string> m_shaderSourceCode;


    };

}

#endif