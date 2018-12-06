#pragma once 
namespace BearGraphics
{
	enum BearTexturePixelFormat
	{
		TPF_R8=0,
		TPF_R8G8,
		TPF_R8G8B8,
		TPF_R8G8B8A8,
		TPF_R32F,
		TPF_R32G32F,
		TPF_R32G32B32F,
		TPF_R32G32B32A32F,
		TPF_DXT_1,//not alpha
		TPF_DXT_1_alpha,//alpha  1 bit
		TPF_DXT_3,//alpga 
		TPF_DXT_5,//alpha
		TPF_BC1 = TPF_DXT_1,
		TPF_BC1a = TPF_DXT_1_alpha,
		TPF_BC2 = TPF_DXT_3,
		TPF_BC3 = TPF_DXT_5,
		TPF_BC4,//R 32 bit 16 pxiel
		TPF_BC5,//RB 64 bit 16 pxiel
		TPF_BC6,//RGBA FP16 64 bit 16 pxiel
		TPF_BC7//RGBA 64 bit 16 pxiel
	};
	enum BearDepthStencilFormat
	{

		DSF_DEPTH16=0,
		DSF_DEPTH32F,
		DSF_DEPTH24_STENCIL8,
		DSF_DEPTH32F_STENCIL8,
	};
	enum BearRenderTargetFormat
	{
		RTF_R8=0,
		RTF_R8G8,
		RTF_R8G8B8A8,
		RTF_R32F,
		RTF_R32G32F,
		RTF_R32G32B32F,
		RTF_R32G32B32A32F,
	};
	enum BearVertexFormat
	{
		VF_NONE=0,
		VF_R32_FLOAT,
		VF_R32G32_FLOAT,
		VF_R32G32B32_FLOAT,
		VF_R32G32B32A32_FLOAT,
		VF_R32_INT,
		VF_R8,
		VF_R8G8,
		VF_R8G8B8A8,
	};
	enum BearConstantFormat
	{
		CF_R32_FLOAT = 0,
		CF_R32G32_FLOAT,
		CF_R32G32B32_FLOAT,
		CF_R32G32B32A32_FLOAT,
		CF_R32_INT,
		CF_MATRIX,
	};
	enum BearDrawType
	{
		DT_POINT=0,
		DT_LINE,
		DT_TRIANGLE,
	};
	enum	BearSamplerAddressMode
	{
		SAM_WRAP=0,
		SAM_MIRROR,
		SAM_CLAMP,
		SAM_BORDER,
	};
	enum BearSamplerFilter
	{
		SF_MAG_MIP_POINT,
		SF_MAG_LINEAR_MIP_POINT,
		SF_MAG_MIP_LINEAR,
		SF_ANISOTROPIC,
		SF_COMPARISON_MAG_MIP_POINT,
		SF_COMPARISON_MAG_LINEAR_MIP_POINT,
		SF_COMPARISON_MAG_MIP_LINEAR,
		SF_COMPARISON_ANISOTROPIC,
	};
	enum BearRasterizerCullMode
	{
		RCM_NONE,
		RCM_FRONT,
		RCM_BACK,
	};
	enum BearRasterizerFillMode
	{
		RFM_WIREFRAME,
		RFM_SOLID
	};
	enum BearBlendFactor
	{
		BF_ZERO,
		BF_ONE,
		BF_SRC_COLOR,
		BF_INV_SRC_COLOR,
		BF_SRC_ALPHA,
		BF_INV_SRC_ALPHA,
		BF_DEST_ALPHA,
		BF_INV_DEST_ALPHA,
		BF_DEST_COLOR,
		BF_INV_DEST_COLOR,
		BF_BLEND_FACTOR,
		BF_INV_BLEND_FACTOR,
	};
	enum BearBlendOp
	{
		BO_ADD,
		BO_SUBTRACT,
		BO_REV_SUBTRACT,
		BO_MIN,
		BO_MAX

	};
	enum BearColorWriteMask
	{
		CWM_R = 1 << 0,
		CWM_G = 1 << 1,
		CWM_B = 1 << 2,
		CWM_A = 1 << 3,
		CWM_RGB = CWM_R | CWM_G | CWM_B,
		CWM_RGBA = CWM_R | CWM_G | CWM_B| CWM_A,
	};
	enum BearCompareFunction
	{
		CF_NEVER,//=0
		CF_ALWAYS,//=1
		CF_EQUAL,//==
		CF_NOTEQUAL,//!=
		CF_LESS,//<
		CF_GREATER,//>
		CF_LESSEQUAL,//<=
		CF_GREATEREQUAL,//>=
	};
	enum BearStencilOp
	{
		SO_KEEP,
		SO_ZERO,
		SO_REPLACE,
		SO_INCR_SAT,
		SO_DECR_SAT,
		SO_INVERT,
		SO_INCR,
		SO_DECR
	};
}