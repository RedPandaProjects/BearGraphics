#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearTexture2DArrayRef::BearTexture2DArrayRef()
{
}

BearGraphics::BearTexture2DArrayRef::~BearTexture2DArrayRef()
{
	Clear();
}

void BearGraphics::BearTexture2DArrayRef::Create(const BearImage & image)
{
	if (image.Empty())return;
	if (!RHIFactoty)return;
	if (BearRHI::BearRHITextureUtils::isCompressor(image.GetFormat()))
		BEAR_FATALERROR(image.GetSize().x % 4 == 0 && image.GetSize().y % 4 == 0, TEXT("Некоректный размер[%dx%d] картики типа BC"), uint32(image.GetSize().x), uint32(image.GetSize().y));
	
	Clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->CreateTexture2DArray(image.GetSize().x, image.GetSize().y, image.GetDepth() , image.GetMips(), image.GetFormat(), (uint8*)*image);
	m_data.get()->size.x = static_cast<float>(image.GetSize().x);
	m_data.get()->size.y = static_cast<float>(image.GetSize().y);
}

void BearGraphics::BearTexture2DArrayRef::Create(bsize w, bsize h, bsize depth, bsize mip, BearTexturePixelFormat format)
{
	if (!RHIFactoty)return;
	Clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->CreateTexture2DArray(w, h, depth, mip,format,0);
	m_data.get()->size.x = static_cast<float>(w);
	m_data.get()->size.y = static_cast<float>(h);
}

void BearGraphics::BearTexture2DArrayRef::Clear()
{
	m_data.clear();
}

void * BearGraphics::BearTexture2DArrayRef::Lock(bsize depth, bsize mip)
{
	if(Empty())
	return nullptr;
	return m_data.get()->resource->Lock(depth,mip);
}

void BearGraphics::BearTexture2DArrayRef::Unlock()
{
	if (Empty())return;
	return m_data.get()->resource->Unlock();
}

BearCore::BearFVector2 BearGraphics::BearTexture2DArrayRef::GetSize() const
{
	if (Empty())
		return BearCore::BearFVector2();
	return  m_data.get()->size;
}


void BearGraphics::BearTexture2DArrayRef::Copy(const BearTexture2DArrayRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearTexture2DArrayRef::Swap(BearTexture2DArrayRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearTexture2DArrayRef::BearTexture2DArrayRef(const BearTexture2DArrayRef & right)
{
	Copy(right);
}

BearGraphics::BearTexture2DArrayRef & BearGraphics::BearTexture2DArrayRef::operator=(const BearTexture2DArrayRef & right)
{
	Copy(right);
	return*this;
}
BearGraphics::BearTexture2DArrayRef::data::data() :resource(0) {}
BearGraphics::BearTexture2DArrayRef::data::~data() { if (resource)RHIFactoty->DestroyTexture2DArray(resource); }
