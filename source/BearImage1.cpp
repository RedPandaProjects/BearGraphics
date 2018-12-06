#include "BearGraphics.hpp"


BearGraphics::BearImage::BearImage() :m_px(TPF_R8), m_images(0), m_w(0), m_h(0), m_depth(0), m_mips(0)
{
}

BearGraphics::BearImage::BearImage(bsize w, bsize h, bool mip, bsize depth, BearTexturePixelFormat px) : m_px(TPF_R8), m_images(0), m_w(0), m_h(0), m_depth(0), m_mips(0)
{
	Create(w, h, mip, depth, px);
}

void BearGraphics::BearImage::Fill(const BearCore::BearColor & color)
{
	if (Empty())return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	bsize size = BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px);
	for (bsize i = 0; i < m_depth; i++)
	{
		BearRHI::BearRHITextureUtils::Fill(m_images + (size*i), m_w, m_h, m_mips, color, m_px);
	}
}

void BearGraphics::BearImage::Create(bsize w, bsize h, bool mip, bsize depth, BearTexturePixelFormat px)
{
	Clear();
	m_mips = 1;
	m_depth = depth;
	m_w = w;
	m_h = h;
	m_px = px;
	BEAR_FATALERROR(m_depth, TEXT("√лубина неможет равн€тьс€ нулю!"));
	if (mip)
	{
		m_mips = BearRHI::BearRHITextureUtils::GetCountMips(w, h);
	}

	m_images = BearCore::bear_alloc<uint8>(GetSizeInMemory());
}

void BearGraphics::BearImage::Append(bsize x, bsize y, const BearImage & img, bsize x_src, bsize y_src, bsize w_src, bsize h_src, bsize dst_depth, bsize src_depth)
{
	if (Empty() || img.Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(img.m_px), TEXT("BlockCompressor нередактируетьс€"));
	BEAR_FATALERROR(m_w >= x + w_src && m_h >= y + h_src, TEXT("Ќезвохможно склеить текстуру из-за маленького размера полотна."));
	BEAR_FATALERROR(img.m_w >= x_src + w_src && img.m_h >= y_src + h_src, TEXT("Ќезвохможно склеить текстуру из-за маленького размера полотна."));
	BEAR_FATALERROR(m_depth > dst_depth, TEXT("«начение глубены [%llu] вышло за пределы [%llu] масива"), dst_depth, m_depth);
	BEAR_FATALERROR(m_depth > src_depth, TEXT("«начение глубены [%llu] вышло за пределы [%llu] масива"), src_depth, m_depth);
	bsize dst_size = BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*dst_depth;
	bsize src_size = BearRHI::BearRHITextureUtils::GetSizeInMemory(img.m_w, img.m_h, img.m_mips, img.m_px)*src_depth;
	uint8*dst_data = m_images + dst_size;
	uint8*src_data = img.m_images + src_size;
	BearRHI::BearRHITextureUtils::Append(dst_data, m_w, m_h, x, y, src_data, img.m_w, img.m_h, BearCore::BearVector4<bsize>(x_src, y_src, w_src, h_src), m_px, img.m_px);
}

void BearGraphics::BearImage::Append(bsize x, bsize y, const BearImage & img, bsize dst_depth, bsize src_depth)
{
	if (Empty() || img.Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	Append(x, y, img, 0, 0, img.m_w, img.m_h, dst_depth, src_depth);
}

void BearGraphics::BearImage::Scale(bsize w, bsize h)
{
	if (Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	BearImage img;
	img.Create(w, h, m_mips > 1, m_depth, m_px);
	bsize src_size = BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px);
	bsize dst_size = BearRHI::BearRHITextureUtils::GetSizeInMemory(img.m_w, img.m_h, img.m_mips, img.m_px);
	for (bsize i = 0; i < m_depth; i++)
	{

		uint8*dst_data = img.m_images + dst_size * i;
		uint8*src_data = m_images + src_size * i;
		BearRHI::BearRHITexture2D::Scale(dst_data, img.m_w, img.m_h, src_data, m_w, m_h, m_px);
	}
	Swap(img);
}

void BearGraphics::BearImage::ScaleCanvas(bsize w, bsize h)
{
	if (Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	BearImage img;

	img.Create(w, h, m_mips > 1, m_depth, m_px);
	for (bsize i = 0; i < m_depth; i++)
	{
		img.Append(0, 0, *this, 0, 0, BearCore::bear_min(m_w, w), BearCore::bear_min(m_h, h), i, i);
	}
	Swap(img);
}


void BearGraphics::BearImage::GenerateMipmap(bsize depth)
{
	if (Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	if (m_mips == 1)
	{
		GenerateMipmap();
	}
	else
	{
	
		for (bsize i = 0 ; i < m_mips-1; i++)
		{
			uint8*cur_mip = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, m_mips, depth, i, m_px);
			uint8*new_mip= BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, m_mips, depth, i+1, m_px);
			BearRHI::BearRHITextureUtils::GenerateMip(new_mip, cur_mip, BearRHI::BearRHITextureUtils::GetMip(m_w, i), BearRHI::BearRHITextureUtils::GetMip(m_h, i), m_px);
		}
		
	}
}

void BearGraphics::BearImage::GenerateMipmap()
{
	if (Empty())
		return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	m_mips = BearRHI::BearRHITexture2D::GetCountMips(m_w, m_h);
	m_images = BearCore::bear_realloc(m_images, BearRHI::BearRHITexture2D::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth);
	bsize size = BearRHI::BearRHITexture2D::GetSizeInMemory(m_w, m_h, 1, m_px);
	for (bsize i = m_depth; i > 1; i--)
	{
		uint8*images = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, 1, i-1, 0, m_px);
		uint8*images_new = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, m_mips, i - 1, 0, m_px);
		BearCore::bear_move(images, images_new- images, size);
	}
	for (bsize i = 0; m_depth>i; i++)
	{
		GenerateMipmap(i);
	}
}


