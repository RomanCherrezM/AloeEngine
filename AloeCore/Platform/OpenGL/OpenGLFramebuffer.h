#pragma once

#include <Render/Framebuffer.h>

namespace Aloe
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Regenerate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value);

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_specification; }
	private:
		uint32_t m_rendererID = 0;
		FramebufferSpecification m_specification;

		std::vector<FramebufferTextureSpecification> m_colorAttachmentSpecifications;
		FramebufferTextureSpecification m_depthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_colorAttachments;
		uint32_t m_depthAttachment = 0;
	};
}