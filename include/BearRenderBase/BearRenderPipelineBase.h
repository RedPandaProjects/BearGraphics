#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderPipelineBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderPipelineBase)
	public:
		BearRenderPipelineBase() {}
		virtual ~BearRenderPipelineBase() = 0;
		virtual void Set(void*) = 0;
	};
	
}