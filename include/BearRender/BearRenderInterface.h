#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearRenderInterface
	{
	public:
		static bool Initialize(const bchar*name);

		static void AttachRenderTargetView(uint32 id, BearRenderTargetViewRef&viewport);
		static void AttachRenderTargetView(uint32 id, BearViewPortRef&viewport);
		static void DetachRenderTargetView(uint32 id);
		static void AttachDepthStencilView(BearDepthStencilViewRef&viewport);
		static void DetachDepthStencilView();


		static void SetVertexInputLayout(const BearVertexInputLayoutRef&shader);
		static void SetVertexShader(const BearVertexShaderRef&shader);
		static void SetPixelShader(const BearPixelShaderRef&shader);

		static void SetIndexBuffer(const BearIndexBufferRef&shader);
		static void SetVertexBuffer(const BearVertexBufferRef&shader, uint32 stride);

		static void Draw(bsize size, bsize possition = 0, BearGraphics::BearDrawType mode = BearGraphics::DT_TRIANGLE);

		static void SetViewport(uint32 id, float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.f);

		static void SetBlendState(const BearBlendStateRef&State,const BearCore::BearColor&color);
		static void SetDepthStencilState(const BearDepthStencilStateRef&State,uint32 StencilRef);
		static void SetRasterizerState(const BearRasterizerStateRef&State);

		static void SetItemInPixelShader(const char*name, float R);
		static void SetItemInPixelShader(const char*name, const BearCore::BearVector2<float>& RG);
		static void SetItemInPixelShader(const char*name, const BearCore::BearVector3<float>& RGB);
		static void SetItemInPixelShader(const char*name, const BearCore::BearVector4<float>& RGGBA);
		static void SetItemInPixelShader(const char*name, float R, float G);
		static void SetItemInPixelShader(const char*name, float R, float G, float B);
		static void SetItemInPixelShader(const char*name, float R, float G, float B, float A);
		static void SetItemInPixelShader(const char*name, const BearTexture2DRef&texture2d, const BearSamplerStateRef&sampler);
		
		static void SetItemInVertexShader(const char*name, float R);
		static void SetItemInVertexShader(const char*name, const BearCore::BearVector2<float>& RG);
		static void SetItemInVertexShader(const char*name, const BearCore::BearVector3<float>& RGB);
		static void SetItemInVertexShader(const char*name, const BearCore::BearVector4<float>& RGGBA);
		static void SetItemInVertexShader(const char*name, float R, float G);
		static void SetItemInVertexShader(const char*name, float R, float G, float B);
		static void SetItemInVertexShader(const char*name, float R, float G, float B, float A);
		static void SetItemInVertexShader(const char*name, const BearTexture2DRef&texture2d, const BearSamplerStateRef&sampler);
		static void SetItemInVertexShader(const char*name, const BearCore::BearMatrix&matrix);

		static void Destroy();

	};
}
