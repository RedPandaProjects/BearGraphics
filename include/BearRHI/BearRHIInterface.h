#pragma once 
namespace BearRHI
{


	class BearRHIInterface
	{
	public:
		virtual void Clear() = 0;
		virtual void AttachViewport( BearRHIViewport*render_target) = 0;
		virtual void AttachRenderTargetView(uint32 id, BearRHIRenderTargetView*render_target) = 0;
		virtual void AttachDepthStencilView(BearRHIDepthStencilView*depthStencill) = 0;
		virtual void DetachRenderTargetView(uint32 id) = 0;
		virtual void DetachDepthStencilView() = 0;
		virtual void DetachViewport() = 0;

		virtual void SetViewport( float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f) = 0;
		virtual void SetScissor(bool Enable, float x, float y, float x1, float y1)=0;

		virtual void SetPixelShader(BearRHIPixelShader*shader) = 0;
		virtual void SetVertexShader(BearRHIVertexShader*shader) = 0;

		virtual void SetIndexBuffer(BearRHIIndexBuffer*buffer) = 0;
		virtual void SetVertexBuffer(BearRHIVertexBuffer*buffer) = 0;

		virtual void SetVertexState(BearRHIVertexState*buffer) = 0;
		virtual void SetBlendState(BearRHIBlendState*State,const  BearCore::BearColor&color) = 0;
		virtual void SetDepthStencilState(BearRHIDepthStencilState*State, uint32 StenciRef) = 0;
		virtual void SetRasterizerState(BearRHIRasterizerState*State) = 0;


		virtual void SetVertexShaderConstants(bsize slot,BearRHIShaderConstants*constants) = 0;
		virtual void SetVertexShaderResource(bsize slot, BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler) = 0;

		virtual void SetPixelShaderConstants(bsize slot, BearRHIShaderConstants*constants) = 0;
		virtual void SetPixelShaderResource(bsize slot, BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler) = 0;

		virtual void Draw(bsize size, bsize possition, BearGraphics::BearDrawType mode) = 0;
	};
}