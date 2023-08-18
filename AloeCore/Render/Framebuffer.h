#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Aloe {

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: m_textureFormat(format) {}

		FramebufferTextureFormat m_textureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: m_attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> m_attachments;
	};

	struct FramebufferSpecification
	{
		uint32_t m_width = 0, m_height = 0;
		FramebufferAttachmentSpecification m_attachments;
		uint32_t m_samples = 1;

		bool m_swapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};


}