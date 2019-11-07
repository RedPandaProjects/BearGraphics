#include "BearGraphics.hpp"

BearRenderBase::BearRenderTexture2DBase::~BearRenderTexture2DBase()
{

}
void BearRenderBase::BearRenderTexture2DBase::Create(BearGraphics::BearImage&image)
{
	if (image.Empty())
		Clear();
	else
		Create(image.GetSize().x, image.GetSize().y, image.GetMips(), image.GetDepth(), image.GetFormat(), *image,true);
}