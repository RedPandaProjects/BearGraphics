#include "BearGraphics.hpp"
#include "BearRenderBase.h"
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)    BearRHI##Name::~BearRHI##Name(){}
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name)
namespace BearRHI
{
#include "BearTemplate/BearGraphicsObjectsList.h"
}

BearRHI::BearRenderHardwareInterface::~BearRenderHardwareInterface()
{

}
BearRHI::BearRHIFactory::~BearRHIFactory()
{

}