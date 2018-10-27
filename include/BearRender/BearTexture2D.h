#pragma once 

namespace BearGraphics
{
	class BEARGRAPHICS_API BearTexture2DRef
	{
	public:
		friend class BearRenderInterface;
		BearTexture2DRef();
		~BearTexture2DRef();
		void create(const BearImage&image,bsize depth=0, bool dynamic = false);
		void create(bsize w, bsize h, bsize mip, BearTexturePixelFormat format,bool dynamic=true);
		void clear();
		void*lock(bsize mip);
		void unlock();

		bool empty()const;
		void copy(const BearTexture2DRef&right);
		void swap(BearTexture2DRef&right);
		BearTexture2DRef(const BearTexture2DRef&right);
		BearTexture2DRef&operator=(const BearTexture2DRef&right);
	private:
		struct data
		{
			BearRHI::BearRHITexture2D*resource;
			data();
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;
	};
}