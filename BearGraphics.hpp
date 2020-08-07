#pragma once

#pragma warning(disable:4995)
#include "../BearCore/BearCore.hpp"

#ifdef BEARGRAPHICS_EXPORTS
#define BEARGRAPHICS_API   BEARDLL_EXPORT
#else
#define BEARGRAPHICS_API  BEARDLL_IMPORT
#endif
#include "BearGraphicsEnums.h"


#include "BearRHI/BearRHIObject.h"

namespace BearRHI
{
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...) class  BearRHI##Name ;
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) class  BearRHI##Name;
#include "BearTemplate/BearGraphicsObjectsList.h"
}



#define RENDER_LEVEL_1_REGISTER 0
namespace BearRHI
{
#include "BearTemplate/BearGraphicsFactoryOfDefinitionsForRegistration.h"
#include "BearTemplate/BearGraphicsObjectsList.h"
}

#include "BearTemplate/BearGraphicsTypeManager.h"
#include "BearTemplate/BearGraphicsRemover.h"
#include "BearTemplate/BearGraphicsCaster.h"
#include "BearTemplate/BearFactoryPointer.h"
#include "BearResource/BearImage.h"


#include "BearDescription/BearDispatchRaysDescription.h"

#define RENDER_LEVEL_0_REGISTER 0
namespace BearRHI
{
#include "BearTemplate/BearGraphicsFactoryOfDefinitionsForRegistration.h"
#include "BearTemplate/BearGraphicsObjectsList.h"
}
#include "BearDescription/BearViewportDescription.h"
#include "BearDescription/BearPipelineGraphicsDescription.h"
#include "BearDescription/BearPipelineMeshDescription.h"
#include "BearDescription/BearPipelineRayTracingDescription.h"
#include "BearDescription/BearRootSignatureDescription.h"
#include "BearDescription/BearDescriptorHeapDescription.h"
#include "BearDescription/BearSamplerDescription.h"
#include "BearDescription/BearRenderPassDescription.h"
#include "BearDescription/BearFrameBufferDescription.h"
#include "BearDescription/BearBottomLevelDescription.h"
#include "BearDescription/BearTopLevelDescription.h"
#include "BearDescription/BearRayTracingShaderTableDescription.h"

#include "BearRenderInterface.h"
#include "BearRenderStats.h"
#include "BearUtils/BearContextEventLock.h"
#include "BearSystem/BearWindow.h"