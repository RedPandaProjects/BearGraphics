#pragma once
class BEARGRAPHICS_API BearRenderInterface
{
	BEAR_CLASS_STATIC(BearRenderInterface);
public:
	static bool Initialize(const bchar* name);
	static BearFactoryPointer<BearRHI::BearRHIViewport> CreateViewport(BearWindow&Window,const BearViewportDescription& Description, bool Vsync=false);
	static BearFactoryPointer<BearRHI::BearRHIContext> CreateContext();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreatePixelShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateVertexShader();
	static BearFactoryPointer < BearRHI::BearRHIVertexBuffer> CreateVertexBuffer();
	static BearFactoryPointer < BearRHI::BearRHIIndexBuffer> CreateIndexBuffer();

	static BearFactoryPointer < BearRHI::BearRHIPipeline> CreatePipeline(const BearPipelineDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIRootSignature> CreateRootSignature(const BearRootSignatureDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIDescriptorHeap> CreateDescriptorHeap(const BearDescriptorHeapDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIUniformBuffer> CreateUniformBuffer();
	static BearFactoryPointer < BearRHI::BearRHITexture2D> CreateTexture2D(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat,const void* data);
	static BearFactoryPointer < BearRHI::BearRHISampler> CreateSampler();
	static bool RTXSupport();
	static void Destroy();
	static bool Empty();
};