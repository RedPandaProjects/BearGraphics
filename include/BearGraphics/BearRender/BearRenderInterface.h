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
		static BearFactoryPointer<BearRenderBase::BearRenderTexture2DBase> CreateTexture2D();
		static BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase> CreateSamplerState(const BearRenderSamplerDescription&Description);
		/*RTX*/
		static BearFactoryPointer<BearRenderBase::BearRenderShaderBase> CreateRayGenerationShader();
		static BearFactoryPointer<BearRenderBase::BearRenderShaderBase> CreateMissShader();
		static BearFactoryPointer<BearRenderBase::BearRenderShaderBase> CreateHitShader();

		static bool RTXSupport();
		static void Destroy();
		static bool Empty();
	};
}
