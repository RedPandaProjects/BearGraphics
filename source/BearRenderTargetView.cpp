#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearRenderTargetViewRef::BearRenderTargetViewRef()
{
}

BearGraphics::BearRenderTargetViewRef::~BearRenderTargetViewRef()
{
	clear();
}

void BearGraphics::BearRenderTargetViewRef::copy(const BearRenderTargetViewRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearRenderTargetViewRef::swap(BearRenderTargetViewRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearRenderTargetViewRef & BearGraphics::BearRenderTargetViewRef::operator=(const BearRenderTargetViewRef & right)
{
	copy(right);
	return*this;
}

BearGraphics::BearRenderTargetViewRef::BearRenderTargetViewRef(const BearRenderTargetViewRef & right)
{
	copy(right);
}

void BearGraphics::BearRenderTargetViewRef::create(bsize w, bsize h, BearRenderTargetFormat format)
{
	if (!RHIFactoty)return;
	clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->createRenderTargetView(w,h,format);
}

void BearGraphics::BearRenderTargetViewRef::clearColor(const BearCore::BearColor & color)
{
	if (empty())return;
	m_data.get()->resource->clearColor(color);
}

void BearGraphics::BearRenderTargetViewRef::resize(bsize w, bsize h)
{
	if (empty())return;
	m_data.get()->resource->reisze(w, h);
}

void BearGraphics::BearRenderTargetViewRef::genetateMips()
{
	if (empty())return;
	m_data.get()->resource->generateMips();
}

void BearGraphics::BearRenderTargetViewRef::clear()
{
	m_data.clear();
}
bool BearGraphics::BearRenderTargetViewRef::empty() const
{
	return m_data.empty();
}
 BearGraphics::BearRenderTargetViewRef::data::data():resource(0)
{
	
}
 
 BearGraphics::BearRenderTargetViewRef::data::~data()
 {
	 if (resource)
		 RHIFactoty->destroyRenderTargetView(resource);
 }