#pragma once
#include "BearCore.hpp"

#ifdef BEAR_GRAPHICS_EXPORTS
#define BEARGRAPHICS_API  BEARPROJECT_EXPORT
#else
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
#endif

#include "BearGraphicsEnum.h"

#include "BearRHI/BearRHITextureUtils.h"
#include "BearRHI/BearRHITexture2D.h"

#include "BearRHI/BearRHIView.h"
#include "BearRHI/BearRHIViewPort.h"

#include "BearRHI/BearRHIIndexBuffer.h"
#include "BearRHI/BearRHIVertexBuffer.h"

#include "BearRHI/BearRHIVertexShader.h"
#include "BearRHI/BearRHIVertexShaderCompiler.h"
#include "BearRHI/BearRHIVertexInputLayout.h"

#include "BearRHI/BearRHIPixelShader.h"
#include "BearRHI/BearRHIPixelShaderCompiler.h"

#include "BearRHI/BearRHIStats.h"

#include "BearRHI/BearRHIInterface.h"


#include "BearRender/BearRenderResource.h"

#include "BearRender/BearVertexInputLayout.h"

#include "BearRender/BearShader.h"
#include "BearRender/BearBuffer.h"

#include "BearResource/BearImage.h"
#include "BearRender/BearTexture2D.h"

#include "BearRender/BearDepthStencilView.h"
#include "BearRender/BearRenderTargetView.h"
#include "BearRender/BearViewPort.h"

#include "BearRender/BearStatsInitializers.h"
#include "BearRender/BearStats.h"

#include "BearRender/BearRenderInterface.h"

#include "BearRHI/BearRHIFactory.h"
