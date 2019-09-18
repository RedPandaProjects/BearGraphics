#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderInterfaceBase
	{
		BEAR_CLASS_NO_COPY(BearRenderInterfaceBase)
	public:
		BearRenderInterfaceBase() {}
		virtual ~BearRenderInterfaceBase() = 0;
	};
}