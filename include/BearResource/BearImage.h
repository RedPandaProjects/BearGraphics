#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearImage
	{
	public:
		BearImage();

		BearImage(bsize w, bsize h,bool mip=false,bsize depth = 1, BearTexturePixelFormat px = TPF_R8G8B8A8);
		void fill(const BearCore::BearColor &color = BearCore::BearColor::Brown);
		void create(bsize w, bsize h, bool mip = false, bsize depth = 1, BearTexturePixelFormat px = TPF_R8G8B8A8);
		void append(bsize x, bsize y, const BearImage&img,bsize x_src,bsize y_src,bsize w_src,bsize h_src, bsize dst_depth, bsize src_depth);
		void append(bsize x, bsize y, const BearImage&img,bsize dst_depth,bsize src_depth);

		void scale(bsize w, bsize h);

		void scaleCanvas(bsize w, bsize h);
		

		void generateMipmap(bsize depth);
		void generateMipmap();
		void clearMipLevels();

		void normalizedSizeNotScale();
		void normalizedSize();

		BearCore::BearColor getPixel(bsize x, bsize y, bsize d = 0)const;
		void setPixel(const BearCore::BearColor&color, bsize x, bsize y, bsize d = 0);
		
		bool loadDDSFromFile(const bchar*str);
		bool loadDDSFromInput(const BearCore::BearInputStream&stream);
		bool loadDDSFromBuffer(const BearCore::BearBufferedReader&stream);

		bool loadFromFile(const bchar*str);
		bool loadFromInput(const BearCore::BearInputStream&stream);
		bool loadFromBuffer(const BearCore::BearBufferedReader&stream);

		bool loadFromFile(bsize depth, const bchar*str);
		bool loadFromInput(bsize depth, const BearCore::BearInputStream&stream);
		bool loadFromBuffer(bsize depth, const BearCore::BearBufferedReader&stream);

		bool saveToJpg(const bchar*name, bsize depth = 0);
		bool saveToPng(const bchar*name, bsize depth = 0);
		bool saveToBmp(const bchar*name, bsize depth = 0);
		bool saveToTga(const bchar*name, bsize depth = 0);
		bool saveToDds(const bchar*name);

		void*operator*();
		const void*operator*()const;

		void clear();
		~BearImage();

		bool empty() const;

		BearImage(const BearImage&img);
		void copy(const BearImage&img);
		void swap(BearImage&img);
		BearImage&operator=(const BearImage&img);
		void convert(BearTexturePixelFormat format);

		BearTexturePixelFormat getFormat()const;
		bsize getDepth()const;
		bsize getMips()const;
		bsize getSizeInMemory()const;
		BearCore::BearVector2<bsize>getSize()const;

	private:
		void resize(bsize w, bsize h, bsize depth, BearTexturePixelFormat px);
		bsize m_w, m_h,m_mips,m_depth;
		BearTexturePixelFormat m_px;
		uint8* m_images;

	};
}
