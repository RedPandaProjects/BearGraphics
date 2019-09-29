#pragma once 
namespace BearGraphics
{

	struct BearVertexStateElement
	{
		BearVertexStateElement(const char*Name, BearVertexFormat Type, bsize Offset, bool IsInstance = false) :Name(Name), Type(Type), Offset(Offset), IsInstance(IsInstance), SemanticIndex(0) {}
		BearVertexStateElement() :Type(VF_NONE), Offset(0), IsInstance(0), SemanticIndex(0) {}
		BearVertexFormat Type;
		BearCore::BearStringConteniarAnsi Name;
		bsize Offset;
		bsize SemanticIndex;
		bool IsInstance;
	};
	class BEARGRAPHICS_API BearRenderPipelineDescription
	{
	public:
		BearRenderPipelineDescription();
		BearRenderPipelineDescription(const BearRenderPipelineDescription&Right);
		BearRenderPipelineDescription(BearRenderPipelineDescription&&Right);
		inline ~BearRenderPipelineDescription() {}
		


		void Copy(const BearRenderPipelineDescription&Right);
		void Swap(BearRenderPipelineDescription&Right);
		inline BearRenderPipelineDescription&operator=(const BearRenderPipelineDescription&Right) {			Copy(Right); return*this;		}
		inline BearRenderPipelineDescription&operator=(BearRenderPipelineDescription&&Right) { Swap(Right); return*this; }
		struct
		{
			BearVertexStateElement Elements[16];

		} VertexState;

		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Pixel;
			BearFactoryPointer<BearRenderBase::BearRenderShaderBase> Vertex;
		}Shaders;
	
		struct
		{
			BearRenderTargetFormat Formats[8];
			
		} RenderTargets;
		
		
	};
}
