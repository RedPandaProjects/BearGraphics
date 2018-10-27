#pragma once 
namespace BearRHI
{
	class BearRHIVertexBuffer
	{
	public:
		virtual void*lock()=0;
		virtual void unlock()=0;
	};
}