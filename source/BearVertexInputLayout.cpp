#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty ;
BearGraphics::BearVertexInputLayoutInitializer::BearVertexInputLayoutInitializer()
{
}

BearGraphics::BearVertexInputLayoutInitializer::~BearVertexInputLayoutInitializer()
{
	clear();
}

void BearGraphics::BearVertexInputLayoutInitializer::appendItem(const bchar* name, BearInputLayoutElementType type)
{
	auto a= findItem(name);
	if (a)
	{
		a->type = type;
	}
	Item item;
	BearCore::BearString::Copy( item.name ,name);
	item.type = type;
	m_items.push_back(item);
}


bsize BearGraphics::BearVertexInputLayoutInitializer::count() const
{
	return m_items.size();
}

const bchar* BearGraphics::BearVertexInputLayoutInitializer::getName(bsize id) const
{
	if (m_items.size() > id)
		return m_items[id].name;
	return TEXT("");
}

BearGraphics::BearInputLayoutElementType BearGraphics::BearVertexInputLayoutInitializer::getType(bsize id) const
{
	if (m_items.size() > id)
		return m_items[id].type;
	return BearGraphics::ILE_R32G32B32A32_FLOAT;
}

void BearGraphics::BearVertexInputLayoutInitializer::clear()
{
	m_items.clear();
}

bsize BearGraphics::BearVertexInputLayoutInitializer::GetSizeElement(BearInputLayoutElementType type)
{
	switch (type)
	{
	case BearGraphics::ILE_R32_FLOAT:
		return 4;
		break;
	case BearGraphics::ILE_R32G32_FLOAT:
		return 8;
		break;
	case BearGraphics::ILE_R32G32B32_FLOAT:
		return 12;
		break;
	case BearGraphics::ILE_R32G32B32A32_FLOAT:
		return 16;
		break;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearGraphics::BearVertexInputLayoutInitializer::copyToVertexBuffer(bsize id, void * buffer, void * src, bsize count)
{
	if (id >= m_items.size())return;
	bsize sizeTo = getAppendsItemsSize(id);
	bsize size = getStride();
	bsize sizeType = GetSizeElement(m_items[id].type);
	uint8*to = (uint8*)buffer;
	for (bsize i = 0; i < count; i++)
	{
		BearCore::bear_copy(to + sizeTo, (uint8*)src+size*i,sizeType);
		to += size;
		
	}
}

void BearGraphics::BearVertexInputLayoutInitializer::copyToVertexBuffer(const bchar* str, void * buffer, void * src, bsize count)
{
	auto t = findItem(str);
	if (!t)
		return ;
	copyToVertexBuffer((bsize)((uint8*)t - (uint8*)&m_items[0]), buffer, src, count);
}


bsize BearGraphics::BearVertexInputLayoutInitializer::getStride()
{
	return getAppendsItemsSize(m_items.size() );
}

bsize BearGraphics::BearVertexInputLayoutInitializer::getAppendsItemsSize(bsize id)
{
	auto begin = m_items.begin();
	auto end = m_items.begin()+id;
	bsize size = 0;
	while (begin != end)
	{
		size += GetSizeElement(begin->type);
		begin++;

	}
	return size;
}

BearGraphics::BearVertexInputLayoutInitializer::Item * BearGraphics::BearVertexInputLayoutInitializer::findItem(const bchar* str)
{
	auto begin=BearCore::bear_find_if(m_items.begin(), m_items.end(), BearCore::bear_bind_compare(BearCore::BearEqual(), str));
	if (begin == m_items.end())return 0;
	return &*begin;
}
#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 
#define  CREATE_RENDERRESOURCE_ARGUMENTS1 ,void*data,bsize size
#define  CREATE_RENDERRESOURCE_ARGUMENTS2 ,data,size
CREATE_RENDERRESOURCE_CLASS2(VertexInputLayout);