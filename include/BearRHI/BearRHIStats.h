#pragma once 
namespace BearRHI
{
	class BearRHIStats
	{
	public:
		virtual uint16 getCountIndexBuffer()=0;
		virtual uint16 getCountVertexBuffer()=0;		
			
		virtual uint16 getCountPixelShader()=0;
		virtual uint16 getCountPixelShaderCompiler()=0;	
		
		virtual uint16 getCountVertexShader()=0;
		virtual uint16 getCountVertexShaderCompiler()=0;	
		
		virtual uint16 getCountRenderTargetView()=0;
		virtual uint16 getCountViewPort()=0;
		virtual uint16 getCountDepthStencilView()=0;
		
		virtual uint16 getCountVertexInputLayout()=0;
		
		virtual uint16 getCountTexture1D()=0;
		virtual uint16 getCountTexture1DArray()=0;
		virtual uint16 getCountTexture2D()=0;
		virtual uint16 getCountTexture2DArray()=0;
		virtual uint16 getCountTexture3D()=0;
		virtual uint16 getCountTextureCubeMap()=0;
		virtual uint16 getCountTextureCubeMapArray()=0;
		
		virtual uint16 getCountBlendState()=0;
		virtual uint16 getCountSamplerState()=0;
		virtual uint16 getCountDepthStencilState()=0;
		virtual uint16 getCountRasterizerState()=0;
		
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
}