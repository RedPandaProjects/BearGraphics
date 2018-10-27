#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
__declspec(dllexport) BearRHI::BearRHIStats*RHIStats=NULL;
uint16 BearGraphics::BearStats::GetCountIndexBuffer()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountIndexBuffer();
}

uint16 BearGraphics::BearStats::GetCountVertexBuffer()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountVertexBuffer();
}

uint16 BearGraphics::BearStats::GetCountPixelShader()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountPixelShader();
}

uint16 BearGraphics::BearStats::GetCountPixelShaderCompiler()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountPixelShaderCompiler();
}

uint16 BearGraphics::BearStats::GetCountVertexShader()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountVertexShader();
}

uint16 BearGraphics::BearStats::GetCountVertexShaderCompiler()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountVertexShaderCompiler();
}

uint16 BearGraphics::BearStats::GetCountRenderTargetView()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountRenderTargetView();
}

uint16 BearGraphics::BearStats::GetCountViewPort()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountViewPort();
}

uint16 BearGraphics::BearStats::GetCountDepthStencilView()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountDepthStencilView();
}

uint16 BearGraphics::BearStats::GetCountVertexInputLayout()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountVertexInputLayout();
}

uint16 BearGraphics::BearStats::GetCountTexture1D()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTexture1D();
}

uint16 BearGraphics::BearStats::GetCountTexture1DArray()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTexture1DArray();
}

uint16 BearGraphics::BearStats::GetCountTexture2D()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTexture2D();
}

uint16 BearGraphics::BearStats::GetCountTexture2DArray()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTexture2DArray();
}

uint16 BearGraphics::BearStats::GetCountTexture3D()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTexture3D();
}

uint16 BearGraphics::BearStats::GetCountTextureCubeMap()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTextureCubeMap();
}

uint16 BearGraphics::BearStats::GetCountTextureCubeMapArray()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountTextureCubeMapArray();
}

uint16 BearGraphics::BearStats::GetCountBlendState()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountBlendState();
}

uint16 BearGraphics::BearStats::GetCountSamplerState()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountSamplerState();
}

uint16 BearGraphics::BearStats::GetCountDepthStencilState()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountDepthStencilState();
}

uint16 BearGraphics::BearStats::GetCountRasterizerState()
{
	if (!RHIStats)return 0;
	return RHIStats->getCountRasterizerState();
}

void BearGraphics::BearStats::DumpToLog()
{
	/*BearCore::BearDebug::GetLog()->printf(TEXT("----------------------------BearGraphics Статус-----------------------------"));
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Index Buffer"), GetCountIndexBuffer());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Buffer"), GetCountVertexBuffer());

	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Pixel Shader"), GetCountPixelShader());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Pixel Shader Compiler"), GetCountPixelShaderCompiler());

	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Shader"), GetCountVertexShader());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Shader Compiler"), GetCountVertexShaderCompiler());

	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("RenderTarget View"), GetCountRenderTargetView());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("View Port"), GetCountViewPort());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("DepthStencil View"), GetCountDepthStencilView());

	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Vertex InputLayout"), GetCountVertexInputLayout());
	
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Texture1D"), GetCountTexture1D());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Texture1D Array"), GetCountTexture1DArray());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Texture2D"), GetCountTexture2D());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Texture2D Array"), GetCountTexture2DArray());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Texture3D"), GetCountTexture3D());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("TextureCubeMap"), GetCountTextureCubeMap());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("TextureCubeMap Array"), GetCountTextureCubeMapArray());

	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Blend State"), GetCountBlendState());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Sampler State"), GetCountSamplerState());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("DepthStencil State"), GetCountDepthStencilState());
	BearCore::BearDebug::GetLog()->printf(TEXT("Количество %s[%hu]"), TEXT("Rasterize State"), GetCountRasterizerState());
	BearCore::BearDebug::GetLog()->printf(TEXT("----------------------------------------------------------------------------"));*/
}

void BearGraphics::BearStats::TestForDestroy()
{
	BEAR_FATALERROR(!GetCountIndexBuffer() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Index Buffer"), GetCountIndexBuffer());
	BEAR_FATALERROR(!GetCountVertexBuffer(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Buffer"), GetCountVertexBuffer());

	BEAR_FATALERROR(!GetCountPixelShader() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Pixel Shader"), GetCountPixelShader());
	BEAR_FATALERROR(!GetCountPixelShaderCompiler() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Pixel Shader Compiler"), GetCountVertexShaderCompiler());

	BEAR_FATALERROR(!GetCountVertexShader(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Shader"), GetCountVertexShader());
	BEAR_FATALERROR(!GetCountVertexShaderCompiler(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Shader Compiler"), GetCountVertexShaderCompiler());

	BEAR_FATALERROR(!GetCountRenderTargetView() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("RenderTarget View"), GetCountRenderTargetView());
	BEAR_FATALERROR(!GetCountViewPort() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("View Port"), GetCountViewPort());
	BEAR_FATALERROR(!GetCountDepthStencilView(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("DepthStencil View"), GetCountDepthStencilView());

	BEAR_FATALERROR(!GetCountVertexInputLayout() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex InputLayout"), GetCountVertexShader());


	BEAR_FATALERROR(!GetCountTexture1D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture1D"), GetCountTexture1D());
	BEAR_FATALERROR(!GetCountTexture1DArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture1D Array"), GetCountTexture1DArray());
	BEAR_FATALERROR(!GetCountTexture2D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture2D"), GetCountTexture2D());
	BEAR_FATALERROR(!GetCountTexture2DArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture2D Array"), GetCountTexture2DArray());
	BEAR_FATALERROR(!GetCountTexture3D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture3D"), GetCountTexture3D());
	BEAR_FATALERROR(!GetCountTextureCubeMap(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("TextureCubeMap"), GetCountTextureCubeMap());
	BEAR_FATALERROR(!GetCountTextureCubeMapArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("TextureCubeMap Array"), GetCountTextureCubeMapArray());


	BEAR_FATALERROR(!GetCountBlendState(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Blend State"), GetCountBlendState());
	BEAR_FATALERROR(!GetCountSamplerState() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Sampler State"), GetCountSamplerState());
	BEAR_FATALERROR(!GetCountDepthStencilState() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("DepthStencil State"), GetCountDepthStencilState());
	BEAR_FATALERROR(!GetCountRasterizerState(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Rasterizer State"), GetCountRasterizerState());
}

#define  CREATE_RENDERRESOURCE_ARGUMENTS1 
#define  CREATE_RENDERRESOURCE_ARGUMENTS2

CREATE_RENDERRESOURCE_CLASS2(BlendState);
CREATE_RENDERRESOURCE_CLASS2(DepthStencilState);
CREATE_RENDERRESOURCE_CLASS2(SamplerState);
CREATE_RENDERRESOURCE_CLASS2(RasterizerState);
