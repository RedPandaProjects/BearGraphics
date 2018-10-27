#pragma once 
namespace BearGraphics
{
#define CREATE_BUFFER_CLASS(name)\
	class BEARGRAPHICS_API Bear##name##BufferRef\
	{\
	public:\
	friend class BearRenderInterface;\
		Bear##name##BufferRef();\
		~Bear##name##BufferRef();\
		void create(void*data, bsize size, bool dynamic);\
		void create(bsize size);\
		void clear();\
		void*lock();\
		void unlock();\
		bool empty()const;\
		\
		void copy(const Bear##name##BufferRef&right);\
		void swap(Bear##name##BufferRef&right);\
		Bear##name##BufferRef&operator=(const Bear##name##BufferRef&right);\
		Bear##name##BufferRef(const Bear##name##BufferRef&right);\
	private:\
		struct data\
		{\
			data();\
			~data();\
			BearRHI::BearRHI##name##Buffer * buffer;\
		\
		};\
		BearCore::BearMemoryMultiRef<data> m_data;\
	};
	CREATE_BUFFER_CLASS(Vertex)
	CREATE_BUFFER_CLASS(Index)
#undef CREATE_BUFFER_CLASS
};