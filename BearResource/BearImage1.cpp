#include "BearGraphics.hpp"
#include "BearRHI/BearTextureUtils.h"

BearImage::BearImage() :m_px(TPF_R8), m_w(0), m_h(0), m_mips(0), m_depth(0), m_images(0)
{
}

BearImage::BearImage(bsize w, bsize h, bsize mip, bsize depth, BearTexturePixelFormat px) : m_px(TPF_R8), m_w(0), m_h(0), m_mips(0), m_depth(0), m_images(0)
{
	Create(w, h, mip, depth, px);
}

void BearImage::Fill(const BearColor & color)
{
	if (Empty())return;
	bsize size = BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px);
	for (bsize i = 0; i < m_depth; i++)
	{
		BearTextureUtils::Fill(m_images + (size*i), m_w, m_h, m_mips, color, m_px);
	}
}

void BearImage::Create(bsize w, bsize h, bsize mip, bsize depth, BearTexturePixelFormat px)
{
	Clear();

	m_depth = depth;
	if (BearTextureUtils::isCompressor(px))
	{
		BEAR_CHECK(m_w%4==0&&m_h%4==0);
	}
	m_w = w;
	m_h = h;
	m_px = px;
	BEAR_CHECK(m_depth);
	if(mip)
		m_mips = mip;
	else
		m_mips = 1;
	m_images = bear_alloc<uint8>(GetSizeInMemory());
}

void BearImage::Append(bsize x, bsize y, const BearImage & img, bsize x_src, bsize y_src, bsize w_src, bsize h_src, bsize dst_depth, bsize src_depth)
{
	if (Empty() || img.Empty())
		return;
	BEAR_ASSERT(m_w >= x + w_src && m_h >= y + h_src);
	BEAR_ASSERT(img.m_w >= x_src + w_src && img.m_h >= y_src + h_src);
	BEAR_ASSERT(m_depth > dst_depth);
	BEAR_ASSERT(m_depth > src_depth);
	bsize dst_size = BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*dst_depth;
	bsize src_size = BearTextureUtils::GetSizeInMemory(img.m_w, img.m_h, img.m_mips, img.m_px)*src_depth;
	uint8*dst_data = m_images + dst_size;
	uint8*src_data = img.m_images + src_size;
	BearTextureUtils::Append(dst_data, m_w, m_h, x, y, src_data, img.m_w, img.m_h, BearVector4<bsize>(x_src, y_src, w_src, h_src), m_px, img.m_px);
}

void BearImage::Append(bsize x, bsize y, const BearImage & img, bsize dst_depth, bsize src_depth)
{
	if (Empty() || img.Empty())
		return;
	Append(x, y, img, 0, 0, img.m_w, img.m_h, dst_depth, src_depth);
}

void BearImage::Scale(bsize w, bsize h)
{
	if (Empty())
		return;
	BearImage img;
	bsize mips = m_mips;
	ClearMipLevels();
	img.Create(w, h, 1 , m_depth, m_px);
	bsize src_size = BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px);
	bsize dst_size = BearTextureUtils::GetSizeInMemory(img.m_w, img.m_h, img.m_mips, img.m_px);
	for (bsize i = 0; i < m_depth; i++)
	{

		uint8*dst_data = img.m_images + dst_size * i;
		uint8*src_data = m_images + src_size * i;
		BearTextureUtils::Scale(dst_data, img.m_w, img.m_h, src_data, m_w, m_h, m_px);
	}

	Swap(img);
	if (mips > 1) GenerateMipmap();
}

void BearImage::ScaleCanvas(bsize w, bsize h)
{
	if (Empty())
		return;
	bsize mips = m_mips;
	BearImage img;
	ClearMipLevels();
	img.Create(w, h, m_mips, m_depth, m_px);
	img.Fill(BearColor::Black);
	for (bsize i = 0; i < m_depth; i++)
	{
		img.Append(0, 0, *this, 0, 0, BearMath::min(m_w, w), BearMath::min(m_h, h), i, i);
	}
	Swap(img);
	if (mips > 1) GenerateMipmap();

}


void BearImage::GenerateMipmap(bsize depth)
{
	if (Empty())
		return;
	if (m_mips == 1)
	{
		GenerateMipmap();
	}
	else
	{
	
		for (bsize i = 0 ; i < m_mips-1; i++)
		{
			uint8*cur_mip = BearTextureUtils::GetImage(m_images, m_w, m_h, m_mips, depth, i, m_px);
			uint8*new_mip= BearTextureUtils::GetImage(m_images, m_w, m_h, m_mips, depth, i+1, m_px);
			BearTextureUtils::GenerateMip(new_mip, cur_mip, BearTextureUtils::GetMip(m_w, i), BearTextureUtils::GetMip(m_h, i), m_px);
		}
		
	}
}

