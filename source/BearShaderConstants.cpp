#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
BearGraphics::BearShaderConstantsRef::BearShaderConstantsRef()
{
}

BearGraphics::BearShaderConstantsRef::BearShaderConstantsRef(const BearShaderConstantsInitializer & initializer, bool dynamic)
{
	m_data->resource = RHIFactoty->CreateShaderConstants(initializer, dynamic);
}

BearGraphics::BearShaderConstantsRef::~BearShaderConstantsRef()
{
}

void BearGraphics::BearShaderConstantsRef::Copy(const BearShaderConstantsRef & right)
{
	m_data.copy(right.m_data);
}

void BearGraphics::BearShaderConstantsRef::Swap(BearShaderConstantsRef & right)
{
	m_data.swap(right.m_data);
}

BearGraphics::BearShaderConstantsRef & BearGraphics::BearShaderConstantsRef::operator=(const BearShaderConstantsRef & right)
{
	Copy(right);
	return *this;
}

BearGraphics::BearShaderConstantsRef::BearShaderConstantsRef(const BearShaderConstantsRef & right)
{
	Copy(right);
}


void * BearGraphics::BearShaderConstantsRef::Lock()
{
	if (m_data.empty())
		return nullptr;
	else
		return m_data->resource->Lock();
}

void BearGraphics::BearShaderConstantsRef::Unlock()
{
	if (!m_data.empty())
		 m_data->resource->Unlock();
}

void BearGraphics::BearShaderConstantsRef::Clear()
{
	m_data.clear();
}
BearGraphics::BearShaderConstantsRef::data::~data()
{
	RHIFactoty->DestroyShaderConstants(resource);
}