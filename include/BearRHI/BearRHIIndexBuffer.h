#pragma once 
namespace BearRHI
{
	class BearRHIIndexBuffer
	{
	public:
		virtual void*Lock()=0;
		virtual void Unlock()=0;
	};
}