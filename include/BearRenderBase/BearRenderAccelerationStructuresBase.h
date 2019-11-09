#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderAccelerationStructuresBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderAccelerationStructuresBase)
	public:
		BearRenderAccelerationStructuresBase() {}
		virtual ~BearRenderAccelerationStructuresBase() = 0;
	};
}