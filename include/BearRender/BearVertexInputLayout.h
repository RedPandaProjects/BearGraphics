#pragma once 

namespace BearGraphics
{

	class BEARGRAPHICS_API BearVertexInputLayoutInitializer
	{
	public:
		friend class BearRenderInterface;
		BearVertexInputLayoutInitializer();
		~BearVertexInputLayoutInitializer();
		void appendItem(const bchar*name,BearInputLayoutElementType type);
		bsize count()const;
		const bchar*getName(bsize id)const;
		BearInputLayoutElementType getType(bsize id)const;
		void clear();
		static bsize GetSizeElement(BearInputLayoutElementType type);
		void copyToVertexBuffer(bsize id,void *buffer,void *src, bsize count);
		void copyToVertexBuffer(const bchar*str,void *buffer,void* src,bsize count);
		bsize getStride();
	private:
		bsize getAppendsItemsSize(bsize id);
		struct Item 
		{
			BearCore::BearString32 name;
			BearInputLayoutElementType type;
			bool operator==(const bchar*n)const {return BearCore::BearString::Compare(name,n)==0;}
		};
		Item * findItem(const bchar*str);

		BearCore::BearVector<Item> m_items;
	};
#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 
#define  CREATE_RENDERRESOURCE_ARGUMENTS1 ,void*data,bsize size
#define  CREATE_RENDERRESOURCE_ARGUMENTS2 ,data,size
	CREATE_RENDERRESOURCE_CLASS1(VertexInputLayout);
#undef   CREATE_RENDERRESOURCE_ARGUMENTS1 
#undef   CREATE_RENDERRESOURCE_ARGUMENTS2 
}