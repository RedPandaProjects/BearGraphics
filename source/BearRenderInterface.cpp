#include "BearGraphics.hpp"

static void(*FInitialize)(void);
static void(*FDestroy)(void);
BEARPROJECT_EXPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
bool BearGraphics::BearRenderInterface::Initialize(const bchar * name)
{
	Destroy();
	if (!BearCore::BearProjectTool::CheckProject(name))
	{
		return false;
	}
	FInitialize = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RenderInitialize"));
	FDestroy = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RenderDestroy"));
	if (!FInitialize || !FDestroy)return false;
	FInitialize();
	if (!GRenderFactoty)
	{
		Destroy();
		return false;

	}
	return true;
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderContextBase> BearGraphics::BearRenderInterface::CreateContext()
{
	if(Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderContextBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderContextBase>(GRenderFactoty->CreateContext());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderPipelineBase> BearGraphics::BearRenderInterface::CreatePipeline(const BearRenderPipelineDescription & Descripter)
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderPipelineBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderPipelineBase>(GRenderFactoty->CreatePipeline(Descripter));

}
BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderPipelineBase> BearGraphics::BearRenderInterface::CreatePipeline(const BearRenderRTXPipelineDescription & Descripter)
{
	if (Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderPipelineBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderPipelineBase>(GRenderFactoty->CreatePipeline(Descripter));
}
BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderShaderBase> BearGraphics::BearRenderInterface::CreatePixelShader()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>(GRenderFactoty->CreateShader(ST_Pixel));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderShaderBase> BearGraphics::BearRenderInterface::CreateVertexShader()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>(GRenderFactoty->CreateShader(ST_Vertex));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase> BearGraphics::BearRenderInterface::CreateVertexBuffer()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase>(GRenderFactoty->CreateVertexBuffer());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase> BearGraphics::BearRenderInterface::CreateIndexBuffer()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase>(GRenderFactoty->CreateIndexBuffer());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> BearGraphics::BearRenderInterface::CreateUniformBuffer()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase>(GRenderFactoty->CreateUniformBuffer());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderViewportBase> BearGraphics::BearRenderInterface::CreateViewport(const BearWindow&Window, const BearRenderViewportDescription&Description)
{
	if (Empty()|| Window.Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderViewportBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderViewportBase>(GRenderFactoty->CreateViewport(Window.GetWindowHandle(), Window.GetSize().x, Window.GetSize().y, Window.IsFullScreen(),false, Description));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderTargetViewBase> BearGraphics::BearRenderInterface::CreateRenderTarget(const BearRenderTargetViewDescription & Description)
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderTargetViewBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderTargetViewBase>(GRenderFactoty->CreateTargetView(Description));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderFrameBufferBase> BearGraphics::BearRenderInterface::CreateFrameBuffer(const BearRenderFrameBufferDescription & Description)
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderFrameBufferBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderFrameBufferBase>(GRenderFactoty->CreateFrameBuffer(Description));
}


BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> BearGraphics::BearRenderInterface::CreateRootSignature(const BearRenderRootSignatureDescription & Description)
{
	if (Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase>(GRenderFactoty->CreateRootSignature(Description));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderDescriptorHeapBase> BearGraphics::BearRenderInterface::CreateDescriptorHeap(const BearRenderDescriptorHeapDescription & Description)
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderDescriptorHeapBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderDescriptorHeapBase>(GRenderFactoty->CreateDescriptorHeap(Description));

}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderTexture2DBase> BearGraphics::BearRenderInterface::CreateTexture2D()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderTexture2DBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderTexture2DBase>(GRenderFactoty->CreateTexture2D());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderTexture2DUAVBase> BearGraphics::BearRenderInterface::CreateTexture2DUAV()
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderTexture2DUAVBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderTexture2DUAVBase>(GRenderFactoty->CreateTexture2DUAV());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase> BearGraphics::BearRenderInterface::CreateSamplerState(const BearRenderSamplerDescription & Description)
{
	if (Empty())
	return BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderSamplerStateBase>(GRenderFactoty->CreateSamplerState(Description));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderShaderBase> BearGraphics::BearRenderInterface::CreateRayGenerationShader()
{
	if (Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>(GRenderFactoty->CreateShader(ST_RayGeneration));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderShaderBase> BearGraphics::BearRenderInterface::CreateMissShader()
{
	if (Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>(GRenderFactoty->CreateShader(ST_Miss));
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderShaderBase> BearGraphics::BearRenderInterface::CreateHitShader()
{
	if (Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderShaderBase>(GRenderFactoty->CreateShader(ST_Hit));
}

bool BearGraphics::BearRenderInterface::RTXSupport()
{
	return false;
}

void BearGraphics::BearRenderInterface::Destroy()
{
	if (FDestroy)
	{
		FDestroy();
		FDestroy = 0;
		FInitialize = 0;
	}
}

bool BearGraphics::BearRenderInterface::Empty()
{
	return GRenderFactoty==0;
}
