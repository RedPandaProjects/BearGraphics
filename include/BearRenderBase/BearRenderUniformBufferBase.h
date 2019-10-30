#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderUniformBufferBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderUniformBufferBase)
	public:
		BearRenderUniformBufferBase() {}
		virtual void Create( bsize size, void*data = 0, bool dynamic = false) = 0;
		virtual void* Lock() = 0;
		virtual void Unlock() = 0;
		virtual void Clear() = 0;
		virtual ~BearRenderUniformBufferBase() = 0;
	};
}