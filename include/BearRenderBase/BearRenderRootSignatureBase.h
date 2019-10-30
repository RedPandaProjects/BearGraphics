#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderRootSignatureBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderRootSignatureBase)
	public:
		BearRenderRootSignatureBase() {}
		virtual ~BearRenderRootSignatureBase() = 0;
	};
}