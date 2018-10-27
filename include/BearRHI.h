#pragma once
#include "BearCore.hpp"
#define BEARGRAPHICS_API  BEARPROJECT_IMPORT
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
#include "BearRender/BearRenderResource.h" 
#include "BearRender/BearVertexInputLayout.h"

#include "BearRHI/BearRHIPixelShader.h"
#include "BearRHI/BearRHIPixelShaderCompiler.h"

#include "BearRHI/BearRHIStats.h"
#include "BearRender/BearStatsInitializers.h"

#include "BearRHI/BearRHIInterface.h"
#include "BearRHI/BearRHIFactory.h"




extern "C"  __declspec(dllexport)  void RHIInitialize();
extern "C" __declspec(dllexport)  void RHIDestroy();
extern __declspec(dllimport) BearRHI::BearRHIFactory*RHIFactoty;
extern __declspec(dllimport) BearRHI::BearRHIStats*RHIStats;