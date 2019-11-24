#pragma once
namespace BearRHI
{
	class BEARGRAPHICS_API BearRenderHardwareInterface
	{
	public:

		virtual bool SupportRTX() = 0;
		virtual ~BearRenderHardwareInterface() = 0;
	};
}