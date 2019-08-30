#pragma once
#include "BearCore.hpp"

#ifdef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_EXPORT
#else
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif

#include "BearGraphicsEnums.h"
#include "BearResource/BearImage.h"
#include "BearRender/BearRenderInterface.h"
#include "BearRenderBase.h"
#include "BearTemplate/BearGraphicsTypeManager.h"
