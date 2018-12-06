#pragma once 

namespace BearGraphics
{
	class BEARGRAPHICS_API BearTexture2DRef
	{
	public:
		friend class BearRenderInterface;
		BearTexture2DRef();
		~BearTexture2DRef();
		void Create(const BearImage&image,bsize depth=0, bool dynamic = false);
		void Create(bsize w, bsize h, bsize mip, BearTexturePixelFormat format,bool dynamic=true);
		void Clear();
		void*Lock(bsize mip);
		void Unlock();
		BearCore::BearFVector2 GetSize()const;
		inline bool Empty()const { return m_data.empty(); }
		inline bool IsOne()const { return m_data.is_one(); }
		void Copy(const BearTexture2DRef&right);
		void Swap(BearTexture2DRef&right);
		BearTexture2DRef(const BearTexture2DRef&right);
		BearTexture2DRef&operator=(const BearTexture2DRef&right);
	private:
		struct data
		{
			BearRHI::BearRHITexture2D*resource;
			BearCore::BearFVector2 size;
			data();
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;
	};
}