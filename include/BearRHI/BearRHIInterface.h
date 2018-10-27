#pragma once 
namespace BearRHI
{


	class BearRHIInterface
	{
	public:
		virtual void clear() = 0;
		virtual void attachRenderTargetView(uint32 id, BearRHIViewPort*render_target) = 0;
		virtual void attachRenderTargetView(uint32 id, BearRHIRenderTargetView*render_target) = 0;
		virtual void attachDepthStencilView(BearRHIDepthStencilView*depthStencill) = 0;
		virtual void detachRenderTargetView(uint32 id) = 0;
		virtual void detachDepthStencilView() = 0;

		virtual void setViewport(uint32 id, float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f) = 0;

		virtual void setPixelShader(BearRHIPixelShader*shader) = 0;
		virtual void setVertexShader(BearRHIVertexShader*shader) = 0;

		virtual void setIndexBuffer(BearRHIIndexBuffer*buffer) = 0;
		virtual void setVertexBuffer(BearRHIVertexBuffer*buffer, uint32 stride) = 0;

		virtual void setVertexInputLayout(BearRHIVertexInputLayout*buffer) = 0;

		virtual void setBlendState(BearRHIBlendState*State,const  BearCore::BearColor&color) = 0;
		virtual void setDepthStencilState(BearRHIDepthStencilState*State, uint32 StenciRef) = 0;
		virtual void setRasterizerState(BearRHIRasterizerState*State) = 0;

		virtual void setItemInPixelShader(const char*name, float R) = 0;
		virtual void setItemInPixelShader(const char*name, const BearCore::BearVector2<float>& RG) = 0;
		virtual void setItemInPixelShader(const char*name, const BearCore::BearVector3<float>& RGB) = 0;
		virtual void setItemInPixelShader(const char*name, const BearCore::BearVector4<float>& RGGBA) = 0;
		virtual void setItemInPixelShader(const char*name, BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler) = 0;

		virtual void setItemInVertexShader(const char*name, float R) = 0;
		virtual void setItemInVertexShader(const char*name, const BearCore::BearVector2<float>& RG) = 0;
		virtual void setItemInVertexShader(const char*name, const BearCore::BearVector3<float>& RGB) = 0;
		virtual void setItemInVertexShader(const char*name, const BearCore::BearVector4<float>& RGGBA) = 0;
		virtual void setItemInVertexShader(const char*name, const BearCore::BearMatrix&matrix) = 0;
		virtual void setItemInVertexShader(const char*name, BearRHITexture2D*texture2d, BearRHI::BearRHISamplerState*sampler) = 0;
		virtual void draw(bsize size, bsize possition, BearGraphics::BearDrawType mode) = 0;
	};
}