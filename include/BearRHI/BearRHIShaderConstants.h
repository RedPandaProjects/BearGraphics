#pragma once 
namespace BearRHI
{
	class BearRHIShaderConstants
	{
	public:
		virtual void*Lock() = 0;
		virtual void Unlock() = 0;
	};
}