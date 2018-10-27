#include "BearGraphics.hpp"
#include "..\..\..\engine\bear\bearengine\include\BearRender\BearTexture2D.h"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearTexture2DRef::BearTexture2DRef()
{
}

BearGraphics::BearTexture2DRef::~BearTexture2DRef()
{
	clear();
}

void BearGraphics::BearTexture2DRef::create(const BearImage & image, bsize depth , bool dynamic)
{
	if (image.empty())return;
	if (!RHIFactoty)return;
	if (BearRHI::BearRHITextureUtils::isCompressor(image.getFormat()))
		BEAR_FATALERROR(image.getSize().x % 4 == 0 && image.getSize().y % 4 == 0, TEXT("Ќекоректный размер[%dx%d] картики типа BC"), uint32(image.getSize().x), uint32(image.getSize().y));
	
	BEAR_FATALERROR(image.getDepth() > depth, TEXT("«начение глубены [%llu] вышло за пределы [%llu] масива"), depth, image.getDepth());
	clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->createTexture2D(image.getSize().x, image.getSize().y, image.getMips(), image.getFormat(), dynamic, (uint8*)*image+BearRHI::BearRHITextureUtils::GetSizeInMemory(image.getSize().x, image.getSize().y,image.getMips(),image.getFormat())*depth);
}

void BearGraphics::BearTexture2DRef::create(bsize w, bsize h, bsize mip, BearTexturePixelFormat format, bool dynamic)
{
	if (!RHIFactoty)return;
	clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->createTexture2D(w, h, mip,format, dynamic,0);
}

void BearGraphics::BearTexture2DRef::clear()
{
	m_data.clear();
}

void * BearGraphics::BearTexture2DRef::lock(bsize mip)
{
	if(empty())
	return nullptr;
	return m_data.get()->resource->lock(mip);
}

void BearGraphics::BearTexture2DRef::unlock()
{
	if (empty())return;
	return m_data.get()->resource->unlock();
}


bool BearGraphics::BearTexture2DRef::empty() const
{
	return m_data.empty();
}

void BearGraphics::BearTexture2DRef::copy(const BearTexture2DRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearTexture2DRef::swap(BearTexture2DRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearTexture2DRef::BearTexture2DRef(const BearTexture2DRef & right)
{
	copy(right);
}

BearGraphics::BearTexture2DRef & BearGraphics::BearTexture2DRef::operator=(const BearTexture2DRef & right)
{
	copy(right);
	return*this;
}
BearGraphics::BearTexture2DRef::data::data() :resource(0) {}
BearGraphics::BearTexture2DRef::data::~data() { if (resource)RHIFactoty->destroyTexture2D(resource); }
