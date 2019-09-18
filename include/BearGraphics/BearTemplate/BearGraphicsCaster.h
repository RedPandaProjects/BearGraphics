#pragma once
namespace BearGraphics
{
	namespace Impl
	{

		class BearCasterObject
		{
			BEAR_CLASS_STATIC(BearCasterObject);
		private:
			template<typename C>
			static inline void*CastParent( C*, BearGraphicsObjectType OutType)
			{
				return 0;
			}
#define REGISTER_OBJECT(EType,Class,Parent)  template<>		static inline void*CastParent<BearRenderBase::Class>(BearRenderBase::Class *C,BearGraphicsObjectType OutType) { BearRenderBase::Parent*P= static_cast<BearRenderBase::Parent*>(C); if(OutType==BearTypeManager::GetType<BearRenderBase::Parent>()) return reinterpret_cast<void*>(P); return CastParent<BearRenderBase::Parent>(P,OutType); }
#include "BearGraphics_Objects.h"
		public:
			static inline void*Cast(void*in, BearGraphicsObjectType InType, BearGraphicsObjectType OutType)
			{
				if (OutType == GOT_None)return 0;
				switch (InType)
				{
#define REGISTER_OBJECT(EType,Class,Parent) case EType: return CastParent<BearRenderBase::Class>(reinterpret_cast<BearRenderBase::Class*>(in),OutType);
#include "BearGraphics_Objects.h"
				default:
					return 0;
					break;
				}
			//	return 0;
			}
		};
	}
}