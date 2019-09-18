#pragma once 
namespace BearGraphics
{
	enum BearVertexFormat
	{
		VF_NONE = 0,
		VF_R32_FLOAT,
		VF_R32G32_FLOAT,
		VF_R32G32B32_FLOAT,
		VF_R32G32B32A32_FLOAT,
		VF_R32_INT,
		VF_R8,
		VF_R8G8,
		VF_R8G8B8A8,
	};
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
		~BearRenderPipelineDescription();

		BearVertexStateElement VertexStateElements[16];
		BearFactoryPointer<BearRenderBase::BearRenderShaderBase> PixelShader;
		BearFactoryPointer<BearRenderBase::BearRenderShaderBase> VertexShader;

		
	};
}
