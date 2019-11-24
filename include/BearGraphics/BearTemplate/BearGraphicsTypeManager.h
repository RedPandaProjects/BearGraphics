#pragma once
namespace BearGraphics
{
	namespace Impl
	{
		class BearTypeManager
		{
			BEAR_CLASS_STATIC(BearTypeManager);
		public:
			template<typename C>
			static	BearGraphicsObjectType GetType()
			{
				return GOT_None;
			}

#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...) template<> static	BearGraphicsObjectType GetType<BearRHI::BearRHI##Name>(){return GOT_##Name;}
#include "BearTemplate/BearGraphicsObjectsList.h"


		private:

		};
	}
}