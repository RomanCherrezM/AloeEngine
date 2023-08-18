#include "OpenGLTexture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Aloe
{
	OpenGLTexture::OpenGLTexture(const TextureSpecification& specification)
		: m_Specification(specification), m_Width(m_Specification.Width), m_Height(m_Specification.Height)
	{
		m_assetSpec.m_state = AssetState::Unloaded;
		m_assetSpec.m_type = AssetType::Texture;
	}

	OpenGLTexture::OpenGLTexture(const std::string& path)
	{
		m_assetSpec.m_state = AssetState::Unloaded;
		m_assetSpec.m_type = AssetType::Texture;
		m_assetSpec.m_path = path;
	}

	void OpenGLTexture::Load()
	{
		if (m_assetSpec.m_path == "") 
		{
			m_Width = m_Specification.Width;
			m_Height = m_Specification.Height;
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// Set default values to 1
			uint8_t whitePixel[] = { 255, 255, 255 };
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, whitePixel);

			m_assetSpec.m_state = AssetState::Loaded;
		}
		else
		{

			int width, height, channels;
			stbi_set_flip_vertically_on_load(1);
			stbi_uc* data = nullptr;
			{
				data = stbi_load(m_assetSpec.m_path.c_str(), &width, &height, &channels, 0);
			}

			if (data)
			{
				m_assetSpec.m_state = AssetState::Loaded;

				m_Width = width;
				m_Height = height;

				GLenum internalFormat = 0, dataFormat = 0;
				if (channels == 4)
				{
					internalFormat = GL_RGBA8;
					dataFormat = GL_RGBA;
				}
				else if (channels == 3)
				{
					internalFormat = GL_RGB8;
					dataFormat = GL_RGB;
				}

				m_InternalFormat = internalFormat;
				m_DataFormat = dataFormat;

				glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
				glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

				glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

				stbi_image_free(data);
			}
		}
	}

	void OpenGLTexture::Unload()
	{
		m_assetSpec.m_state = AssetState::Unloaded;
		m_assetSpec.m_path = "";

		glDeleteTextures(1, &m_RendererID);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		Unload();
	}

	void OpenGLTexture::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}