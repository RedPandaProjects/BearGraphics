#include "BearGraphics.hpp"
extern BEARGRAPHICS_API BearRHI::BearRHIFactory*RHIFactoty;
#define CREATE_BUFFER_CLASS(name)\
BearGraphics::Bear##name##BufferRef::Bear##name##BufferRef()\
{\
}\
\
BearGraphics::Bear##name##BufferRef::~Bear##name##BufferRef()\
{\
	Clear();\
}\
\
void BearGraphics::Bear##name##BufferRef::Create(void * data, bsize size, bool dynamic)\
{\
	Clear();\
	if (!RHIFactoty)return;\
	m_data.create();\
	m_data.get()->buffer = RHIFactoty->Create##name##Buffer(data, size, dynamic);\
}\
\
void BearGraphics::Bear##name##BufferRef::Create(bsize size)\
{\
	Create(0, size, true);\
}\
\
void BearGraphics::Bear##name##BufferRef::Clear()\
{\
	m_data.clear();\
}\
\
void * BearGraphics::Bear##name##BufferRef::Lock()\
{\
	if (Empty())return 0;\
	return m_data.get()->buffer->Lock();\
}\
\
void BearGraphics::Bear##name##BufferRef::Unlock()\
{\
	if (Empty())return ;\
	 m_data.get()->buffer->Unlock();\
}\
void BearGraphics::Bear##name##BufferRef::Copy(const Bear##name##BufferRef & right)\
{\
	m_data = right.m_data;\
}\
\
void BearGraphics::Bear##name##BufferRef::Swap(Bear##name##BufferRef & right)\
{\
	m_data.swap(right.m_data);\
}\
\
BearGraphics::Bear##name##BufferRef & BearGraphics::Bear##name##BufferRef::operator=(const Bear##name##BufferRef & right)\
{\
	Copy(right);\
	return*this;\
}\
\
BearGraphics::Bear##name##BufferRef::Bear##name##BufferRef(const Bear##name##BufferRef & right)\
{\
	Copy(right);\
}\
BearGraphics::Bear##name##BufferRef::data::data()\
{\
	buffer = 0;\
}\
BearGraphics::Bear##name##BufferRef::data::~data()\
{\
if(buffer)\
	RHIFactoty->Destroy##name##Buffer(buffer);\
}

CREATE_BUFFER_CLASS(Vertex)
CREATE_BUFFER_CLASS(Index)
