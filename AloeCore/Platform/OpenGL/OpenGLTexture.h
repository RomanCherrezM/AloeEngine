#pragma once

#include <Render/Texture.h>

#include <glad/glad.h>

namespace Aloe 
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const TextureSpecification& specification);
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();

		virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == other.GetRendererID();
		}

		// Asset
		virtual void Load() override;
		virtual void Unload() override;

	private:
		TextureSpecification m_Specification;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
