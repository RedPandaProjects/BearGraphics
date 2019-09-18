#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderShaderBase:public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderShaderBase)
	public:
		BearRenderShaderBase() {}
		virtual ~BearRenderShaderBase() = 0;
		virtual bool CompileText(const bchar*Text,BearCore::BearString &Out) = 0;
	};
}