#pragma once
#include "BearCore.hpp"
#ifndef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif
#include "BearGraphicsEnums.h"

#include "BearRenderInterfaceBase.h"
#include "BearRenderObject.h"
#include "BearRenderShaderResourceViewBase.h"
#include "BearRenderUnorderedAccessViewBase.h"
#include "BearRenderTexture2DBase.h"
#include "BearRenderTexture2DUAVBase.h"
#include "BearRenderTargetViewBase.h"
#include "BearRenderViewportBase.h"
#include "BearRenderShaderBase.h"
#include "BearRenderPipelineBase.h"
#include "BearRenderFrameBufferBase.h"
#include "BearRenderIndexBufferBase.h"
#include "BearRenderVertexBufferBase.h"
#include "BearRenderUniformBufferBase.h"

#include "BearRenderRootSignatureBase.h"
#include "BearRenderDescriptorHeapBase.h"
#include "BearRenderSamplerStateBase.h"
//RTX
#include "BearRenderAccelerationStructuresBase.h"

#include "BearTemplate/BearGraphicsTypeManager.h"
#include "BearTemplate/BearGraphicsRemover.h"
#include "BearTemplate/BearGraphicsCaster.h"
#include "BearResource/BearFactoryPointer.h"
#include "BearRenderContextBase.h"
#include "BearDescription/BearRenderDescriptorHeapDescription.h"
#include "BearDescription/BearRenderRootSignatureDescription.h"
#include "BearDescription/BearRenderFrameBufferDescription.h"
#include "BearDescription/BearRenderPipelineDescription.h"
#include "BearDescription/BearRenderViewportDescription.h"
#include "BearDescription/BearRenderSamplerDescription.h"
#include "BearDescription/BearRenderTargetViewDescription.h"
#include "BearDescription/BearRenderAccelerationStructuresDescription.h"
#include "BearDescription/BearRenderRTXPipelineDescription.h"
#include "BearRenderFactoryBase.h"

#include "BearTextureUtils.h"

extern "C"  BEARPROJECT_EXPORT void RenderInitialize();
extern "C"  BEARPROJECT_EXPORT  void RenderDestroy();
#ifndef BEAR_GRAPHICS_EXPORTS
extern BEARPROJECT_IMPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
#else
extern BEARPROJECT_EXPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
#endif
