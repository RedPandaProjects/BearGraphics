#pragma once
namespace BearGraphics
{
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)    GOT_##Name,
	enum BearGraphicsObjectType
	{
		GOT_None=0,
#include "BearTemplate/BearGraphicsObjectsList.h"
	};
	
}