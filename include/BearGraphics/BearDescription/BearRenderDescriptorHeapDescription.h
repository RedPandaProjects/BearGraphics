#pragma once
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderDescriptorHeapDescription
	{
	public:
		BearRenderDescriptorHeapDescription() {}
		BearRenderDescriptorHeapDescription(const BearRenderDescriptorHeapDescription&Right) { Copy(Right); }
		BearRenderDescriptorHeapDescription(BearRenderDescriptorHeapDescription&&Right) { Swap(Right); }
		inline ~BearRenderDescriptorHeapDescription() {}
		void Copy(const BearRenderDescriptorHeapDescription&Right);
		void Swap(BearRenderDescriptorHeapDescription&Right);
		inline BearRenderDescriptorHeapDescription&operator=(const BearRenderDescriptorHeapDescription&Right) { Copy(Right); return*this; }
		inline BearRenderDescriptorHeapDescription&operator=(BearRenderDescriptorHeapDescription&&Right) { Swap(Right); return*this; }
		struct UniformBuffer
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
		}
		UniformBuffers[16];

		struct TextureBuffer
		{
			BearFactoryPointer<BearRenderBase::BearRenderTexture2DBase> Texture;
		}
		TextureBuffers[16];

		struct SamplerBuffer
		{
			BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase> Sampler;
		}
		SamplerBuffers[16];

		BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> RootSignature;
	};
}