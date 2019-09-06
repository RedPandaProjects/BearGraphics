#pragma once
#include "BearCore.hpp"
#ifndef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif
#include "BearGraphicsEnums.h"
#include "BearRenderInterfaceBase.h"
#include "BearRenderObject.h"
#include "BearRenderShaderResource.h"
#include "BearRenderTexture2DBase.h"
#include "BearRenderTargetViewBase.h"
#include "BearRenderViewportBase.h"
#include "BearTemplate/BearGraphicsTypeManager.h"
#include "BearTemplate/BearGraphicsCaster.h"
#include "BearResource/BearFactoryPointer.h"
#include "BearRenderContextBase.h"
#include "BearRenderFactoryBase.h"

extern "C"  BEARPROJECT_EXPORT void RenderInitialize();
extern "C"  BEARPROJECT_EXPORT  void RenderDestroy();
#ifndef BEAR_GRAPHICS_EXPORTS
extern BEARPROJECT_IMPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
#else
extern BEARPROJECT_EXPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
#endif
