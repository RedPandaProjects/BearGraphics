#pragma once 
namespace BearRenderBase
{

#define RHI_FACTORY_DECLARE(Class,...) \
	virtual BearRender##Class##Base* Create##Class(__VA_ARGS__)=0; 
	class  BearRenderFactoryBase
	{
		BEAR_CLASS_NO_COPY(BearRenderFactoryBase)
	public:
		BearRenderFactoryBase() {}
		RHI_FACTORY_DECLARE(Interface);
		RHI_FACTORY_DECLARE(Context);
		RHI_FACTORY_DECLARE(Pipeline, const BearGraphics::BearRenderPipelineDescription&Descruotion);
		RHI_FACTORY_DECLARE(Viewport, void*Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync,const BearGraphics::BearRenderViewportDescription&Descruotion);

		RHI_FACTORY_DECLARE(Shader, BearGraphics::BearShaderType Type);

		RHI_FACTORY_DECLARE(IndexBuffer);
		RHI_FACTORY_DECLARE(VertexBuffer);
		RHI_FACTORY_DECLARE(UniformBuffer);
		RHI_FACTORY_DECLARE(RootSignature, const BearGraphics::BearRenderRootSignatureDescription&Descruotion);
	/*	RHI_FACTORY_DECLARE(DefaultManager);

		RHI_FACTORY_DECLARE(RenderTargetView, bsize w, bsize h, BearGraphics::BearRenderTargetFormat format);
		RHI_FACTORY_DECLARE(Viewport, void*win, bsize w, bsize h, bool fullscreen, bool vsync);
		RHI_FACTORY_DECLARE(DepthStencilView, bsize w, bsize h, BearGraphics::BearDepthStencilFormat format);

		RHI_FACTORY_DECLARE(Texture2D, bsize w, bsize h, bsize mip, BearGraphics::BearTexturePixelFormat format, bool dynamic, void*data);
		RHI_FACTORY_DECLARE(Texture2DArray, bsize w, bsize h, bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format, void*data);

		RHI_FACTORY_DECLARE(VertexBuffer, void*data, bsize size,bool dynamic);
		RHI_FACTORY_DECLARE(IndexBuffer, void*data, bsize size, bool dynamic);
	
		RHI_FACTORY_DECLARE(ShaderConstants, const BearGraphics::BearShaderConstantsInitializer&shader, bool dynamic);

		RHI_FACTORY_DECLARE(VertexShader,void*data,bsize size);
		RHI_FACTORY_DECLARE(PixelShader, void*data, bsize size);
		RHI_FACTORY_DECLARE(VertexShaderCompiler);
		RHI_FACTORY_DECLARE(PixelShaderCompiler);

		RHI_FACTORY_DECLARE(VertexState, const BearGraphics::BearVertexStateInitializer&initializer,void*data,bsize size);
		RHI_FACTORY_DECLARE(BlendState, const BearGraphics::BearBlendStateInitializer&initializer);
		RHI_FACTORY_DECLARE(DepthStencilState, const BearGraphics::BearDepthStencilStateInitializer&initializer);
		RHI_FACTORY_DECLARE(RasterizerState, const BearGraphics::BearRasterizerStateInitializer&initializer);
		RHI_FACTORY_DECLARE(SamplerState, const BearGraphics::BearSamplerStateInitializer&initializer);*/

	};
#undef RHI_FACTORY_DECLARE
}