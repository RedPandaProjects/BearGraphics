#include "BearGraphics.hpp"
BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty = NULL;
BearRHI::BearRHIInterface*Interface = NULL;
BearRHI::BearRHIDefaultManager*DefualtManager = NULL;

extern BearGraphics::BearVertexShaderRef* GDVertexShaders[BearGraphics::DVS_COUNT];
extern BearGraphics::BearPixelShaderRef* GDPixelShaders[BearGraphics::DPS_COUNT];
 void (*RHIInitialize)(void);
 void(*RHIDestroy)(void);

bool BearGraphics::BearRenderInterface::Initialize(const bchar * name)
{
	Destroy();
	if (!BearCore::BearProjectTool::CheckProject(name) )
	{
		Destroy();
		return false;
	}
	RHIInitialize =BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name,TEXT("RHIInitialize"));
	RHIDestroy = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RHIDestroy"));
	RHIInitialize();
	Interface = RHIFactoty->CreateInterface();
	DefualtManager = RHIFactoty->CreateDefaultManager();
	BearCore::bear_fill(GDVertexShaders);
	BearCore::bear_fill(GDPixelShaders);
	BearCore::BearLog::Printf(TEXT("BearGraphics build %s"), *BearCore::BearLog::GetBuild(2016, 11, 27));
	return true;
	
}

void BearGraphics::BearRenderInterface::AttachRenderTargetView(uint32 id, BearRenderTargetViewRef & viewport)
{
	if (Interface && !viewport.Empty())Interface->AttachRenderTargetView(id, viewport.m_data.get()->resource);
}

void BearGraphics::BearRenderInterface::AttachRenderTargetView(uint32 id, BearViewport & viewport)
{
	if (Interface && !viewport.Empty())Interface->AttachRenderTargetView(id, viewport.viewport);
}

void BearGraphics::BearRenderInterface::DetachRenderTargetView(uint32 id)
{
	if (Interface)Interface->DetachRenderTargetView(id);
}

void BearGraphics::BearRenderInterface::AttachDepthStencilView(BearDepthStencilViewRef & viewport)
{
	if (Interface && !viewport.Empty())Interface->AttachDepthStencilView( viewport.m_data.get()->resource);
}

void BearGraphics::BearRenderInterface::DetachDepthStencilView()
{
	if (Interface)Interface->DetachDepthStencilView();
}

void BearGraphics::BearRenderInterface::SetVertexState(const BearVertexStateRef & shader)
{
	if(Interface && !shader.Empty())Interface->SetVertexState(shader.m_data.get()->reosurce);
}

void BearGraphics::BearRenderInterface::SetVertexShader(const BearVertexShaderRef & shader)
{
	if (Interface && !shader.Empty())Interface->SetVertexShader(shader.m_data.get()->shader);
}

void BearGraphics::BearRenderInterface::SetPixelShader(const BearPixelShaderRef & shader)
{
	if (Interface && !shader.Empty())Interface->SetPixelShader(shader.m_data.get()->shader);
}

void BearGraphics::BearRenderInterface::SetIndexBuffer(const BearIndexBufferRef & shader)
{
	if (Interface && !shader.Empty())Interface->SetIndexBuffer(shader.m_data.get()->buffer);
}

void BearGraphics::BearRenderInterface::SetVertexBuffer(const BearVertexBufferRef & shader)
{
	if (Interface && !shader.Empty())Interface->SetVertexBuffer(shader.m_data.get()->buffer);
}

void BearGraphics::BearRenderInterface::Draw(bsize size, bsize possition, BearGraphics::BearDrawType mode)
{
	if (Interface)Interface->Draw(size, possition, mode);
}

void BearGraphics::BearRenderInterface::SetViewport( float x, float y, float width, float height, float minDepth, float maxDepth)
{
	if (Interface)Interface->SetViewport(x, y, width, height, minDepth, maxDepth);
}

void BearGraphics::BearRenderInterface::SetScissor( float x, float y, float x1, float y1)
{
	if (Interface)Interface->SetScissor( x, y, x1, y1);
}



void BearGraphics::BearRenderInterface::SetBlendState(const BearBlendStateRef & State, const BearCore::BearColor & color)
{
	if (Interface && !State.Empty())Interface->SetBlendState(State.m_data.get()->reosurce,color);
}

void BearGraphics::BearRenderInterface::SetDepthStencilState(const BearDepthStencilStateRef & State, uint32 StencilRef)
{
	if (Interface && !State.Empty())Interface->SetDepthStencilState(State.m_data.get()->reosurce, StencilRef);
}

void BearGraphics::BearRenderInterface::SetRasterizerState(const BearRasterizerStateRef & State)
{
	if (Interface && !State.Empty())Interface->SetRasterizerState(State.m_data.get()->reosurce);
}


void BearGraphics::BearRenderInterface::SetPixelShaderConstants(bsize slot, const BearShaderConstantsRef & consts)
{
	if (Interface && !consts.Empty())Interface->SetPixelShaderConstants(slot, consts.m_data->resource);
}

void BearGraphics::BearRenderInterface::SetPixelShaderResource(bsize slot, const BearTexture2DRef & texture2d, const BearSamplerStateRef & sampler)
{
	if (Interface&&!texture2d.Empty()&& !sampler.Empty()) Interface->SetPixelShaderResource(slot, texture2d.m_data.get()->resource,sampler.m_data.get()->reosurce);
}

void BearGraphics::BearRenderInterface::SetVertexShaderConstants(bsize slot, const BearShaderConstantsRef & consts)
{
	if (Interface && !consts.Empty())Interface->SetVertexShaderConstants(slot, consts.m_data->resource);
}


void BearGraphics::BearRenderInterface::Destroy()
{
	if (!RHIFactoty)return;
	BearDefaultManager::Clear();
	BearStats::TestForDestroy();

	RHIFactoty->DestroyInterface(Interface);
	RHIFactoty->DestroyDefaultManager(DefualtManager);

	if (RHIDestroy)RHIDestroy();
	RHIDestroy = 0;
	RHIInitialize = 0;
	Interface = 0;
}
void BearGraphics::BearRenderInterface::SetVertexShaderResource(bsize slot, const BearTexture2DRef & texture2d, const BearSamplerStateRef & sampler)
{
	if (Interface && !texture2d.Empty() && !sampler.Empty()) Interface->SetVertexShaderResource(slot, texture2d.m_data.get()->resource, sampler.m_data.get()->reosurce);
}
