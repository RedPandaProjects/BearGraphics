#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearRenderInterface
	{
		BEAR_CLASS_STATIC(BearRenderInterface);
	public:
		static bool Initialize(const bchar*name);
		static BearFactoryPointer<BearRenderBase::BearRenderContextBase> CreateContext();
		static BearFactoryPointer<BearRenderBase::BearRenderPipelineBase> CreatePipeline(const BearRenderPipelineDescription&Descripter);
		static BearFactoryPointer<BearRenderBase::BearRenderShaderBase> CreatePixelShader();
		static BearFactoryPointer<BearRenderBase::BearRenderShaderBase> CreateVertexShader();
		static BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase> CreateVertexBuffer();
		static BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase> CreateIndexBuffer();
		static BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> CreateUniformBuffer();
		static BearFactoryPointer<BearRenderBase::BearRenderViewportBase> CreateViewport(const BearWindow&Window,const BearRenderViewportDescription&Description);

		static BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> CreateRootSignature(const BearRenderRootSignatureDescription&Description);
		static BearFactoryPointer<BearRenderBase::BearRenderDescriptorHeapBase> CreateDescriptorHeap(const BearRenderDescriptorHeapDescription&Description);

		static void Destroy();
		static bool Empty();
	};
}
