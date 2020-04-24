#pragma once 

class BEARGRAPHICS_API BearPipelineMeshDescription
{
public:


	BearPipelineMeshDescription();
	BearPipelineMeshDescription(const BearPipelineMeshDescription&Right);
	BearPipelineMeshDescription(BearPipelineMeshDescription&&Right);
	inline ~BearPipelineMeshDescription() {}
		
	void Copy(const BearPipelineMeshDescription&Right);
	void Swap(BearPipelineMeshDescription&Right);
	inline BearPipelineMeshDescription&operator=(const BearPipelineMeshDescription&Right) {			Copy(Right); return*this;		}
	inline BearPipelineMeshDescription&operator=(BearPipelineMeshDescription&&Right) { Swap(Right); return*this; }
	bool operator== (const BearPipelineMeshDescription& Right)const;
	inline bool operator!= (const BearPipelineMeshDescription& Right)const { return !((*this) == Right); }
	bool operator<(const BearPipelineMeshDescription& Right)const;

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
		BearFactoryPointer<BearRHI::BearRHIShader> Mesh;
		BearFactoryPointer<BearRHI::BearRHIShader> Amplification;
		BearFactoryPointer<BearRHI::BearRHIShader> Pixel;
	}Shaders;
	
	BearFactoryPointer<BearRHI::BearRHIRenderPass>  RenderPass;
	BearFactoryPointer<BearRHI::BearRHIRootSignature> RootSignature;
};
