#pragma once
namespace BearGraphics
{
	enum BearWindowEventType
	{
		WET_None,
		WET_KeyDouble,
		WET_KeyDown,
		WET_KeyUp,
		WET_Char,
		WET_Resize,
		WET_Deactive,
		WET_Active,
		WET_MouseMove,
		WET_MouseEnter,
		WET_MouseLevae,

	};
	enum BearShaderType
	{
		ST_Vertex,
		ST_Pixel
	};
	enum BearTexturePixelFormat
	{
		TPF_R8 = 0,
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
	enum BearGraphicsObjectType
	{
		GOT_None,
		GOT_Object,
		GOT_Texture2D,
		GOT_RenderTargetView,
		GOT_Viewport,
		GOT_Shader,
		GOT_Pipeline,
		GOT_Context,
		GOT_IndexBuffer,
		GOT_VertexBuffer,
	};
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
	enum BearRenderTargetFormat
	{
		RTF_NONE=0,
		RTF_R8 ,
		RTF_R8G8,
		RTF_R8G8B8A8,
		RTF_R32F,
		RTF_R32G32F,
		RTF_R32G32B32F,
		RTF_R32G32B32A32F,
	};
}