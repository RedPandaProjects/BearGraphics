#pragma once



#include "BearGraphics.hpp"
#include "BearRHI/BearRHIFactory.h"
#include "BearRHI/BearRenderHardwareInterface.h"

BEARGRAPHICS_API BearRHI::BearRHIFactory*GFactory = 0;
BEARGRAPHICS_API BearRHI::BearRenderHardwareInterface*GRenderHardwareInterface = 0;
#ifndef BEAR_GRAPHICS_EXPORTS
extern "C"
{
	BEARPROJECT_EXPORT bool RHIInitialize();
}
#endif