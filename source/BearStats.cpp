#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
__declspec(dllexport) BearRHI::BearRHIStats*RHIStats=NULL;
uint16 BearGraphics::BearStats::GetCountIndexBuffer()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountIndexBuffer();
}

uint16 BearGraphics::BearStats::GetCountVertexBuffer()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountVertexBuffer();
}

uint16 BearGraphics::BearStats::GetCountPixelShader()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountPixelShader();
}

uint16 BearGraphics::BearStats::GetCountPixelShaderCompiler()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountPixelShaderCompiler();
}

uint16 BearGraphics::BearStats::GetCountVertexShader()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountVertexShader();
}

uint16 BearGraphics::BearStats::GetCountVertexShaderCompiler()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountVertexShaderCompiler();
}

uint16 BearGraphics::BearStats::GetCountRenderTargetView()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountRenderTargetView();
}

uint16 BearGraphics::BearStats::GetCountViewPort()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountViewPort();
}

uint16 BearGraphics::BearStats::GetCountDepthStencilView()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountDepthStencilView();
}

uint16 BearGraphics::BearStats::GetCountShaderConstants()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountShaderConstants();
}

uint16 BearGraphics::BearStats::GetCountVertexState()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountVertexState();
}

uint16 BearGraphics::BearStats::GetCountTexture1D()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTexture1D();
}

uint16 BearGraphics::BearStats::GetCountTexture1DArray()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTexture1DArray();
}

uint16 BearGraphics::BearStats::GetCountTexture2D()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTexture2D();
}

uint16 BearGraphics::BearStats::GetCountTexture2DArray()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTexture2DArray();
}

uint16 BearGraphics::BearStats::GetCountTexture3D()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTexture3D();
}

uint16 BearGraphics::BearStats::GetCountTextureCubeMap()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTextureCubeMap();
}

uint16 BearGraphics::BearStats::GetCountTextureCubeMapArray()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountTextureCubeMapArray();
}

uint16 BearGraphics::BearStats::GetCountBlendState()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountBlendState();
}

uint16 BearGraphics::BearStats::GetCountSamplerState()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountSamplerState();
}

uint16 BearGraphics::BearStats::GetCountDepthStencilState()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountDepthStencilState();
}

uint16 BearGraphics::BearStats::GetCountRasterizerState()
{
	if (!RHIStats)return 0;
	return RHIStats->GetCountRasterizerState();
}

void BearGraphics::BearStats::DumpToLog()
{
	BearCore::BearLog::Printf(TEXT("----------------------------BearGraphics Статус-----------------------------"));
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Index Buffer"), GetCountIndexBuffer());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Buffer"), GetCountVertexBuffer());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Pixel Shader"), GetCountPixelShader());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Pixel Shader Compiler"), GetCountPixelShaderCompiler());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Shader"), GetCountVertexShader());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Vertex Shader Compiler"), GetCountVertexShaderCompiler());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("RenderTarGet View"), GetCountRenderTargetView());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("View Port"), GetCountViewPort());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("DepthStencil View"), GetCountDepthStencilView());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Shader Constants"), GetCountShaderConstants());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Texture1D"), GetCountTexture1D());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Texture1D Array"), GetCountTexture1DArray());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Texture2D"), GetCountTexture2D());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Texture2D Array"), GetCountTexture2DArray());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Texture3D"), GetCountTexture3D());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("TextureCubeMap"), GetCountTextureCubeMap());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("TextureCubeMap Array"), GetCountTextureCubeMapArray());

	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Vertex State"), GetCountVertexState());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Blend State"), GetCountBlendState());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Sampler State"), GetCountSamplerState());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("DepthStencil State"), GetCountDepthStencilState());
	BearCore::BearLog::Printf(TEXT("Количество %s[%hu]"), TEXT("Rasterize State"), GetCountRasterizerState());
	BearCore::BearLog::Printf(TEXT("----------------------------------------------------------------------------"));
}

void BearGraphics::BearStats::TestForDestroy()
{
	BEAR_FATALERROR(!GetCountIndexBuffer() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Index Buffer"), GetCountIndexBuffer());
	BEAR_FATALERROR(!GetCountVertexBuffer(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Buffer"), GetCountVertexBuffer());


	BEAR_FATALERROR(!GetCountPixelShader() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Pixel Shader"), GetCountPixelShader());
	BEAR_FATALERROR(!GetCountPixelShaderCompiler() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Pixel Shader Compiler"), GetCountVertexShaderCompiler());


	BEAR_FATALERROR(!GetCountVertexShader(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Shader"), GetCountVertexShader());
	BEAR_FATALERROR(!GetCountVertexShaderCompiler(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex Shader Compiler"), GetCountVertexShaderCompiler());


	BEAR_FATALERROR(!GetCountRenderTargetView() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("RenderTarGet View"), GetCountRenderTargetView());
	BEAR_FATALERROR(!GetCountViewPort() , TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("View Port"), GetCountViewPort());
	BEAR_FATALERROR(!GetCountDepthStencilView(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("DepthStencil View"), GetCountDepthStencilView());


	BEAR_FATALERROR(!GetCountShaderConstants(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Shader Constants"), GetCountShaderConstants());


	BEAR_FATALERROR(!GetCountTexture1D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture1D"), GetCountTexture1D());
	BEAR_FATALERROR(!GetCountTexture1DArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture1D Array"), GetCountTexture1DArray());
	BEAR_FATALERROR(!GetCountTexture2D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture2D"), GetCountTexture2D());
	BEAR_FATALERROR(!GetCountTexture2DArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture2D Array"), GetCountTexture2DArray());
	BEAR_FATALERROR(!GetCountTexture3D(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Texture3D"), GetCountTexture3D());
	BEAR_FATALERROR(!GetCountTextureCubeMap(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("TextureCubeMap"), GetCountTextureCubeMap());
	BEAR_FATALERROR(!GetCountTextureCubeMapArray(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("TextureCubeMap Array"), GetCountTextureCubeMapArray());


	BEAR_FATALERROR(!GetCountVertexState(), TEXT("Не все %s были очищены количетсво[%hu]"), TEXT("Vertex State"), GetCountVertexState());
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
#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 
#define  CREATE_RENDERRESOURCE_ARGUMENTS1 ,void*data,bsize size
#define  CREATE_RENDERRESOURCE_ARGUMENTS2 ,data,size
CREATE_RENDERRESOURCE_CLASS2(VertexState);