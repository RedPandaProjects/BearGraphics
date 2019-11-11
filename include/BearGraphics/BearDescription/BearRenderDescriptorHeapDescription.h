#pragma once
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderDescriptorHeapDescription
	{
	public:
		BearRenderDescriptorHeapDescription():CS(false){}
		BearRenderDescriptorHeapDescription(const BearRenderDescriptorHeapDescription&Right) { Copy(Right); }
		BearRenderDescriptorHeapDescription(BearRenderDescriptorHeapDescription&&Right) { Swap(Right); }
		inline ~BearRenderDescriptorHeapDescription() {}
		void Copy(const BearRenderDescriptorHeapDescription&Right);
		void Swap(BearRenderDescriptorHeapDescription&Right);
		inline BearRenderDescriptorHeapDescription&operator=(const BearRenderDescriptorHeapDescription&Right) { Copy(Right); return*this; }
		inline BearRenderDescriptorHeapDescription&operator=(BearRenderDescriptorHeapDescription&&Right) { Swap(Right); return*this; }
		struct UAVResource
		{
			BearFactoryPointer<BearRenderBase::BearRenderUnorderedAccessViewBase> UAVResource;
		}
		UAVResources[16];
		
		struct UniformBuffer
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
		}
		UniformBuffers[16];

		struct SRVResource
		{
			BearFactoryPointer<BearRenderBase::BearRenderShaderResourceViewBase> SRVResource;
		}
		SRVResources[16];

		struct Sampler
		{
			BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase> Sampler;
		}
		Samplers[16];
		bool CS;
		BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> RootSignature;
	};
}