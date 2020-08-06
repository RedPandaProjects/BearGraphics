#include "BearGraphics.hpp"
#include "BearRHI/BearRHIFactory.h"
#include "BearRHI/BearRHIStats.h"
BEARGRAPHICS_API BearRHI::BearRHIFactory* GFactory=0;
BEARGRAPHICS_API BearRHI::BearRHIStats* GStats = 0;
static BearStringConteniar LName;
bool BearRenderInterface::Initialize(BearStringConteniar name)
{
	Destroy();

	if (!BearManagerDynamicLibraries::CheckProject(name))
	{
		return false;
	}
	LName = name;
	auto RHIInitialize = BearManagerDynamicLibraries::GetFunctionInProject<void(*)()>(name, TEXT("RHIInitialize"));
	RHIInitialize();
	if (!GFactory)
	{
		Destroy();
		return false;
	}

	BEAR_CHECK(GStats);
	BEAR_PRINTF(TEXT("BearGraphics build %s"), *BearLog::GetBuild(2016, 11, 27));
	return true;
}

BearFactoryPointer<BearRHI::BearRHIViewport> BearRenderInterface::CreateViewport(void* Handle, bsize Width, bsize Height, bool fullscreen, const BearViewportDescription& Description, bool Vsync)
{
	if (GFactory)return GFactory->CreateViewport(Handle, Width, Height, fullscreen,Vsync,Description);
	return BearFactoryPointer<BearRHI::BearRHIViewport>();
}

BearFactoryPointer<BearRHI::BearRHIContext> BearRenderInterface::CreateContext()
{
	if (GFactory)return GFactory->CreateContext();
	return BearFactoryPointer<BearRHI::BearRHIContext>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreatePixelShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Pixel);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateComputeShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Compute);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateMeshShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Mesh);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateAmplificationShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Amplification);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateRayTracingShader()
{
	if (GFactory)return GFactory->CreateShader(ST_RayTracing);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateVertexShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Vertex);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateHullShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Hull);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateDomainShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Domain);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateGeometryShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Geometry);
	return BearFactoryPointer<BearRHI::BearRHIShader>();
}

BearFactoryPointer<BearRHI::BearRHIVertexBuffer> BearRenderInterface::CreateVertexBuffer()
{
	if (GFactory)return GFactory->CreateVertexBuffer();
	return BearFactoryPointer<BearRHI::BearRHIVertexBuffer>();
}

BearFactoryPointer<BearRHI::BearRHIIndexBuffer> BearRenderInterface::CreateIndexBuffer()
{
	if (GFactory)return GFactory->CreateIndexBuffer();
	return BearFactoryPointer<BearRHI::BearRHIIndexBuffer>();
}