void BearGraphics::BearImage::ClearMipLevels()
{
	if (Empty() || m_mips == 1)return;
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	bsize size = BearRHI::BearRHITexture2D::GetSizeInMemory(m_w, m_h, 1, m_px);
	for (bsize i = m_depth; i > 1; i--)
	{
		uint8*images_new = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, 1, i - 1, 0, m_px);
		uint8*images = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, m_mips, i - 1, 0, m_px);
		BearCore::bear_move(images, images_new - images, size);
	}
	m_mips = 1;
	m_images = BearCore::bear_realloc(m_images, BearRHI::BearRHITexture2D::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth);
}

void BearGraphics::BearImage::NormalizedSizeNotScale()
{
	bsize size = BearCore::bear_max(BearCore::bear_recommended_size(m_w), BearCore::bear_recommended_size(m_h));
	ScaleCanvas(size, size);
}

void BearGraphics::BearImage::NormalizedSize()
{
	bsize size = BearCore::bear_max(BearCore::bear_recommended_size(m_w), BearCore::bear_recommended_size(m_h));
	Scale(size, size);
}

BearCore::BearColor BearGraphics::BearImage::GetPixel(bsize x, bsize y, bsize d) const
{
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируетьс€"));
	if (Empty())
		return BearCore::BearColor();

	//	bsize count_comp = BearRHI::BearRHITextureUtils::GetCountComp(m_px);;
	BearCore::BearColor color;
	/*if(BearRHI::BearRHITextureUtils::is)
	 BearRHI::BearRHITextureUtils::GetPixelFloat(x, y, m_w, count_comp, 0, data);*/
	return BearCore::BearColor();

}

void BearGraphics::BearImage::SetPixel(const BearCore::BearColor & color, bsize x, bsize y, bsize d)
{
}



void BearGraphics::BearImage::Clear()
{
	if (m_images)BearCore::bear_free(m_images);
	m_h = 0;
	m_w = 0;
	m_mips = 0;
	m_depth = 0;
	m_px = TPF_R8;
}

BearGraphics::BearImage::~BearImage()
{
	Clear();
}

bool BearGraphics::BearImage::Empty() const
{
	return false;
}

BearGraphics::BearImage::BearImage(const BearImage & img) :m_px(TPF_R8), m_images(0), m_w(0), m_h(0), m_depth(0), m_mips(0)
{
	Copy(img);
}

void BearGraphics::BearImage::Copy(const BearImage & img)
{
	if (Empty())return;
	Clear();
	m_h = img.m_h;
	m_w = img.m_w;
	m_mips = img.m_mips;
	m_depth = img.m_depth;
	m_px = img.m_px;
	m_images = BearCore::bear_alloc<uint8>(GetSizeInMemory());
	BearCore::bear_copy(m_images, img.m_images, GetSizeInMemory());
}

void BearGraphics::BearImage::Swap(BearImage & img)
{
	BearCore::bear_swap(m_h , img.m_h);
	BearCore::bear_swap(m_w , img.m_w);
	BearCore::bear_swap(m_mips , img.m_mips);
	BearCore::bear_swap(m_depth , img.m_depth);
	BearCore::bear_swap(m_px , img.m_px);
	BearCore::bear_swap(m_images, img.m_images);
}

BearGraphics::BearImage & BearGraphics::BearImage::operator=(const BearImage & img)
{
	Copy(img);
	return*this;
}

void BearGraphics::BearImage::Convert(BearTexturePixelFormat format)
{
	if (Empty())return;
	BearImage img(m_w, m_h, m_mips >1, m_depth, format);
	uint8*src= (uint8*)**this;
	uint8*dst = (uint8*)*img;
	for (bsize i = 0; i < m_depth; i++)
	{
		
		for (bsize a = 0; a < m_mips; a++)
		{
			bsize w = BearRHI::BearRHITextureUtils::GetMip(m_w,a);
			bsize h = BearRHI::BearRHITextureUtils::GetMip(m_h, a);
			BearRHI::BearRHITextureUtils::Convert(format, m_px, dst, src, w, h);
			src +=BearRHI::BearRHITextureUtils::GetSizeDepth(w, h,m_px);
			dst += BearRHI::BearRHITextureUtils::GetSizeDepth(w, h, format);
		}
	}
	Swap(img);
}

BearGraphics::BearTexturePixelFormat BearGraphics::BearImage::GetFormat() const
{
	return m_px;
}

bsize BearGraphics::BearImage::GetDepth() const
{
	return m_depth;
}

bsize BearGraphics::BearImage::GetMips()const
{
	return m_mips;
}

void * BearGraphics::BearImage::operator*()
{
	return m_images;
}

const void * BearGraphics::BearImage::operator*() const
{
	return m_images;
}

bsize BearGraphics::BearImage::GetSizeInMemory() const
{
	return BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth;
}

BearCore::BearVector2<bsize> BearGraphics::BearImage::GetSize() const
{
	return BearCore::BearVector2<bsize>(m_w,m_h);
}


void BearGraphics::BearImage::Resize(bsize w, bsize h,bsize depth,BearTexturePixelFormat px)
{
	if (m_w != w || m_h != h || m_px != px)
	{
		Create(w, h, m_mips > 1, depth + 1, px);
	}
	else
	{
		if(m_depth< depth + 1)
			m_images = BearCore::bear_realloc(m_images, BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*(depth + 1));
		m_depth = depth + 1;
	}
}

