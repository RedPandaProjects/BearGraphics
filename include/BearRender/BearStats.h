#pragma once 

namespace BearGraphics
{

	class BEARGRAPHICS_API BearStats
	{
	public:
		friend BearRenderInterface;
		 static uint16 GetCountIndexBuffer() ;
		 static uint16 GetCountVertexBuffer() ;

		 static uint16 GetCountPixelShader() ;
		 static uint16 GetCountPixelShaderCompiler() ;

		 static uint16 GetCountVertexShader() ;
		 static uint16 GetCountVertexShaderCompiler() ;

		 static uint16 GetCountRenderTargetView() ;
		 static uint16 GetCountViewPort() ;
		 static uint16 GetCountDepthStencilView() ;

		 static uint16 GetCountShaderConstants();

		 static uint16 GetCountTexture1D() ;
		 static uint16 GetCountTexture1DArray() ;
		 static uint16 GetCountTexture2D() ;
		 static uint16 GetCountTexture2DArray() ;
		 static uint16 GetCountTexture3D() ;
		 static uint16 GetCountTextureCubeMap() ;
		 static uint16 GetCountTextureCubeMapArray() ;

		 static uint16 GetCountVertexState();
		 static uint16 GetCountBlendState() ;
		 static uint16 GetCountSamplerState() ;
		 static uint16 GetCountDepthStencilState() ;
		 static uint16 GetCountRasterizerState() ;
		 static void DumpToLog();
	private:
		static void TestForDestroy();
	};
#define  CREATE_RENDERRESOURCE_ARGUMENTS1 
#define  CREATE_RENDERRESOURCE_ARGUMENTS2

	CREATE_RENDERRESOURCE_CLASS1(BlendState);
	CREATE_RENDERRESOURCE_CLASS1(DepthStencilState);
	CREATE_RENDERRESOURCE_CLASS1(SamplerState);
	CREATE_RENDERRESOURCE_CLASS1(RasterizerState);

#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 

#define  CREATE_RENDERRESOURCE_ARGUMENTS1 ,void*shader,bsize size
#define  CREATE_RENDERRESOURCE_ARGUMENTS2 ,data,size
	CREATE_RENDERRESOURCE_CLASS1(VertexState);
#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 
}