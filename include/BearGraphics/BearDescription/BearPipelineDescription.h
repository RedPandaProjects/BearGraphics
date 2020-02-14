#pragma once 

struct BearInputLayoutElement
{
	BearInputLayoutElement(const char*Name, BearVertexFormat Type, bsize Offset, bool IsInstance = false) :Type(Type),Name(Name), Offset(Offset), SemanticIndex(0), IsInstance(IsInstance) {}
	BearInputLayoutElement() :Type(VF_NONE), Offset(0), SemanticIndex(0) ,IsInstance(0){}
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

	struct BlendStateDescription
	{
		BlendStateDescription() {  AlphaToCoverageEnable = false; }
		struct RenderTarget
		{
			RenderTarget(
				bool enable = false,
				BearBlendOp color = BO_ADD,
				BearBlendFactor colorSrc = BF_ONE,
				BearBlendFactor colorDst = BF_ZERO,
				BearBlendOp alpha = BO_ADD,
				BearBlendFactor alphaSrc = BF_ONE,
				BearBlendFactor alphaDst = BF_ZERO,
				BearColorWriteMask colorWriteMask = CWM_RGBA
			) :Enable(enable), Color(color), ColorSrc(colorSrc), ColorDst(colorDst), Alpha(alpha), AlphaSrc(alphaSrc), AlphaDst(alphaDst), ColorWriteMask(colorWriteMask) {}

			bool Enable;
			BearBlendOp Color;
			BearBlendFactor ColorSrc;
			BearBlendFactor ColorDst;
			BearBlendOp Alpha;
			BearBlendFactor AlphaSrc;
			BearBlendFactor AlphaDst;
			BearColorWriteMask ColorWriteMask;
		};
		bool AlphaToCoverageEnable;
		RenderTarget RenderTarget[8];

	} BlendState;
	struct DepthStencilStateDescription
	{
		DepthStencilStateDescription(
			bool depthEnable = false,
			bool enableDepthWrite = true,
			BearCompareFunction depthTest = CF_LESSEQUAL,
			bool stencillEnable = false,
			bool backStencillEnable = false,
			uint8 stencilReadMask = 0xFF,
			uint8 stencilWriteMask = 0xFF)

			:EnableDepthWrite(enableDepthWrite),
			DepthEnable(depthEnable),
			DepthTest(depthTest),
			StencillEnable(stencillEnable),
			BackStencillEnable(stencillEnable),
			StencilReadMask(stencilReadMask),
			StencilWriteMask(stencilWriteMask)
		{

		}
		struct Stencill
		{
			Stencill(BearStencilOp stencilFailOp = SO_KEEP,
				BearStencilOp stencilDepthFailOp = SO_KEEP,
				BearStencilOp stencilPassOp = SO_KEEP,
				BearCompareFunction stencilTest = CF_ALWAYS) :StencilFailOp(stencilFailOp), StencilDepthFailOp(stencilDepthFailOp), StencilPassOp(stencilPassOp), StencilTest(stencilTest) {}

			BearStencilOp StencilFailOp;
			BearStencilOp StencilDepthFailOp;
			BearStencilOp StencilPassOp;
			BearCompareFunction StencilTest;
		};
		bool EnableDepthWrite;
		bool DepthEnable;
		BearCompareFunction DepthTest;
		bool StencillEnable;
		bool BackStencillEnable;
		uint8 StencilReadMask;
		uint8 StencilWriteMask;
		Stencill FrontFace;
		Stencill BackFace;
	} DepthStencilState;
	
	struct RasterizerStateDescription
	{
		RasterizerStateDescription(
			BearRasterizerCullMode cullMode = RCM_BACK,
			BearRasterizerFillMode fillMode = RFM_SOLID,
			BearRasterizerFrontFace frontFace = RFF_FACE_CLOCKWISE,
			float depthBias = 0,
			float slopeScaleDepthBias = 0) :
			CullMode(cullMode),
			FillMode(fillMode),
			FrontFace(frontFace),
			DepthBias(depthBias),
			SlopeScaleDepthBias(slopeScaleDepthBias)
		{}
		BearRasterizerCullMode CullMode;
		BearRasterizerFillMode FillMode;
		BearRasterizerFrontFace FrontFace;
		float DepthBias;
		float SlopeScaleDepthBias;
	} RasterizerState;

	struct
	{
		BearFactoryPointer<BearRHI::BearRHIShader> Pixel;
		BearFactoryPointer<BearRHI::BearRHIShader> Vertex;
	}Shaders;
	
	BearFactoryPointer<BearRHI::BearRHIRenderPass>  RenderPass;
	BearTopologyType TopologyType;
	BearFactoryPointer<BearRHI::BearRHIRootSignature> RootSignature;
};
