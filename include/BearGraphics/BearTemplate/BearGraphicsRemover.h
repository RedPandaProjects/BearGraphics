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
#define REGISTER_OBJECT(EType,Class,Parent) case EType: BearCore::bear_delete(reinterpret_cast<BearRenderBase::Class*>(object));  break;
#include "BearGraphics_Objects.h"
				default:
					BearCore::bear_delete(object);
					break;
				};
			}
		};
	}
}