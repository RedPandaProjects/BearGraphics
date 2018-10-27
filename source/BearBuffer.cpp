#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
#define CREATE_BUFFER_CLASS(name)\
BearGraphics::Bear##name##BufferRef::Bear##name##BufferRef()\
{\
}\
\
BearGraphics::Bear##name##BufferRef::~Bear##name##BufferRef()\
{\
	clear();\
}\
\
void BearGraphics::Bear##name##BufferRef::create(void * data, bsize size, bool dynamic)\
{\
	clear();\
	if (!RHIFactoty)return;\
	m_data.create();\
	m_data.get()->buffer = RHIFactoty->create##name##Buffer(data, size, dynamic);\
}\
\
void BearGraphics::Bear##name##BufferRef::create(bsize size)\
{\
	create(0, size, true);\
}\
\
void BearGraphics::Bear##name##BufferRef::clear()\
{\
	m_data.clear();\
}\
\
void * BearGraphics::Bear##name##BufferRef::lock()\
{\
	if (empty())return 0;\
	return m_data.get()->buffer->lock();\
}\
\
void BearGraphics::Bear##name##BufferRef::unlock()\
{\
	if (empty())return ;\
	 m_data.get()->buffer->unlock();\
}\
\
bool BearGraphics::Bear##name##BufferRef::empty() const\
{\
	return m_data.empty();\
}\
void BearGraphics::Bear##name##BufferRef::copy(const Bear##name##BufferRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::Bear##name##BufferRef::swap(Bear##name##BufferRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::Bear##name##BufferRef & BearGraphics::Bear##name##BufferRef::operator=(const Bear##name##BufferRef & right)\
{\
	copy(right);\
	return*this;\
}\
\
BearGraphics::Bear##name##BufferRef::Bear##name##BufferRef(const Bear##name##BufferRef & right)\
{\
	copy(right);\
}\
BearGraphics::Bear##name##BufferRef::data::data()\
{\
	buffer = 0;\
}\
BearGraphics::Bear##name##BufferRef::data::~data()\
{\
if(buffer)\
	RHIFactoty->destroy##name##Buffer(buffer);\
}

CREATE_BUFFER_CLASS(Vertex)
CREATE_BUFFER_CLASS(Index)