BearFactoryPointer<BearRHI::BearRHIPipelineGraphics> BearRenderInterface::CreatePipelineGraphics(const BearPipelineGraphicsDescription& Descriptor)
{
	if (GFactory)return GFactory->CreatePipelineGraphics(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIPipelineGraphics>();
}

BearFactoryPointer<BearRHI::BearRHIPipelineMesh> BearRenderInterface::CreatePipelineMesh(const BearPipelineMeshDescription& Descriptor)
{
	if (GFactory)return GFactory->CreatePipelineMesh(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIPipelineMesh>();
}

BearFactoryPointer<BearRHI::BearRHIPipelineRayTracing> BearRenderInterface::CreatePipelineRayTracing(const BearPipelineRayTracingDescription& Descriptor)
{
	if (GFactory)return GFactory->CreatePipelineRayTracing(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIPipelineRayTracing>();
}

BearFactoryPointer<BearRHI::BearRHIBottomLevel> BearRenderInterface::CreateBottomLevel(const BearBottomLevelDescription& Descriptor)
{
	if (GFactory)return GFactory->CreateBottomLevel(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIBottomLevel>();
}

BearFactoryPointer<BearRHI::BearRHITopLevel> BearRenderInterface::CreateTopLevel(const BearTopLevelDescription& Descriptor)
{
	if (GFactory)return GFactory->CreateTopLevel(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHITopLevel>();
}


BearFactoryPointer<BearRHI::BearRHIRootSignature> BearRenderInterface::CreateRootSignature(const BearRootSignatureDescription& Descriptor)
{
	if (GFactory)return GFactory->CreateRootSignature(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIRootSignature>();
}

BearFactoryPointer<BearRHI::BearRHIDescriptorHeap> BearRenderInterface::CreateDescriptorHeap(const BearDescriptorHeapDescription& Descriptor)
{
	if (GFactory)return GFactory->CreateDescriptorHeap(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIDescriptorHeap>();
}

BearFactoryPointer<BearRHI::BearRHIUniformBuffer> BearRenderInterface::CreateUniformBuffer(bsize Stride, bsize Count, bool Dynamic)
{
	if (GFactory)return GFactory->CreateUniformBuffer(Stride,Count,Dynamic);
	return BearFactoryPointer<BearRHI::BearRHIUniformBuffer>();
}

BearFactoryPointer<BearRHI::BearRHITexture2D> BearRenderInterface::CreateTexture2D(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage , const void* data, bool UAV)
{
	if (GFactory)return GFactory->CreateTexture2D(Width, Height, Mips, Count, PixelFormat, TypeUsage,const_cast<void*>( data),UAV);
	return BearFactoryPointer<BearRHI::BearRHITexture2D>();
}

BearFactoryPointer<BearRHI::BearRHITextureCube> BearRenderInterface::CreateTextureCube(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage, const void* data)
{
	if (GFactory)return GFactory->CreateTextureCube(Width, Height, Mips, Count, PixelFormat, TypeUsage, const_cast<void*>(data));
	return BearFactoryPointer<BearRHI::BearRHITextureCube>();
}

BearFactoryPointer<BearRHI::BearRHIStructuredBuffer> BearRenderInterface::CreateStructuredBuffer(bsize Size, const void* Data, bool UAV)
{
	if (GFactory)return GFactory->CreateStructuredBuffer(Size, const_cast<void*>(Data), UAV);
	return BearFactoryPointer<BearRHI::BearRHIStructuredBuffer>();
}

BearFactoryPointer<BearRHI::BearRHISampler> BearRenderInterface::CreateSampler(const BearSamplerDescription& Description)
{
	if (GFactory)return GFactory->CreateSampler(Description);
	return BearFactoryPointer<BearRHI::BearRHISampler>();
}

BearFactoryPointer<BearRHI::BearRHITexture2D> BearRenderInterface::CreateTexture2D(bsize Width, bsize Height, BearRenderTargetFormat RTF)
{
	if (GFactory)return GFactory->CreateTexture2D(Width, Height, RTF);
	return BearFactoryPointer<BearRHI::BearRHITexture2D>();
}

BearFactoryPointer<BearRHI::BearRHITexture2D> BearRenderInterface::CreateTexture2D(bsize Width, bsize Height, BearDepthStencilFormat DSF)
{
	if (GFactory)return GFactory->CreateTexture2D(Width, Height, DSF);
	return BearFactoryPointer<BearRHI::BearRHITexture2D>();
}

BearFactoryPointer<BearRHI::BearRHIRenderPass> BearRenderInterface::CreateRenderPass(const BearRenderPassDescription& Description)
{
	if (GFactory)return GFactory->CreateRenderPass(Description);
	return BearFactoryPointer<BearRHI::BearRHIRenderPass>();
}

BearFactoryPointer<BearRHI::BearRHIFrameBuffer> BearRenderInterface::CreateFrameBuffer(const BearFrameBufferDescription& Description)
{
	if (GFactory)return GFactory->CreateFrameBuffer(Description);
	return BearFactoryPointer<BearRHI::BearRHIFrameBuffer>();
}


bool BearRenderInterface::RTXSupport()
{
	return false;
}

bool BearRenderInterface::MeshShaderSupport()
{
	if (GFactory)return GFactory->SupportMeshShader();
	return false;
}

void BearRenderInterface::Destroy()
{
	BearRenderStats::Cheak();

	if (GFactory)bear_delete(GFactory);
	if (GStats) bear_delete(GStats);
	GStats = nullptr;
	GFactory = nullptr;
	if ((*LName)[0])
	{
		BearManagerDynamicLibraries::UnLoad(LName);
	}
}

bool BearRenderInterface::Empty()
{
	return GFactory==nullptr;
}
