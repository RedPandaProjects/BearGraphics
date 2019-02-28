#pragma once 

namespace BearGraphics
{
	struct BearBlendStateInitializer
	{
		BearBlendStateInitializer() { RenderTarget[0].Enable = true; }
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
	
	};
	struct BearDepthStencilStateInitializer
	{
		BearDepthStencilStateInitializer(
			bool depthEnable=true,
			BearCompareFunction depthTest= CF_LESSEQUAL,
			bool stencillEnable=false,
			uint8 stencilReadMask=0xFF,
			uint8 stencilWriteMask=0xFF) 
			:DepthEnable(depthEnable), 
			DepthTest(depthTest), 
			StencillEnable(stencillEnable), 
			StencilReadMask(stencilReadMask), 
			StencilWriteMask(stencilWriteMask)
		{

		}
		struct Stencill
		{
			Stencill(BearStencilOp stencilFailOp = SO_KEEP,
			BearStencilOp stencilDepthFailOp = SO_KEEP,
			BearStencilOp stencilPassOp=SO_KEEP,
			BearCompareFunction stencilTest=CF_ALWAYS):StencilFailOp(stencilFailOp), StencilDepthFailOp(stencilDepthFailOp), StencilPassOp(stencilPassOp), StencilTest(stencilTest){}

			BearStencilOp StencilFailOp;
			BearStencilOp StencilDepthFailOp;
			BearStencilOp StencilPassOp;
			BearCompareFunction StencilTest;
		};
		bool DepthEnable;
		BearCompareFunction DepthTest;
		bool StencillEnable;
		uint8 StencilReadMask;
		uint8 StencilWriteMask;
		Stencill FrontFace;
		Stencill BackFace;
	};
	struct BearSamplerStateInitializer
	{
		BearSamplerStateInitializer(
			BearSamplerAddressMode addressU = SAM_WRAP,
			BearSamplerAddressMode addressV = SAM_WRAP,
			BearSamplerAddressMode addressW = SAM_WRAP,
			bsize mipBias = 0,
			bsize maxAnisotropy = 1,
			BearSamplerFilter filter = SF_MAG_MIP_POINT,
			BearCore::BearColor borderColor = BearCore::BearColor::Transparent
		)
			:AddressU(addressU),
			AddressV(addressV),
			AddressW(addressW),
			MipBias(mipBias),
			MaxAnisotropy(maxAnisotropy),
			Filter(filter),
			BorderColor(borderColor)
		{}

		BearSamplerAddressMode AddressU;
		BearSamplerAddressMode AddressV;
		BearSamplerAddressMode AddressW;
		bsize MipBias;
		bsize MaxAnisotropy;
		BearSamplerFilter Filter;
		BearCore::BearColor BorderColor;
	};
	struct BearRasterizerStateInitializer
	{
		BearRasterizerStateInitializer(
			BearRasterizerCullMode cullMode=RCM_BACK,
			BearRasterizerFillMode fillMode=RFM_SOLID,
			float depthBias=0,
			float slopeScaleDepthBias=0):
			CullMode(cullMode),
			FillMode(fillMode), 
			DepthBias(depthBias),
			SlopeScaleDepthBias(slopeScaleDepthBias)
		{}
		BearRasterizerCullMode CullMode;
		BearRasterizerFillMode FillMode;
		float DepthBias;
		float SlopeScaleDepthBias;
	};
	struct BearVertexStateElement
	{
		BearVertexStateElement(const char*Name, BearVertexFormat Type, bsize Offset,bool IsInstance=false) :Name(Name), Type(Type), Offset(Offset), IsInstance(IsInstance), SemanticIndex(0){}
		BearVertexStateElement() :Type(VF_NONE), Offset(0) , IsInstance(0), SemanticIndex(0){}
		BearVertexFormat Type;
		BearCore::BearStringConteniarAnsi Name;
		bsize Offset;
		bsize SemanticIndex;
		bool IsInstance;
	};
	struct BearVertexStateInitializer
	{
		BearVertexStateElement Elements[16];
	};

}