#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearTexture2DRef::BearTexture2DRef()
{
}

BearGraphics::BearTexture2DRef::~BearTexture2DRef()
{
	Clear();
}

void BearGraphics::BearTexture2DRef::Create(const BearImage & image, bsize depth , bool dynamic)
{
	if (image.Empty())return;
	if (!RHIFactoty)return;
	if (BearRHI::BearRHITextureUtils::isCompressor(image.GetFormat()))
		BEAR_FATALERROR(image.GetSize().x % 4 == 0 && image.GetSize().y % 4 == 0, TEXT("Ќекоректный размер[%dx%d] картики типа BC"), uint32(image.GetSize().x), uint32(image.GetSize().y));
	
	BEAR_FATALERROR(image.GetDepth() > depth, TEXT("«начение глубены [%llu] вышло за пределы [%llu] масива"), depth, image.GetDepth());
	m_data.get()->~data();
	m_data.get()->resource = RHIFactoty->CreateTexture2D(image.GetSize().x, image.GetSize().y, image.GetMips(), image.GetFormat(), dynamic, (uint8*)*image+BearRHI::BearRHITextureUtils::GetSizeInMemory(image.GetSize().x, image.GetSize().y,image.GetMips(),image.GetFormat())*depth);
	m_data.get()->size.x = static_cast<float>(image.GetSize().x);
	m_data.get()->size.y = static_cast<float>(image.GetSize().y);
}

void BearGraphics::BearTexture2DRef::Create(bsize w, bsize h, bsize mip, BearTexturePixelFormat format, bool dynamic)
{
	if (!RHIFactoty)return;
	m_data.get()->~data();
	m_data.get()->resource = RHIFactoty->CreateTexture2D(w, h, mip,format, dynamic,0);
	m_data.get()->size.x = static_cast<float>(w);
	m_data.get()->size.y = static_cast<float>(h);
}

void BearGraphics::BearTexture2DRef::Clear()
{
	m_data.clear();
}

void * BearGraphics::BearTexture2DRef::Lock(bsize mip)
{
	if(Empty())
	return nullptr;
	return m_data.get()->resource->Lock(mip);
}

void BearGraphics::BearTexture2DRef::Unlock()
{
	if (Empty())return;
	return m_data.get()->resource->Unlock();
}

BearCore::BearFVector2 BearGraphics::BearTexture2DRef::GetSize() const
{
	if (Empty())
		return BearCore::BearFVector2();
	return  m_data.get()->size;
}


void BearGraphics::BearTexture2DRef::Unload()
{
	m_data.get()->~data();
}

void BearGraphics::BearTexture2DRef::Copy(const BearTexture2DRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearTexture2DRef::Swap(BearTexture2DRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearTexture2DRef::BearTexture2DRef(const BearTexture2DRef & right)
{
	Copy(right);
}

BearGraphics::BearTexture2DRef & BearGraphics::BearTexture2DRef::operator=(const BearTexture2DRef & right)
{
	Copy(right);
	return*this;
}
BearGraphics::BearTexture2DRef::data::data() :resource(0) {}
BearGraphics::BearTexture2DRef::data::~data() { if (resource)RHIFactoty->DestroyTexture2D(resource); }
