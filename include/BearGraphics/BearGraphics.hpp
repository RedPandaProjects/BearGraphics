#pragma once
#include "BearCore.hpp"

#ifdef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_EXPORT
#else
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif
#include "BearGraphicsEnums.h"

namespace BearRenderBase
{
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...) class  BearRHI##Name ;
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) class  BearRHI##Name;
#include "BearTemplate/BearGraphicsObjectsList.h"
}
#include "BearTemplate/BearGraphicsTypeManager.h"
#include "BearTemplate/BearGraphicsRemover.h"

namespace BearRHI
{
#include "BearTemplate/BearGraphicsFactoryOfDefinitionsForRegistration.h"
#include "BearTemplate/BearGraphicsObjectsList.h"
}


#include "BearTemplate/BearGraphicsCaster.h"
#include "BearTemplate/BearFactoryPointer.h"
/*

#define RENDER_LEVEL_0_REGISTER 0
namespace BearRHI
{
#include "BearTemplate/BearGraphicsFactoryOfDefinitionsForRegistration.h"
#include "BearTemplate/BearGraphicsObjectsList.h"
}
#include "BearDescription/BearRenderViewportDescription.h"*/