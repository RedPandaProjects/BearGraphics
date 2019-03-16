#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearDepthStencilViewRef::BearDepthStencilViewRef()
{
}

BearGraphics::BearDepthStencilViewRef::~BearDepthStencilViewRef()
{
	Clear();
}

void BearGraphics::BearDepthStencilViewRef::Copy(const BearDepthStencilViewRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearDepthStencilViewRef::Swap(BearDepthStencilViewRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearDepthStencilViewRef & BearGraphics::BearDepthStencilViewRef::operator=(const BearDepthStencilViewRef & right)
{
	Copy(right);
	return*this;
	// TODO: вставьте здесь оператор return
}

BearGraphics::BearDepthStencilViewRef::BearDepthStencilViewRef(const BearDepthStencilViewRef & right)
{
	Copy(right);
}

void BearGraphics::BearDepthStencilViewRef::Create(bsize w, bsize h, BearDepthStencilFormat format)
{
	if (!RHIFactoty)return;
	Clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->CreateDepthStencilView(w, h, format);
}
/*
void BearGraphics::BearDepthStencilViewRef::GenerateMips()
{
	if (Empty())return;
	m_data.get()->resource->GenerateMips();
}*/

void BearGraphics::BearDepthStencilViewRef::ClearDepth(float debpt)
{
	if (Empty())return;
	m_data.get()->resource->ClearDepth(debpt);
}

void BearGraphics::BearDepthStencilViewRef::ClearStencil(uint8 mask)
{
	if (Empty())return;
	m_data.get()->resource->ClearStencil(mask);
}

void BearGraphics::BearDepthStencilViewRef::Resize(bsize w, bsize h)
{
	if (Empty())return;
	m_data.get()->resource->Resize(w, h);
}

void BearGraphics::BearDepthStencilViewRef::Clear()
{
	m_data.clear();
}

BearGraphics::BearDepthStencilViewRef::data::data()
{
	resource = 0;
}
BearGraphics::BearDepthStencilViewRef::data::~data()
{
	if (resource)RHIFactoty->DestroyDepthStencilView(resource);
}