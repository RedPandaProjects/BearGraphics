#pragma once 
namespace BearRHI
{
	class BearRHIVertexBuffer
	{
	public:
		virtual void*Lock()=0;
		virtual void Unlock()=0;
	};
}