#pragma once 

struct BearInputLayoutElement
{
	BearInputLayoutElement(const bchar8*Name, BearVertexFormat Type, bsize Offset, bool IsInstance = false) :Type(Type),Name(Name), Offset(Offset), SemanticIndex(0), IsInstance(IsInstance) {}
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
	inline bool operator ==(const BearInputLayoutElement& right) const
	{
		if (Type != right.Type)return false;
		if (Name != right.Name)return false;
		if (Offset != right.Offset)return false;
		if (SemanticIndex != right.SemanticIndex)return false;
		return IsInstance == right.IsInstance;
	}
	inline bool operator !=(const BearInputLayoutElement& right) const
	{
		if (Type != right.Type)return true;
		if (Name != right.Name)return true;
		if (Offset != right.Offset)return true;
		if (SemanticIndex != right.SemanticIndex)return true;
		return IsInstance != right.IsInstance;
	}
	inline bool operator<(const BearInputLayoutElement& right)const
	{
		if (Type != right.Type)return Type < right.Type;
		if (Name != right.Name)return Name < right.Name;
		if (Offset != right.Offset)return Offset < right.Offset;
		if (SemanticIndex != right.SemanticIndex)return SemanticIndex < right.SemanticIndex;
		return IsInstance != right.IsInstance;
	}

};
class BEARGRAPHICS_API BearPipelineGraphicsDescription
{
public:


	BearPipelineGraphicsDescription();
	BearPipelineGraphicsDescription(const BearPipelineGraphicsDescription&Right);
	BearPipelineGraphicsDescription(BearPipelineGraphicsDescription&&Right);
	inline ~BearPipelineGraphicsDescription() {}
		
	void Copy(const BearPipelineGraphicsDescription&Right);
	void Swap(BearPipelineGraphicsDescription&Right);
	inline BearPipelineGraphicsDescription&operator=(const BearPipelineGraphicsDescription&Right) {			Copy(Right); return*this;		}
	inline BearPipelineGraphicsDescription&operator=(BearPipelineGraphicsDescription&&Right) { Swap(Right); return*this; }
	bool operator== (const BearPipelineGraphicsDescription& Right)const;
	inline bool operator!= (const BearPipelineGraphicsDescription& Right)const { return !((*this) == Right); }
	bool operator<(const BearPipelineGraphicsDescription& Right)const;
	struct
	{
		BearInputLayoutElement Elements[16];

	} InputLayout;

	struct BlendStateDescription
	{
		BlendStateDescription() { IndependentBlendEnable = false; }
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
		RenderTarget RenderTarget[8];
		bool IndependentBlendEnable;
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
			:DepthEnable(depthEnable),
			EnableDepthWrite(enableDepthWrite),
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
			DepthBiasEnable(false),
			DepthBias(depthBias),
			DepthSlopeScaleBias(slopeScaleDepthBias),
			DepthClampEnable(false),
			DepthClmapBias(0)
		{}
		BearRasterizerCullMode CullMode;
		BearRasterizerFillMode FillMode;
		BearRasterizerFrontFace FrontFace;

		bool DepthBiasEnable;
		float DepthBias;
		float DepthSlopeScaleBias;

		bool DepthClampEnable;
		float DepthClmapBias;
	} RasterizerState;
	struct MultisampleStateDescription
	{
		MultisampleStateDescription() { AlphaToCoverageEnable = false; MultisampleEnable = false; }
		bool MultisampleEnable;
		bool AlphaToCoverageEnable;
	}MultisampleState;
	struct
	{
		BearFactoryPointer<BearRHI::BearRHIShader> Vertex;
		BearFactoryPointer<BearRHI::BearRHIShader> Hull;
		BearFactoryPointer<BearRHI::BearRHIShader> Domain;
		BearFactoryPointer<BearRHI::BearRHIShader> Geometry;
		BearFactoryPointer<BearRHI::BearRHIShader> Pixel;
	}Shaders;
	
	BearFactoryPointer<BearRHI::BearRHIRenderPass>  RenderPass;
	BearTopologyType TopologyType;
	BearFactoryPointer<BearRHI::BearRHIRootSignature> RootSignature;
};
