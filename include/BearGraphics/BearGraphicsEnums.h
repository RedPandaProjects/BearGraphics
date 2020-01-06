#pragma once
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)    GOT_##Name,
enum BearGraphicsObjectType
{
	GOT_None=0,
#include "BearTemplate/BearGraphicsObjectsList.h"
};
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
enum  BearShaderType
{
	ST_Null,
	ST_Vertex,
	ST_Pixel,
};
enum BearVertexFormat
{
	VF_NONE = 0,
	VF_R16G16_FLOAT,
	VF_R16G16B16_FLOAT,
	VF_R16G16B16A16_FLOAT,
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
	RTF_NONE = 0,
	RTF_R8,
	RTF_R8G8,
	RTF_R8G8B8A8,
	RTF_R32F,
	RTF_R32G32F,
	RTF_R32G32B32F,
	RTF_R32G32B32A32F,
};
enum BearTopologyType
{
	TT_POINT_LIST = 0,
	TT_LINE_LIST,
	TT_TRIANGLE_LIST,
};