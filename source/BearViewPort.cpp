#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty ;
BearGraphics::BearViewPortRef::BearViewPortRef()
{
}

BearGraphics::BearViewPortRef::~BearViewPortRef()
{
	close();
}

void BearGraphics::BearViewPortRef::create(BearCore::BearWindow & window, bool vsync)
{
	create((bptr)window.getRef(), window.getSize().x, window.getSize().y, window.getFullScreen(),vsync);
}

void BearGraphics::BearViewPortRef::create(bptr win, bsize wigth, bsize height, bool fullscreen, bool vsync)
{
	close();
	if (!RHIFactoty)return; 
	m_data.create();
	m_data.get()->viewport= RHIFactoty->createViewPort((void*)win,wigth,height,fullscreen,vsync);
}

void BearGraphics::BearViewPortRef::close()
{
	m_data.clear();
}

void BearGraphics::BearViewPortRef::resize(bsize wigth, bsize height)
{
	if (empty())return;
	m_data.get()->viewport->reisze(wigth, height);
}

void BearGraphics::BearViewPortRef::setFullScreen(bool fullscreen)
{
	m_data.get()->viewport->setFullScreen(fullscreen);
}

void BearGraphics::BearViewPortRef::setVsync(bool vsync)
{
}

void BearGraphics::BearViewPortRef::swap()
{
	m_data.get()->viewport->swap();
}

void BearGraphics::BearViewPortRef::clearColor(const BearCore::BearColor & color)
{
	m_data.get()->viewport->clearColor(color);
}

bool BearGraphics::BearViewPortRef::empty() const
{
	return m_data.empty();
}

void BearGraphics::BearViewPortRef::copy(const BearViewPortRef & viewport)
{
	m_data = viewport.m_data;
}

void BearGraphics::BearViewPortRef::swap(BearViewPortRef & viewport)
{
	m_data.swap(viewport.m_data);
}

BearGraphics::BearViewPortRef::BearViewPortRef(const BearViewPortRef & viewport)
{
	copy(viewport);
}

BearGraphics::BearViewPortRef & BearGraphics::BearViewPortRef::operator=(const BearViewPortRef & viewport)
{
	copy(viewport);
	return*this;
}
BearGraphics::BearViewPortRef::data::data():viewport(0)
{

}
BearGraphics::BearViewPortRef::data::~data()
{
	RHIFactoty->destroyViewPort(viewport);
}