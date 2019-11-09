#pragma once 
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderRTXPipelineDescription
	{
	public:
		BearRenderRTXPipelineDescription() {}
		BearRenderRTXPipelineDescription(const BearRenderRTXPipelineDescription&Right) { Copy(Right); }
		BearRenderRTXPipelineDescription(BearRenderRTXPipelineDescription&&Right) { Swap(Right); }
		inline ~BearRenderRTXPipelineDescription() {}
		
		void Copy(const BearRenderRTXPipelineDescription&Right);
		void Swap(BearRenderRTXPipelineDescription&Right);
		inline BearRenderRTXPipelineDescription&operator=(const BearRenderRTXPipelineDescription&Right) {			Copy(Right); return*this;		}
		inline BearRenderRTXPipelineDescription&operator=(BearRenderRTXPipelineDescription&&Right) { Swap(Right); return*this; }

		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> RayGeneration;
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Hit;
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Miss;
		}Shaders;
	
		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> Global;
			BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> Local;
		}RootSignature;
	
	};
}
