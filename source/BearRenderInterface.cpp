#include "BearGraphics.hpp"
BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty = NULL;
BearRHI::BearRHIInterface*Interface = NULL;

 void (__stdcall*RHIInitialize)(void);
 void(__stdcall*RHIDestroy)(void);

bool BearGraphics::BearRenderInterface::Initialize(const bchar * name)
{
	if (!BearCore::BearProjectTool::CheckProject(name) )
	{
		Destroy();
		return false;
	}
	RHIInitialize =BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name,TEXT("RHIInitialize"));
	RHIDestroy = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RHIDestroy"));
	RHIInitialize();
	Interface = RHIFactoty->createInterface();
	return true;
	
}

void BearGraphics::BearRenderInterface::AttachRenderTargetView(uint32 id, BearRenderTargetViewRef & viewport)
{
	if (Interface && !viewport.empty())Interface->attachRenderTargetView(id, viewport.m_data.get()->resource);
}

void BearGraphics::BearRenderInterface::AttachRenderTargetView(uint32 id, BearViewPortRef & viewport)
{
	if (Interface && !viewport.empty())Interface->attachRenderTargetView(id, viewport.m_data.get()->viewport);
}

void BearGraphics::BearRenderInterface::DetachRenderTargetView(uint32 id)
{
	if (Interface)Interface->detachRenderTargetView(id);
}

void BearGraphics::BearRenderInterface::AttachDepthStencilView(BearDepthStencilViewRef & viewport)
{
	if (Interface && !viewport.empty())Interface->attachDepthStencilView( viewport.m_data.get()->resource);
}

void BearGraphics::BearRenderInterface::DetachDepthStencilView()
{
	if (Interface)Interface->detachDepthStencilView();
}

void BearGraphics::BearRenderInterface::SetVertexInputLayout(const BearVertexInputLayoutRef & shader)
{
	if(Interface && !shader.empty())Interface->setVertexInputLayout(shader.m_data.get()->reosurce);
}

void BearGraphics::BearRenderInterface::SetVertexShader(const BearVertexShaderRef & shader)
{
	if (Interface && !shader.empty())Interface->setVertexShader(shader.m_data.get()->shader);
}

void BearGraphics::BearRenderInterface::SetPixelShader(const BearPixelShaderRef & shader)
{
	if (Interface && !shader.empty())Interface->setPixelShader(shader.m_data.get()->shader);
}

void BearGraphics::BearRenderInterface::SetIndexBuffer(const BearIndexBufferRef & shader)
{
	if (Interface && !shader.empty())Interface->setIndexBuffer(shader.m_data.get()->buffer);
}

void BearGraphics::BearRenderInterface::SetVertexBuffer(const BearVertexBufferRef & shader, uint32 stride)
{
	if (Interface && !shader.empty())Interface->setVertexBuffer(shader.m_data.get()->buffer,stride);
}

void BearGraphics::BearRenderInterface::Draw(bsize size, bsize possition, BearGraphics::BearDrawType mode)
{
	if (Interface)Interface->draw(size, possition, mode);
}

void BearGraphics::BearRenderInterface::SetViewport(uint32 id, float x, float y, float width, float height, float minDepth, float maxDepth)
{
	if (Interface)Interface->setViewport(id, x, y, width, height, minDepth, maxDepth);
}



void BearGraphics::BearRenderInterface::SetBlendState(const BearBlendStateRef & State, const BearCore::BearColor & color)
{
	if (Interface && !State.empty())Interface->setBlendState(State.m_data.get()->reosurce,color);
}

void BearGraphics::BearRenderInterface::SetDepthStencilState(const BearDepthStencilStateRef & State, uint32 StencilRef)
{
	if (Interface && !State.empty())Interface->setDepthStencilState(State.m_data.get()->reosurce, StencilRef);
}

void BearGraphics::BearRenderInterface::SetRasterizerState(const BearRasterizerStateRef & State)
{
	if (Interface && !State.empty())Interface->setRasterizerState(State.m_data.get()->reosurce);
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, float R)
{
	if (Interface) Interface->setItemInPixelShader(name, R);
}
void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, const BearCore::BearVector2<float>& RG)
{
	if (Interface) Interface->setItemInPixelShader(name, RG);
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, const BearCore::BearVector3<float>& RGB)
{
	if (Interface) Interface->setItemInPixelShader(name, RGB);
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, const BearCore::BearVector4<float>& RGBA)
{
	if (Interface) Interface->setItemInPixelShader(name, RGBA);
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, float R, float G)
{
	if (Interface) Interface->setItemInPixelShader(name, BearCore::BearVector2<float>(R,G));
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, float R, float G, float B)
{
	if (Interface) Interface->setItemInPixelShader(name, BearCore::BearVector3<float>(R, G,B));
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, float R, float G, float B, float A)
{
	if (Interface) Interface->setItemInPixelShader(name, BearCore::BearVector4<float>(R, G,B,A));
}

void BearGraphics::BearRenderInterface::SetItemInPixelShader(const char * name, const BearTexture2DRef & texture2d, const BearSamplerStateRef & sampler)
{
	if (Interface&&!texture2d.empty()&& !sampler.empty()) Interface->setItemInPixelShader(name, texture2d.m_data.get()->resource,sampler.m_data.get()->reosurce);
}


void BearGraphics::BearRenderInterface::Destroy()
{
	BearStats::TestForDestroy();
	if(RHIFactoty&&Interface)
	RHIFactoty->destroyInterface(Interface);
	if (RHIDestroy)RHIDestroy();
	RHIDestroy = 0;
	RHIInitialize = 0;
	Interface = 0;
}
void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, float R)
{
	if (Interface) Interface->setItemInVertexShader(name, R);
}
void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, const BearCore::BearVector2<float>& RG)
{
	if (Interface) Interface->setItemInVertexShader(name, RG);
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, const BearCore::BearVector3<float>& RGB)
{
	if (Interface) Interface->setItemInVertexShader(name, RGB);
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, const BearCore::BearVector4<float>& RGBA)
{
	if (Interface) Interface->setItemInVertexShader(name, RGBA);
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, float R, float G)
{
	if (Interface) Interface->setItemInVertexShader(name, BearCore::BearVector2<float>(R, G));
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, float R, float G, float B)
{
	if (Interface) Interface->setItemInVertexShader(name, BearCore::BearVector3<float>(R, G, B));
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, float R, float G, float B, float A)
{
	if (Interface) Interface->setItemInVertexShader(name, BearCore::BearVector4<float>(R, G, B, A));
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, const BearTexture2DRef & texture2d, const BearSamplerStateRef & sampler)
{
	if (Interface && !texture2d.empty() && !sampler.empty()) Interface->setItemInVertexShader(name, texture2d.m_data.get()->resource, sampler.m_data.get()->reosurce);
}

void BearGraphics::BearRenderInterface::SetItemInVertexShader(const char * name, const BearCore::BearMatrix & matrix)
{
	if (Interface) Interface->setItemInVertexShader(name, matrix);
}
