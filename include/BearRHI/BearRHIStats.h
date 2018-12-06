#pragma once 
namespace BearRHI
{
	class BearRHIStats
	{
	public:
		virtual uint16 GetCountIndexBuffer()=0;
		virtual uint16 GetCountVertexBuffer()=0;		
			
		virtual uint16 GetCountPixelShader()=0;
		virtual uint16 GetCountPixelShaderCompiler()=0;	
		
		virtual uint16 GetCountVertexShader()=0;
		virtual uint16 GetCountVertexShaderCompiler()=0;	
		
		virtual uint16 GetCountRenderTargetView()=0;
		virtual uint16 GetCountViewPort()=0;
		virtual uint16 GetCountDepthStencilView()=0;
		
		virtual uint16 GetCountShaderConstants() = 0;
		
		virtual uint16 GetCountTexture1D()=0;
		virtual uint16 GetCountTexture1DArray()=0;
		virtual uint16 GetCountTexture2D()=0;
		virtual uint16 GetCountTexture2DArray()=0;
		virtual uint16 GetCountTexture3D()=0;
		virtual uint16 GetCountTextureCubeMap()=0;
		virtual uint16 GetCountTextureCubeMapArray()=0;
		
		virtual uint16 GetCountVertexState() = 0;
		virtual uint16 GetCountBlendState()=0;
		virtual uint16 GetCountSamplerState()=0;
		virtual uint16 GetCountDepthStencilState()=0;
		virtual uint16 GetCountRasterizerState()=0;
		
	};
	class BearRHIBlendState
	{
	};
	class BearRHISamplerState
	{
	};
	class BearRHIDepthStencilState
	{
	};
	class BearRHIRasterizerState
	{
	};
	class BearRHIVertexState
	{
	};
}