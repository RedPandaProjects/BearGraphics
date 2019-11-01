#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderDescriptorHeapBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderDescriptorHeapBase)
	public:
		BearRenderDescriptorHeapBase() {}
		virtual ~BearRenderDescriptorHeapBase() = 0;
	};
}