void BearImage::GenerateMipmap()
{
	if (Empty())
		return;
	m_mips = BearTextureUtils::GetCountMips(m_w, m_h);
	m_images = bear_realloc(m_images, BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth);
	bsize size = BearTextureUtils::GetSizeInMemory(m_w, m_h, 1, m_px);
	for (bsize i = m_depth; i > 1; i--)
	{
		uint8*images = BearTextureUtils::GetImage(m_images, m_w, m_h, 1, i-1, 0, m_px);
		uint8*images_new = BearTextureUtils::GetImage(m_images, m_w, m_h, m_mips, i - 1, 0, m_px);
		bear_move(images, images_new- images, size);
	}
	for (bsize i = 0; m_depth>i; i++)
	{
		GenerateMipmap(i);
	}
}


void BearImage::ClearMipLevels()
{
	if (Empty() || m_mips == 1)return;
	bsize size = BearTextureUtils::GetSizeInMemory(m_w, m_h, 1, m_px);
	for (bsize i = m_depth; i > 1; i--)
	{
		uint8*images_new = BearTextureUtils::GetImage(m_images, m_w, m_h, 1, i - 1, 0, m_px);
		uint8*images = BearTextureUtils::GetImage(m_images, m_w, m_h, m_mips, i - 1, 0, m_px);
		bear_move(images, images_new - images, size);
	}
	m_mips = 1;
	m_images = bear_realloc(m_images, BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth);
}

void BearImage::NormalizedSizeNotScale()
{
	bsize size = BearMath::max(bear_recommended_size(m_w), bear_recommended_size(m_h));
	ScaleCanvas(size, size);
}

void BearImage::NormalizedSize()
{
	bsize size = BearMath::max(bear_recommended_size(m_w), bear_recommended_size(m_h));
	Scale(size, size);
}

BearColor BearImage::GetPixel(bsize x, bsize y, bsize d) const
{
	if (Empty())
		return BearColor();
	
	BearColor color;
	BearTextureUtils::GetPixel(color,m_images,x,y,d,m_w,m_h,m_mips,m_px);
	return color;

}

void BearImage::SetPixel(const BearColor & color, bsize x, bsize y, bsize d)
{
	if (Empty())
		return;
	BearTextureUtils::SetPixel(color, m_images, x, y, d, m_w, m_h, m_mips, m_px);
}



void BearImage::Clear()
{
	if (m_images)
		bear_free(m_images); 
	m_images = 0;
	m_h = 0;
	m_w = 0;
	m_mips = 0;
	m_depth = 0;
	m_px = TPF_R8;
}

BearImage::~BearImage()
{
	Clear();
}

bool BearImage::Empty() const
{
	return m_depth==0||m_mips==0||m_w==0||m_h==0;
}

BearImage::BearImage(const BearImage & img) :m_px(TPF_R8), m_w(0), m_h(0), m_mips(0), m_depth(0), m_images(0)
{
	Copy(img);
}

void BearImage::Copy(const BearImage & img)
{
	if (Empty())return;
	Clear();
	m_h = img.m_h;
	m_w = img.m_w;
	m_mips = img.m_mips;
	m_depth = img.m_depth;
	m_px = img.m_px;
	m_images = bear_alloc<uint8>(GetSizeInMemory());
	bear_copy(m_images, img.m_images, GetSizeInMemory());
}

void BearImage::Swap(BearImage & img)
{
	bear_swap(m_h , img.m_h);
	bear_swap(m_w , img.m_w);
	bear_swap(m_mips , img.m_mips);
	bear_swap(m_depth , img.m_depth);
	bear_swap(m_px , img.m_px);
	bear_swap(m_images, img.m_images);
}

BearImage & BearImage::operator=(const BearImage & img)
{
	Copy(img);
	return*this;
}

void BearImage::Convert(BearTexturePixelFormat format)
{
	if (Empty())return;
	BearImage img(m_w, m_h, m_mips , m_depth, format);
	uint8*src= (uint8*)**this;
	uint8*dst = (uint8*)*img;
	for (bsize i = 0; i < m_depth; i++)
	{
		
		for (bsize a = 0; a < m_mips; a++)
		{
			bsize w = BearTextureUtils::GetMip(m_w,a);
			bsize h = BearTextureUtils::GetMip(m_h, a);
			BearTextureUtils::Convert(format, m_px, dst, src, w, h);
			src +=BearTextureUtils::GetSizeDepth(w, h,m_px);
			dst += BearTextureUtils::GetSizeDepth(w, h, format);
		}
	}
	Swap(img);
}

BearTexturePixelFormat BearImage::GetFormat() const
{
	return m_px;
}

bsize BearImage::GetDepth() const
{
	return m_depth;
}

bsize BearImage::GetMips()const
{
	return m_mips;
}

void * BearImage::operator*()
{
	return m_images;
}

const void * BearImage::operator*() const
{
	return m_images;
}

bsize BearImage::GetSizeInMemory() const
{
	return BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth;
}

BearVector2<bsize> BearImage::GetSize() const
{
	return BearVector2<bsize>(m_w,m_h);
}


void BearImage::Resize(bsize w, bsize h,bsize depth,BearTexturePixelFormat px)
{
	if (m_w != w || m_h != h || m_px != px)
	{
		Create(w, h, m_mips , depth + 1, px);
	}
	else
	{
		if(m_depth< depth + 1)
			m_images = bear_realloc(m_images, BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px)*(depth + 1));
		m_depth = depth + 1;
	}
}

