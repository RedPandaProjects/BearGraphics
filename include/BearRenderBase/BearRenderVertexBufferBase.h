#pragma once 
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderVertexBufferBase :public BearRenderObject
	{
		BEAR_CLASS_NO_COPY(BearRenderVertexBufferBase)
	public:
		BearRenderVertexBufferBase() {}
		virtual void Create(bsize stride , bsize count, void*data = 0) = 0;
		virtual void* Lock() = 0;
		virtual void Unlock() = 0;
		virtual void Clear() = 0;
		virtual ~BearRenderVertexBufferBase() = 0;
	};
}