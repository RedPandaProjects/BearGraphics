#pragma once 

struct BearInputLayoutElement
{
	BearInputLayoutElement(const char*Name, BearVertexFormat Type, bsize Offset, bool IsInstance = false) :Name(Name), Type(Type), Offset(Offset), IsInstance(IsInstance), SemanticIndex(0) {}
	BearInputLayoutElement() :Type(VF_NONE), Offset(0), IsInstance(0), SemanticIndex(0) {}
	BearVertexFormat Type;
	BearStringConteniarAnsi Name;
	bsize Offset;
	bsize SemanticIndex;
	bool IsInstance;
	inline bool empty()const 
	{
		return Type == VF_NONE;
	}

		

};
class BEARGRAPHICS_API BearPipelineDescription
{
public:
	BearPipelineDescription();
	BearPipelineDescription(const BearPipelineDescription&Right);
	BearPipelineDescription(BearPipelineDescription&&Right);
	inline ~BearPipelineDescription() {}
		
	void Copy(const BearPipelineDescription&Right);
	void Swap(BearPipelineDescription&Right);
	inline BearPipelineDescription&operator=(const BearPipelineDescription&Right) {			Copy(Right); return*this;		}
	inline BearPipelineDescription&operator=(BearPipelineDescription&&Right) { Swap(Right); return*this; }
	struct
	{
		BearInputLayoutElement Elements[16];

	} InputLayout;

	struct
	{
		BearFactoryPointer<BearRHI::BearRHIShader> Pixel;
		BearFactoryPointer<BearRHI::BearRHIShader> Vertex;
	}Shaders;
	
	struct
	{
		BearRenderTargetFormat Formats[8];
			
	} RenderTargets;
	BearTopologyType TopologyType;
		
};
