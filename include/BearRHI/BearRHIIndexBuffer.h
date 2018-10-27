#pragma once 
namespace BearRHI
{
	class BearRHIIndexBuffer
	{
	public:
		virtual void*lock()=0;
		virtual void unlock()=0;
	};
}