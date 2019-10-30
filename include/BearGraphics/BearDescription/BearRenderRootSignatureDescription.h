#pragma once
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderRootSignatureDescription
	{
	public:
		BearRenderRootSignatureDescription();
		BearRenderRootSignatureDescription(const BearRenderRootSignatureDescription&Right);
		BearRenderRootSignatureDescription(BearRenderRootSignatureDescription&&Right);
		inline ~BearRenderRootSignatureDescription() {}
		void Copy(const BearRenderRootSignatureDescription&Right);
		void Swap(BearRenderRootSignatureDescription&Right);
		inline BearRenderRootSignatureDescription&operator=(const BearRenderRootSignatureDescription&Right) { Copy(Right); return*this; }
		inline BearRenderRootSignatureDescription&operator=(BearRenderRootSignatureDescription&&Right) { Swap(Right); return*this; }
		struct UniformBuffer
		{
			UniformBuffer() :Shader(ST_Vertex) {}
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
			BearShaderType Shader;
		}
		UniformBuffers[16];

	};
}