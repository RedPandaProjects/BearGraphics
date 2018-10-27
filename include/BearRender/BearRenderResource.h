#pragma once 
#define  CREATE_RENDERRESOURCE_ARGUMENTS1
#define  CREATE_RENDERRESOURCE_ARGUMENTS2
#define CREATE_RENDERRESOURCE_CLASS1(name)\
class BEARGRAPHICS_API Bear##name##Ref\
{\
public:\
friend class BearRenderInterface;\
	Bear##name##Ref();\
	Bear##name##Ref(const Bear##name##Initializer&Initializer CREATE_RENDERRESOURCE_ARGUMENTS1);\
	~Bear##name##Ref();\
	void copy(const Bear##name##Ref&right);\
	void swap(Bear##name##Ref&right);\
	Bear##name##Ref&operator=(const Bear##name##Ref&right);\
	Bear##name##Ref(const Bear##name##Ref&right);\
	bool empty()const;\
	void clear();\
private:\
	struct data\
	{\
		data();\
		~data();\
		BearRHI::BearRHI##name * reosurce;\
	};\
	BearCore::BearMemoryMultiRef<data> m_data;\
};
#define CREATE_RENDERRESOURCE_CLASS2(name)\
BearGraphics::Bear##name##Ref::Bear##name##Ref()\
{\
}\
BearGraphics::Bear##name##Ref::Bear##name##Ref(const Bear##name##Initializer & Initializer CREATE_RENDERRESOURCE_ARGUMENTS1)\
{\
	if (!RHIFactoty)return;\
	m_data.create();\
	m_data.get()->reosurce = RHIFactoty->create##name##(Initializer CREATE_RENDERRESOURCE_ARGUMENTS2);\
	if (!m_data.get()->reosurce)\
	{\
		clear();\
	}\
}\
BearGraphics::Bear##name##Ref::~Bear##name##Ref()\
{\
	clear();\
}\
void BearGraphics::Bear##name##Ref::copy(const Bear##name##Ref & right)\
{\
	m_data = right.m_data;\
}\
void BearGraphics::Bear##name##Ref::swap(Bear##name##Ref & right)\
{\
	right.m_data.swap(right.m_data);\
}\
BearGraphics::Bear##name##Ref & BearGraphics::Bear##name##Ref::operator=(const Bear##name##Ref & right)\
{\
	copy(right);\
	return*this;\
}\
BearGraphics::Bear##name##Ref::Bear##name##Ref(const Bear##name##Ref & right)\
{\
	copy(right);\
}\
bool BearGraphics::Bear##name##Ref::empty() const\
{\
	return m_data.empty();\
}\
void BearGraphics::Bear##name##Ref::clear()\
{\
	m_data.clear();\
}\
BearGraphics::Bear##name##Ref::data::data() :reosurce(0)\
{\
}\
BearGraphics::Bear##name##Ref::data::~data()\
{\
	if (reosurce)\
		RHIFactoty->destroy##name##(reosurce);\
}
