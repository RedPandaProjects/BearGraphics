#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderIndexBufferBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderIndexBufferBase)
	public:
		BearRenderIndexBufferBase() {}
		virtual void Create(bsize count,void*data=0, bool dynamic = false)=0;
		virtual int32* Lock()=0;
		virtual void Unlock() = 0;
		virtual void Clear() = 0;
		virtual ~BearRenderIndexBufferBase() = 0;
	};
}