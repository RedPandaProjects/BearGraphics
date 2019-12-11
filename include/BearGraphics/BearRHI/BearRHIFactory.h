#pragma once
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...) virtual BearRHI ## Name*Create ## Name(__VA_ARGS__)=0;
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)

#define RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY(Name,...)
#define RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(Name,Parent,...) 


namespace BearRHI
{
	class BEARGRAPHICS_API  BearRHIFactory
	{
	public:
#include "..\BearTemplate\BearGraphicsObjectsList.h"
		virtual ~BearRHIFactory() = 0;
	};
}


