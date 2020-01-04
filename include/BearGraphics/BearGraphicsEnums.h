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
	ST_Vertex,
	ST_Pixel,
};