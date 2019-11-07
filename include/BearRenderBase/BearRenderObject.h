#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderObject)
	public:
		BearRenderObject() {}
		virtual ~BearRenderObject()=0;
		virtual void*GetHandle();
	};
}