#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearImage
	{
	public:
		BearImage();

		BearImage(bsize w, bsize h,bsize mip=1,bsize depth = 1, BearTexturePixelFormat px = TPF_R8G8B8A8);
		void Fill(const BearCore::BearColor &color = BearCore::BearColor::Brown);
		void Create(bsize w, bsize h, bsize mip = 1, bsize depth = 1, BearTexturePixelFormat px = TPF_R8G8B8A8);
		void Append(bsize x, bsize y, const BearImage&img,bsize x_src,bsize y_src,bsize w_src,bsize h_src, bsize dst_depth, bsize src_depth);
		void Append(bsize x, bsize y, const BearImage&img,bsize dst_depth,bsize src_depth);

		void Scale(bsize w, bsize h);

		void ScaleCanvas(bsize w, bsize h);
		

		void GenerateMipmap(bsize depth);
		void GenerateMipmap();
		void ClearMipLevels();

		void NormalizedSizeNotScale();
		void NormalizedSize();

		BearCore::BearColor GetPixel(bsize x, bsize y, bsize d = 0)const;
		void SetPixel(const BearCore::BearColor&color, bsize x, bsize y, bsize d = 0);
		
		bool LoadDDSFromFile(const bchar*str);
		bool LoadDDSFromStream(const BearCore::BearInputStream&stream);
		bool LoadDDSFromBuffer(const BearCore::BearBufferedReader&stream);

		bool LoadFromFile(const bchar*str);
		bool LoadFromStream(const BearCore::BearInputStream&stream);
		bool LoadFromBuffer(const BearCore::BearBufferedReader&stream);

		bool LoadFromFile(bsize depth, const bchar*str);
		bool LoadFromStream(bsize depth, const BearCore::BearInputStream&stream);
		bool LoadFromBuffer(bsize depth, const BearCore::BearBufferedReader&stream);

		bool SaveToJpg(const bchar*name, bsize depth = 0);
		bool SaveToPng(const bchar*name, bsize depth = 0);
		bool SaveToBmp(const bchar*name, bsize depth = 0);
		bool SaveToTga(const bchar*name, bsize depth = 0);
		bool SaveToDds(const bchar*name);

		void*operator*();
		const void*operator*()const;

		void Clear();
		~BearImage();

		bool Empty() const;

		BearImage(const BearImage&img);
		void Copy(const BearImage&img);
		void Swap(BearImage&img);
		BearImage&operator=(const BearImage&img);
		void Convert(BearTexturePixelFormat format);

		BearTexturePixelFormat GetFormat()const;
		bsize GetDepth()const;
		bsize GetMips()const;
		bsize GetSizeInMemory()const;
		BearCore::BearVector2<bsize>GetSize()const;

	private:
		void Resize(bsize w, bsize h, bsize depth, BearTexturePixelFormat px);
		bsize m_w, m_h,m_mips,m_depth;
		BearTexturePixelFormat m_px;
		uint8* m_images;

	};
}
