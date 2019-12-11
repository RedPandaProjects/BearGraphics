#pragma once



#include "BearGraphics.hpp"
#include "BearRHI/BearRHIFactory.h"
#include "BearRHI/BearRenderHardwareInterface.h"

extern BEARGRAPHICS_API BearRHI::BearRHIFactory*GFactory ;
extern BEARGRAPHICS_API BearRHI::BearRenderHardwareInterface*GRenderHardwareInterface;
#ifndef BEAR_GRAPHICS_EXPORTS
extern "C"
{
	BEARPROJECT_EXPORT bool RHIInitialize();
}
#endif