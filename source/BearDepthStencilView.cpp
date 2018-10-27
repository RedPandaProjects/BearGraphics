#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearDepthStencilViewRef::BearDepthStencilViewRef()
{
}

BearGraphics::BearDepthStencilViewRef::~BearDepthStencilViewRef()
{
	clear();
}

void BearGraphics::BearDepthStencilViewRef::copy(const BearDepthStencilViewRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearDepthStencilViewRef::swap(BearDepthStencilViewRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearDepthStencilViewRef & BearGraphics::BearDepthStencilViewRef::operator=(const BearDepthStencilViewRef & right)
{
	copy(right);
	return*this;
	// TODO: вставьте здесь оператор return
}

BearGraphics::BearDepthStencilViewRef::BearDepthStencilViewRef(const BearDepthStencilViewRef & right)
{
	copy(right);
}

void BearGraphics::BearDepthStencilViewRef::create(bsize w, bsize h, BearDepthStencilFormat format)
{
	if (!RHIFactoty)return;
	clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->createDepthStencilView(w, h, format);
}

void BearGraphics::BearDepthStencilViewRef::generateMips()
{
	if (!empty())return;
	m_data.get()->resource->generateMips();
}

void BearGraphics::BearDepthStencilViewRef::clearDepth(float debpt)
{
	if (!empty())return;
	m_data.get()->resource->clearDepth(debpt);
}

void BearGraphics::BearDepthStencilViewRef::clearStencill(uint8 mask)
{
	if (!empty())return;
	m_data.get()->resource->clearStencil(mask);
}

void BearGraphics::BearDepthStencilViewRef::resize(bsize w, bsize h)
{
	if (!empty())return;
	m_data.get()->resource->resize(w, h);
}

void BearGraphics::BearDepthStencilViewRef::clear()
{
	m_data.clear();
}

bool BearGraphics::BearDepthStencilViewRef::empty() const
{
	return m_data.empty();
}
BearGraphics::BearDepthStencilViewRef::data::data()
{
	resource = 0;
}
BearGraphics::BearDepthStencilViewRef::data::~data()
{
	if (resource)RHIFactoty->destroyDepthStencilView(resource);
}