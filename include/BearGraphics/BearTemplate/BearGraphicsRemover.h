#pragma once
namespace BearGraphics
{
	namespace Impl
	{

		class BearRemoverObject
		{
			BEAR_CLASS_STATIC(BearRemoverObject);
		public:
			template<typename T>
			static void Remove(void*object, BearGraphicsObjectType InType)
			{
				if (object == 0)return;
				switch (InType)
				{
				case GOT_None:
					BearCore::bear_delete(reinterpret_cast<T*>(object));
					break;

#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...) case GOT_##Name: BearCore::bear_delete(reinterpret_cast<BearRHI::BearRHI##Name*>(object));  break;
#include "BearTemplate/BearGraphicsObjectsList.h"
				default:
					BearCore::bear_delete(object);
					break;
				};
			}
		};
	}
}