#include "OpenGLFramebuffer.h"

#include <Render/Framebuffer.h>

#include <glad/glad.h>

namespace Aloe
{
	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {

		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

			return false;
		}

		static GLenum HazelFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			return 0;
		}

	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_specification(spec)
	{
		for (auto spec : m_specification.m_attachments.m_attachments)
		{
			if (!Utils::IsDepthFormat(spec.m_textureFormat))
				m_colorAttachmentSpecifications.emplace_back(spec);
			else
				m_depthAttachmentSpecification = spec;
		}

		Regenerate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_rendererID);
		glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
		glDeleteTextures(1, &m_depthAttachment);
	}

	void OpenGLFramebuffer::Regenerate()
	{
		if (m_rendererID)
		{
			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
			glDeleteTextures(1, &m_depthAttachment);

			m_colorAttachments.clear();
			m_depthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

		bool multisample = m_specification.m_samples > 1;

		// Attachments
		if (m_colorAttachmentSpecifications.size())
		{
			m_colorAttachments.resize(m_colorAttachmentSpecifications.size());
			Utils::CreateTextures(multisample, m_colorAttachments.data(), m_colorAttachments.size());

			for (size_t i = 0; i < m_colorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, m_colorAttachments[i]);
				switch (m_colorAttachmentSpecifications[i].m_textureFormat)
				{
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_colorAttachments[i], m_specification.m_samples, GL_RGBA8, GL_RGBA, m_specification.m_width, m_specification.m_height, i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_colorAttachments[i], m_specification.m_samples, GL_R32I, GL_RED_INTEGER, m_specification.m_width, m_specification.m_height, i);
					break;
				}
			}
		}

		if (m_depthAttachmentSpecification.m_textureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &m_depthAttachment, 1);
			Utils::BindTexture(multisample, m_depthAttachment);
			switch (m_depthAttachmentSpecification.m_textureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_depthAttachment, m_specification.m_samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_specification.m_width, m_specification.m_height);
				break;
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		glViewport(0, 0, m_specification.m_width, m_specification.m_height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			return;
		}
		m_specification.m_width = width;
		m_specification.m_height = height;

		Regenerate();
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		auto& spec = m_colorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(m_colorAttachments[attachmentIndex], 0,
			Utils::HazelFBTextureFormatToGL(spec.m_textureFormat), GL_INT, &value);
	}
	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t index) const
	{
		return m_colorAttachments[index];
	}
}
