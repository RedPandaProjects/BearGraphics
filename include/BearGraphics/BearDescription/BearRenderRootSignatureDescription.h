#pragma once
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderRootSignatureDescription
	{
	public:
		BearRenderRootSignatureDescription() {}
		BearRenderRootSignatureDescription(const BearRenderRootSignatureDescription&Right) { Copy(Right); }
		BearRenderRootSignatureDescription(BearRenderRootSignatureDescription&&Right) { Swap(Right); }
		inline ~BearRenderRootSignatureDescription() {}
		void Copy(const BearRenderRootSignatureDescription&Right);
		void Swap(BearRenderRootSignatureDescription&Right);
		inline BearRenderRootSignatureDescription&operator=(const BearRenderRootSignatureDescription&Right) { Copy(Right); return*this; }
		inline BearRenderRootSignatureDescription&operator=(BearRenderRootSignatureDescription&&Right) { Swap(Right); return*this; }
		struct UniformBuffer
		{
			UniformBuffer() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		UniformBuffers[16];
		struct TextureBuffer
		{
			TextureBuffer() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		TextureBuffers[16];
		struct SamplerState
		{
			SamplerState() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		SamplerStates[16];

	};
}