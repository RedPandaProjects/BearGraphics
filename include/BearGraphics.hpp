#pragma once
#include "BearCore.hpp"

#ifdef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_EXPORT
#else
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif

#include "BearGraphicsEnums.h"

#include "BearRHI/BearRHITextureUtils.h"
#include "BearRHI/BearRHITexture2D.h"
#include "BearRHI/BearRHITexture2DArray.h"

#include "BearRHI/BearRHIView.h"
#include "BearRHI/BearRHIViewPort.h"

#include "BearRHI/BearRHIIndexBuffer.h"
#include "BearRHI/BearRHIVertexBuffer.h"

#include "BearRHI/BearRHIVertexShader.h"
#include "BearRHI/BearRHIVertexShaderCompiler.h"

#include "BearRHI/BearRHIPixelShader.h"
#include "BearRHI/BearRHIPixelShaderCompiler.h"

#include "BearRHI/BearRHIShaderConstants.h"

#include "BearRHI/BearRHIStats.h"

#include "BearRHI/BearRHIInterface.h"
#include "BearRHI/BearRHIDefaultManager.h"

#include "BearRender/BearRenderResource.h"


#include "BearRender/BearShader.h"
#include "BearRender/BearShaderConstants.h"
#include "BearRender/BearBuffer.h"

#include "BearResource/BearImage.h"
#include "BearRender/BearTexture2D.h"
#include "BearRender/BearTexture2DArray.h"

#include "BearRender/BearDepthStencilView.h"
#include "BearRender/BearRenderTargetView.h"
#include "BearRender/BearViewPort.h"

#include "BearRender/BearStatsInitializers.h"
#include "BearRender/BearStats.h"

#include "BearRender/BearRenderInterface.h"

#include "BearRHI/BearRHIFactory.h"

#include "BearResource/BearDefualtManager.h"


# define PI           3.14159265358979323846f