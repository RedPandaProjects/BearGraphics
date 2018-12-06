#pragma once 

namespace BearGraphics
{
	class BEARGRAPHICS_API BearTexture2DArrayRef
	{
	public:
		friend class BearRenderInterface;
		BearTexture2DArrayRef();
		~BearTexture2DArrayRef();
		void Create(const BearImage&image);
		void Create(bsize w, bsize h, bsize depth, bsize mip, BearTexturePixelFormat format);
		void Clear();
		void*Lock(bsize depth,bsize mip);
		void Unlock();
		BearCore::BearFVector2 GetSize()const;
		inline bool Empty()const { return m_data.empty(); }
		inline bool IsOne()const { return m_data.is_one(); }
		void Copy(const BearTexture2DArrayRef&right);
		void Swap(BearTexture2DArrayRef&right);
		BearTexture2DArrayRef(const BearTexture2DArrayRef&right);
		BearTexture2DArrayRef&operator=(const BearTexture2DArrayRef&right);
	private:
		struct data
		{
			BearRHI::BearRHITexture2DArray*resource;
			BearCore::BearFVector2 size;
			data();
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;
	};
}