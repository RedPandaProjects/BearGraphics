#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearRenderTargetViewRef::BearRenderTargetViewRef()
{
}

BearGraphics::BearRenderTargetViewRef::~BearRenderTargetViewRef()
{
	Clear();
}

void BearGraphics::BearRenderTargetViewRef::Copy(const BearRenderTargetViewRef & right)
{
	m_data = right.m_data;
}

void BearGraphics::BearRenderTargetViewRef::Swap(BearRenderTargetViewRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearRenderTargetViewRef & BearGraphics::BearRenderTargetViewRef::operator=(const BearRenderTargetViewRef & right)
{
	Copy(right);
	return*this;
}

BearGraphics::BearRenderTargetViewRef::BearRenderTargetViewRef(const BearRenderTargetViewRef & right)
{
	Copy(right);
}

void BearGraphics::BearRenderTargetViewRef::Create(bsize w, bsize h, BearRenderTargetFormat format)
{
	if (!RHIFactoty)return;
	Clear();
	m_data.create();
	m_data.get()->resource = RHIFactoty->CreateRenderTargetView(w,h,format);
}

void BearGraphics::BearRenderTargetViewRef::ClearColor(const BearCore::BearColor & color)
{
	if (Empty())return;
	m_data.get()->resource->ClearColor(color);
}

void BearGraphics::BearRenderTargetViewRef::Resize(bsize w, bsize h)
{
	if (Empty())return;
	m_data.get()->resource->Reisze(w, h);
}

void BearGraphics::BearRenderTargetViewRef::GenetateMips()
{
	if (Empty())return;
	m_data.get()->resource->GenerateMips();
}

void BearGraphics::BearRenderTargetViewRef::Clear()
{
	m_data.clear();
}
 BearGraphics::BearRenderTargetViewRef::data::data():resource(0)
{
	
}
 
 BearGraphics::BearRenderTargetViewRef::data::~data()
 {
	 if (resource)
		 RHIFactoty->DestroyRenderTargetView(resource);
 }