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
		struct UniformTexture
		{
			UniformTexture() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		Textures[16];
		struct UniformSampler
		{
			UniformSampler() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		Samplers[16];

	};
}