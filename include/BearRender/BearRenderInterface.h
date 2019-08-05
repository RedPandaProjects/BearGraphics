#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearRenderInterface
	{
	public:
		static bool Initialize(const bchar*name);

		static void AttachRenderTargetView(uint32 id, BearRenderTargetViewRef&viewport);
		static void AttachRenderTargetView(BearViewport&viewport);
		static void DetachRenderTargetView(uint32 id);
		static void AttachDepthStencilView(BearDepthStencilViewRef&viewport);
		static void DetachDepthStencilView();


		static void SetVertexState(const BearVertexStateRef&shader);
		static void SetVertexShader(const BearVertexShaderRef&shader);
		static void SetPixelShader(const BearPixelShaderRef&shader);

		static void SetIndexBuffer(const BearIndexBufferRef&shader);
		static void SetVertexBuffer(const BearVertexBufferRef&shader);

		static void DrawIndexed(bsize size, bsize possition = 0, BearGraphics::BearDrawType mode = BearGraphics::DT_TRIANGLE);
		static void Draw(bsize size, bsize possition = 0, BearGraphics::BearDrawType mode = BearGraphics::DT_TRIANGLE);

		static void SetViewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.f);
		static void SetScissor(float x, float y, float x1, float y1);
		static void DisableScissor();
		static void SetBlendState(const BearBlendStateRef&State,const BearCore::BearColor&color);
		static void SetDepthStencilState(const BearDepthStencilStateRef&State,uint32 StencilRef);
		static void SetRasterizerState(const BearRasterizerStateRef&State);

		static void SetPixelShaderConstants(bsize slot,const BearShaderConstantsRef&consts);
		static void SetPixelShaderResource(bsize slot, const BearTexture2DRef&texture2d, const BearSamplerStateRef&sampler);
		static void SetVertexShaderConstants(bsize slot, const BearShaderConstantsRef&consts);
		static void SetVertexShaderResource(bsize slot, const BearTexture2DRef&texture2d, const BearSamplerStateRef&sampler);
		static void SetPixelShaderResource(bsize slot, const BearRenderTargetViewRef&texture2d, const BearSamplerStateRef&sampler);
		static void SetVertexShaderResource(bsize slot, const BearRenderTargetViewRef&texture2d, const BearSamplerStateRef&sampler);

		static void Destroy();
	};
}
