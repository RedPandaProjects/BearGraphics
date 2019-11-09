#pragma once
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderRootSignatureDescription
	{
	public:
		BearRenderRootSignatureDescription():Local(false){}
		BearRenderRootSignatureDescription(const BearRenderRootSignatureDescription&Right) { Copy(Right); }
		BearRenderRootSignatureDescription(BearRenderRootSignatureDescription&&Right) { Swap(Right); }
		inline ~BearRenderRootSignatureDescription() {}
		void Copy(const BearRenderRootSignatureDescription&Right);
		void Swap(BearRenderRootSignatureDescription&Right);
		inline BearRenderRootSignatureDescription&operator=(const BearRenderRootSignatureDescription&Right) { Copy(Right); return*this; }
		inline BearRenderRootSignatureDescription&operator=(BearRenderRootSignatureDescription&&Right) { Swap(Right); return*this; }
		struct UAVResource
		{
			UAVResource() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		UAVResources[16];
		struct UniformBuffer
		{
			UniformBuffer() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		UniformBuffers[16];
		struct SRVResource
		{
			SRVResource() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		SRVResources[16];
		struct Sampler
		{
			Sampler() :Shader(ST_Null) {}
			BearShaderType Shader;
		}
		Samplers[16];
		bool Local;
	};
}