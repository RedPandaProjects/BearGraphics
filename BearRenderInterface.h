#pragma once
class BEARGRAPHICS_API BearRenderInterface
{
public:
	static bool Initialize(BearStringConteniar name);
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateVertexShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateHullShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateDomainShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateGeometryShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreatePixelShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateComputeShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateMeshShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateAmplificationShader();
	static BearFactoryPointer<BearRHI::BearRHIShader> CreateRayTracingShader();

	static BearFactoryPointer<BearRHI::BearRHIViewport> CreateViewport(void*Handle,bsize Width,bsize Height,bool fullscreen,const BearViewportDescription& Description, bool Vsync=false);
	static BearFactoryPointer<BearRHI::BearRHIContext> CreateContext();
	static BearFactoryPointer < BearRHI::BearRHIVertexBuffer> CreateVertexBuffer();
	static BearFactoryPointer < BearRHI::BearRHIIndexBuffer> CreateIndexBuffer();

	static BearFactoryPointer < BearRHI::BearRHIPipelineGraphics> CreatePipelineGraphics(const BearPipelineGraphicsDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIPipelineMesh> CreatePipelineMesh(const BearPipelineMeshDescription& Descriptor);

	static BearFactoryPointer < BearRHI::BearRHIRootSignature> CreateRootSignature(const BearRootSignatureDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIDescriptorHeap> CreateDescriptorHeap(const BearDescriptorHeapDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIUniformBuffer> CreateUniformBuffer(bsize Stride, bsize Count, bool Dynamic);
	static BearFactoryPointer < BearRHI::BearRHITexture2D> CreateTexture2D(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage = TU_STATIC,const void* data=0,bool UAV=false);
	static BearFactoryPointer < BearRHI::BearRHITextureCube> CreateTextureCube(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage = TU_STATIC, const void* data = 0);
	static BearFactoryPointer<BearRHI::BearRHIStructuredBuffer> CreateStructuredBuffer(bsize Size, const void* Data, bool UAV = false);
	static BearFactoryPointer < BearRHI::BearRHISampler> CreateSampler(const BearSamplerDescription& Description);

	static BearFactoryPointer < BearRHI::BearRHITexture2D> CreateTexture2D(bsize Width, bsize Height, BearRenderTargetFormat RTF);
	static BearFactoryPointer < BearRHI::BearRHITexture2D> CreateTexture2D(bsize Width, bsize Height, BearDepthStencilFormat DSF);
	static BearFactoryPointer < BearRHI::BearRHIRenderPass> CreateRenderPass(const BearRenderPassDescription& Description);
	static BearFactoryPointer < BearRHI::BearRHIFrameBuffer> CreateFrameBuffer(const BearFrameBufferDescription& Description);

	static BearFactoryPointer < BearRHI::BearRHIPipelineRayTracing> CreatePipelineRayTracing(const BearPipelineRayTracingDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIBottomLevel> CreateBottomLevel(const BearBottomLevelDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHITopLevel> CreateTopLevel(const BearTopLevelDescription& Descriptor);
	static BearFactoryPointer < BearRHI::BearRHIRayTracingShaderTable> CreateRayTracingShaderTable(const BearRayTracingShaderTableDescription& Descriptor);

	static bool RTXSupport();
	static bool MeshShaderSupport();
	static void Destroy();
	static bool Empty();
};