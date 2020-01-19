#include "BearGraphics.hpp"
#include "BearRHI/BearRHIFactory.h"
#include "BearRHI/BearRenderHardwareInterface.h"
BEARGRAPHICS_API BearRHI::BearRHIFactory* GFactory=0;
BEARGRAPHICS_API BearRHI::BearRenderHardwareInterface* GRenderHardwareInterface=0;

static BearStringConteniar LProjectName;
bool BearRenderInterface::Initialize(const bchar* name)
{
	Destroy();
	if (!BearManagerProjects::CheckProject(name))
	{
		Destroy();
		return false;
	}
	auto RHIInitialize = BearManagerProjects::GetFunctionInProject<void(*)(void)>(name, TEXT("RHIInitialize"));
	RHIInitialize();
	if (!GFactory)
	{
		Destroy();
		return false;
	}
	BearLog::Printf(TEXT("BearGraphics build %s"), *BearLog::GetBuild(2016, 11, 27));
	LProjectName = name;
	return true;
}

BearFactoryPointer<BearRHI::BearRHIViewport> BearRenderInterface::CreateViewport(BearWindow& Window, const BearViewportDescription& Description, bool Vsync)
{
	if (GFactory)return GFactory->CreateViewport(Window.GetWindowHandle(), Window.GetSize().x,Window.GetSize().y, Window.IsFullScreen(),Vsync,Description);
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

BearFactoryPointer<BearRHI::BearRHIShader> BearRenderInterface::CreateVertexShader()
{
	if (GFactory)return GFactory->CreateShader(ST_Vertex);
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

BearFactoryPointer<BearRHI::BearRHIPipeline> BearRenderInterface::CreatePipeline(const BearPipelineDescription& Descriptor)
{
	if (GFactory)return GFactory->CreatePipeline(Descriptor);
	return BearFactoryPointer<BearRHI::BearRHIPipeline>();
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

BearFactoryPointer<BearRHI::BearRHIUniformBuffer> BearRenderInterface::CreateUniformBuffer()
{
	if (GFactory)return GFactory->CreateUniformBuffer();
	return BearFactoryPointer<BearRHI::BearRHIUniformBuffer>();
}

BearFactoryPointer<BearRHI::BearRHITexture2D> BearRenderInterface::CreateTexture2D(bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, const void* data)
{
	if (GFactory)return GFactory->CreateTexture2D(Width, Height, Mips, Count, PixelFormat,const_cast<void*>( data));
	return BearFactoryPointer<BearRHI::BearRHITexture2D>();
}

BearFactoryPointer<BearRHI::BearRHISampler> BearRenderInterface::CreateSampler()
{
	if (GFactory)return GFactory->CreateSampler();
	return BearFactoryPointer<BearRHI::BearRHISampler>();
}


bool BearRenderInterface::RTXSupport()
{
	return false;
}

void BearRenderInterface::Destroy()
{
	if (LProjectName.size() == 0)return;
	if (GFactory)bear_delete(GFactory);
	if (GRenderHardwareInterface)bear_delete(GRenderHardwareInterface);
	GRenderHardwareInterface = nullptr;
	GFactory = nullptr;
	BearManagerProjects::UnLoad(LProjectName);
	LProjectName = TEXT("");
}

bool BearRenderInterface::Empty()
{
	return GFactory==nullptr;
}
