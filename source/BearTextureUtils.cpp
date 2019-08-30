#include "BearGraphics.hpp"
#include "BearTextureUtils.h"
#include "ispc_texcomp.h"
#include "nvimage\ColorBlock.h"
#include "nvimage\BlockDXT.h"
#include "nvtt\CompressorDX9.h"
#include "nvtt\QuickCompressDXT.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
bsize BearGraphics::BearTextureUtils::GetSizeWidth(bsize w, BearGraphics::BearTexturePixelFormat format)
{
	if (isCompressor(format))
	{
		return GetSizeBlock(format)*GetCountBlock(w);
	}
	else
	{
		return GetSizePixel(format)*w;
	}
}

bsize BearGraphics::BearTextureUtils::GetSizeDepth(bsize w, bsize h, BearGraphics::BearTexturePixelFormat format)
{
	if (isCompressor(format))
	{
		return GetSizeBlock(format)*GetCountBlock(w)*GetCountBlock(h);
	}
	else
	{
		return GetSizePixel(format)*w*h;
	}
}

bsize BearGraphics::BearTextureUtils::GetSizePixel(BearGraphics::BearTexturePixelFormat format)
{
	switch (format)
	{
	case BearGraphics::TPF_R8:
		return 1;
		break;
	case BearGraphics::TPF_R8G8:
		return 2;
		break;
	case BearGraphics::TPF_R8G8B8:
		return 3;
		break;
	case BearGraphics::TPF_R8G8B8A8:
		return 4;
		break;
	case BearGraphics::TPF_R32F:
		return 4;
		break;
	case BearGraphics::TPF_R32G32F:
		return 8;
		break;
	case BearGraphics::TPF_R32G32B32F:
		return 12;
		break;
	case BearGraphics::TPF_R32G32B32A32F:
		return 16;
		break;
	default:
		BEAR_ASSERT(false);
		break;

	}
	return 0;
}

void BearGraphics::BearTextureUtils::Append(uint8*dst, bsize w_dst, bsize h_dst, bsize x_dst, bsize y_dst, uint8*src, bsize w_src, bsize h_src, BearCore::BearVector4<bsize> squard_src, BearGraphics::BearTexturePixelFormat dst_format, BearGraphics::BearTexturePixelFormat src_format)
{
	BEAR_ASSERT(!isCompressor(dst_format) || !isCompressor(src_format));
	BEAR_ASSERT(w_dst >= squard_src.x1+x_dst);
	BEAR_ASSERT(h_dst >=  squard_src.y1+ y_dst);
	BEAR_ASSERT(w_src >= squard_src.x	+ squard_src.x1);
	BEAR_ASSERT(h_src >= squard_src.y + squard_src.y1);
	uint8 src_comp = GetCountComp(src_format);
	uint8 dst_comp = GetCountComp(dst_format);
	if (isFloatPixel(dst_format) && isFloatPixel(src_format))
	{
		for (bsize iy = 0; iy<squard_src.y1; iy++)
			for (bsize ix = 0; ix < squard_src.x1; ix++)
			{
				FloatPixelToFloat(GetPixelFloat(ix + x_dst, iy + y_dst, w_dst, dst_comp, 0, dst), GetPixelFloat(ix+squard_src.x , iy + squard_src.y, w_src, src_comp, 0, src), dst_comp, src_comp);
			}
	}
	else if (isFloatPixel(src_format) )
	{
		for (bsize iy = 0; iy<squard_src.y1; iy++)
			for (bsize ix = 0; ix < squard_src.x1; ix++)
			{
				Uint8PixelToFloat(GetPixelFloat(ix + x_dst, iy + y_dst, w_dst, dst_comp, 0, dst), GetPixelUint8(ix + squard_src.x, iy + squard_src.y, w_src, src_comp, 0, src), dst_comp, src_comp);
			}
	}
	else if (isFloatPixel(dst_format))
	{
		for (bsize iy = 0; iy<squard_src.y1; iy++)
			for (bsize ix = 0; ix < squard_src.x1; ix++)
			{
				FloatPixelToUint8(GetPixelUint8(ix + x_dst, iy + y_dst, w_dst, dst_comp, 0, dst), GetPixelFloat(ix + squard_src.x, iy + squard_src.y, w_src, src_comp, 0, src), dst_comp, src_comp);
			}
	}
	else
	{
		for (bsize iy = 0; iy<squard_src.y1; iy++)
			for (bsize ix = 0; ix < squard_src.x1; ix++)
			{
				Uint8PixelToUint8(GetPixelUint8(ix + x_dst, iy + y_dst, w_dst, dst_comp, 0, dst), GetPixelUint8(ix + squard_src.x, iy + squard_src.y, w_src, src_comp, 0, src), dst_comp, src_comp);
			}
	}
}


bsize BearGraphics::BearTextureUtils::GetCountMips(bsize w, bsize h)
{
	bsize max_size = BearCore::bear_max(w, h);
	return log2(static_cast<double>(max_size))+1;
}

bsize BearGraphics::BearTextureUtils::GetMip(bsize w, bsize level)
{
	bsize mip = static_cast<bsize>((w ) / pow(2, static_cast<double>(level)));
	return BearCore::bear_max(mip, bsize(1));
}

uint8 * BearGraphics::BearTextureUtils::GetPixelUint8(bsize x, bsize y, bsize w, bsize comps, bsize comp_id, uint8 * data)
{
	return  &data[(x + (y * w))*comps+comp_id];
}

float * BearGraphics::BearTextureUtils::GetPixelFloat(bsize x, bsize y, bsize w, bsize comps, bsize comp_id, uint8 * data)
{
	return (float*)&data[y*w*comps*4+x*4*comps+comp_id*4];
}

bool BearGraphics::BearTextureUtils::isFloatPixel(BearGraphics::BearTexturePixelFormat format)
{
	switch (format)
	{
	case BearGraphics::TPF_R8:
	case BearGraphics::TPF_R8G8:
	case BearGraphics::TPF_R8G8B8:
	case BearGraphics::TPF_R8G8B8A8:
		return false;;
		break;
	case BearGraphics::TPF_R32F:
	case BearGraphics::TPF_R32G32F:
	case BearGraphics::TPF_R32G32B32F:
	case BearGraphics::TPF_R32G32B32A32F:
		return true;
	case BearGraphics::TPF_DXT_1:
	case BearGraphics::TPF_DXT_1_alpha:
	case BearGraphics::TPF_DXT_3:
	case BearGraphics::TPF_DXT_5:
	case BearGraphics::TPF_BC4:
	case BearGraphics::TPF_BC5:
	case BearGraphics::TPF_BC6:
	case BearGraphics::TPF_BC7:
		return false;

		break;
	default:
		BEAR_ASSERT(false);
	}
	return false;
}

bool BearGraphics::BearTextureUtils::isCompressor(BearGraphics::BearTexturePixelFormat format)
{
	switch (format)
	{
	case BearGraphics::TPF_R8:
	case BearGraphics::TPF_R8G8:
	case BearGraphics::TPF_R8G8B8:
	case BearGraphics::TPF_R8G8B8A8:
	case BearGraphics::TPF_R32F:
	case BearGraphics::TPF_R32G32F:
	case BearGraphics::TPF_R32G32B32F:
	case BearGraphics::TPF_R32G32B32A32F:
		return false;
		break;
	case BearGraphics::TPF_DXT_1:
	case BearGraphics::TPF_DXT_1_alpha:
	case BearGraphics::TPF_DXT_3:
	case BearGraphics::TPF_DXT_5:
	case BearGraphics::TPF_BC4:
	case BearGraphics::TPF_BC5:
	case BearGraphics::TPF_BC6:
	case BearGraphics::TPF_BC7:
		return true;
	default:
		break;
	}
	return false;
}

void BearGraphics::BearTextureUtils::Fill(uint8 * data, bsize w, bsize h, bsize mip, const BearCore::BearColor & color, BearGraphics::BearTexturePixelFormat format)
{
	BEAR_ASSERT(!isCompressor(format));
	if (isFloatPixel(format))
	{
		bsize pixel_size = GetSizePixel(format);
		for (bsize i = 0; i < mip; i++) {
			bsize mip_w = GetMip(w, i);
			bsize mip_h = GetMip(h, i);
			FillFloat(data, mip_w, mip_h, color, format);
			data += pixel_size * mip_w*mip_h;
		}
	}
	else
	{
		bsize pixel_size = GetSizePixel(format);
		for (bsize i = 0; i < mip; i++) {
			bsize mip_w = GetMip(w, i);
			bsize mip_h = GetMip(h, i);
			FillUint8(data, mip_w, mip_h, color, format);
			data += pixel_size * mip_w*mip_h;
		}
	}
}

bsize BearGraphics::BearTextureUtils::GetSizeInMemory(bsize w, bsize h, bsize mips, BearGraphics::BearTexturePixelFormat format)
{
	bsize result = 0;
	if (!isCompressor(format))
	{
		bsize pixel_size = GetSizePixel(format);
		//result += w * h * pixel_size;
		for (bsize i = 0; i < mips; i++)
		{
			bsize mip_w = GetMip(w, i);
			bsize mip_h = GetMip(h, i);
			result += mip_w * mip_h * pixel_size;
		}
	}
	else
	{
		bsize size_block = GetSizeBlock(format);
	//	result += GetCountBlock(w)*GetCountBlock(h)*size_block;
		for (bsize i = 0; i < mips; i++)
		{
			bsize mip_w = GetMip(w, i);
			bsize mip_h = GetMip(h, i);
			result += GetCountBlock(mip_w)*GetCountBlock(mip_h)* size_block;
		}
	}
	return result;
}

void BearGraphics::BearTextureUtils::Convert(BearGraphics::BearTexturePixelFormat dst_format, BearGraphics::BearTexturePixelFormat src_format, uint8 * dst, uint8 * src, bsize w, bsize h)
{
	if (src_format == dst_format)return;
	if (isFloatPixel(dst_format)&& isCompressor(src_format))
	{
		CompressorToFloat(dst, src, w, h, GetCountComp(dst_format), src_format);
	}
	else if (isFloatPixel(dst_format) && isFloatPixel(src_format))
	{
		FloatToFloat(dst, src, w, h, GetCountComp(dst_format), GetCountComp(src_format));
	}
	else if (isFloatPixel(dst_format))
	{
		Uint8ToFloat(dst, src, w, h, GetCountComp(dst_format), GetCountComp(src_format));
	}
	else if (isCompressor(dst_format) && isCompressor(src_format))
	{
		CompressorToCompressor(dst, src, w, h, dst_format, src_format);
	}
	else if (isCompressor(dst_format) && isFloatPixel(src_format))
	{
		FloatToCompressor(dst, src, w, h, dst_format, GetCountComp(src_format));
	}
	else  if (isCompressor(dst_format))
	{
		Uint8ToCompressor(dst, src, w, h, dst_format, GetCountComp(src_format));
	}
	else if (isCompressor(src_format))
	{
		CompressorToUint8(dst, src, w, h, GetCountComp(dst_format), src_format);
	}
	else if (isFloatPixel(src_format))
	{
		FloatToUint8(dst, src, w, h, GetCountComp(dst_format), GetCountComp(src_format));
	}
	else
	{
		Uint8ToUint8(dst, src, w, h, GetCountComp(dst_format), GetCountComp(src_format));
	}
}

bsize BearGraphics::BearTextureUtils::GetCountBlock(bsize w)
{
	return (w + 3) / 4;
}

bsize BearGraphics::BearTextureUtils::GetSizeBlock(BearGraphics::BearTexturePixelFormat format)
{
	switch (format)
	{
	case BearGraphics::TPF_DXT_1:
		return 8;
	case BearGraphics::TPF_DXT_1_alpha:
		return 8;
	case BearGraphics::TPF_DXT_3:
		return 16;
	case BearGraphics::TPF_DXT_5:
		return 16;
	case BearGraphics::TPF_BC4:
		return 8;
		break;
	case BearGraphics::TPF_BC5:
		return 16;
		break;
	case BearGraphics::TPF_BC6:
		return 16;
		break;
	case BearGraphics::TPF_BC7:
		return 16;
		break;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}	

uint8 BearGraphics::BearTextureUtils::GetCountComp(BearGraphics::BearTexturePixelFormat format)
{
	switch (format)
	{
	case BearGraphics::TPF_R8:
		return 1;
		break;
	case BearGraphics::TPF_R8G8:
		return 2;
		break;
	case BearGraphics::TPF_R8G8B8:
		return 3;
		break;
	case BearGraphics::TPF_R8G8B8A8:
		return 4;
		break;
	case BearGraphics::TPF_R32F:
		return 1;
		break;
	case BearGraphics::TPF_R32G32F:
		return 2;
		break;
	case BearGraphics::TPF_R32G32B32F:
		return 3;
		break;
	case BearGraphics::TPF_R32G32B32A32F:
		return 4;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearGraphics::BearTextureUtils::GenerateMip(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, BearGraphics::BearTexturePixelFormat format)
{
	if (isFloatPixel(format))
	{
		GenerateMipFloat(dst, src, w_src, h_src,GetCountComp(format));
	}
	else
	{
		BEAR_ASSERT(!isCompressor(format));
		GenerateMipUint8(dst, src, w_src, h_src, GetCountComp(format));
	}
}

void BearGraphics::BearTextureUtils::Scale(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, BearGraphics::BearTexturePixelFormat format)
{
	if (isFloatPixel(format))
	{
		ScaleFloat(dst, w_dst, h_dst, src, w_src, h_src, GetCountComp(format));
	}
	else
	{
		BEAR_ASSERT(!isCompressor(format));
		ScaleUint8(dst, w_dst, h_dst, src, w_src, h_src, GetCountComp(format));
	}
}

uint8 * BearGraphics::BearTextureUtils::GetImage(uint8 * data, bsize w, bsize h, bsize mips, bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format)
{
	return data + BearGraphics::BearTextureUtils::GetSizeInMemory(w, h, mips, format)*depth + BearGraphics::BearTextureUtils::GetSizeInMemory(w, h, mip, format);
}

void BearGraphics::BearTextureUtils::ScaleFloat(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, uint8 comp)
{
	stbir_resize_float(reinterpret_cast<float*>(src), w_src, h_src, 0, reinterpret_cast<float*>(dst), w_dst, h_dst, 0, comp);
}

void BearGraphics::BearTextureUtils::ScaleUint8(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, uint8 comp)
{

	stbir_resize_uint8(src, w_src, h_src, 0, dst, w_dst, h_dst,0, comp);

}



void BearGraphics::BearTextureUtils::GenerateMipFloat(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, bsize comps)
{
	ScaleFloat(dst, w_src / 2, h_src / 2, src, w_src, h_src, comps);
}

void BearGraphics::BearTextureUtils::GenerateMipUint8(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, bsize comps)
{
	ScaleUint8(dst, w_src / 2, h_src / 2, src, w_src, h_src, comps);
}

void BearGraphics::BearTextureUtils::FloatPixelToUint8(uint8 * dst, float * src, uint8 comp_dst, uint8 comp_src)
{
	for (uint8 i = 0; i < comp_dst; i++)
	{
		if (i < comp_src)
		{
			*dst = static_cast<uint8>(*src*255.f);
			src++;
		}
		else if(i==3)
		{
			*dst = 255;
		}
		else
		{
			*dst = 0;
		}
		dst++;
	}
}

void BearGraphics::BearTextureUtils::FloatPixelToFloat(float * dst, float * src, uint8 comp_dst, uint8 comp_src)
{
	for (uint8 i = 0; i < comp_dst; i++)
	{
		if (i < comp_src)
		{
			*dst = *src;
			src++;
		}
		else if (i == 3)
		{
			*dst = 1.f;
		}
		else
		{
			*dst = 0.f;
		}
		dst++;
	}
}

void BearGraphics::BearTextureUtils::Uint8PixelToFloat(float * dst, uint8 * src, uint8 comp_dst, uint8 comp_src)
{
	for (uint8 i = 0; i < comp_dst; i++)
	{
		if (i < comp_src)
		{
			*dst = static_cast<float>(*src/255.f);
			src++;
		}
		else if (i == 3)
		{
			*dst = 1.f;
		}
		else
		{
			*dst = 0.f;
		}
		dst++;
	}
}
void BearGraphics::BearTextureUtils::Uint8PixelToUint8(uint8 * dst, uint8 * src, uint8 comp_dst, uint8 comp_src)
{
	for (uint8 i = 0; i < comp_dst; i++)
	{
		if (i < comp_src)
		{
			*dst = *src;
			src++;
		}
		else if (i == 3)
		{
			*dst = 255;
		}
		else
		{
			*dst = 255;
		}
		dst++;
	}
}
uint16 floatToHalf(float f)
{
	uint32 fuint32 = *((uint32*)&f);
	uint16 a = ((fuint32 >> 16) & 0b1000000000000000) | ((((fuint32 & 0b1111111100000000000000000000000) - 0b111000000000000000000000000000) >> 13) & 0b111110000000000) | ((fuint32 >> 13) & 0b1111111111);
	if (f == 0)
		return 0;
	return a;
}

void BearGraphics::BearTextureUtils::FloatPixelToHalf4(uint16 * dst, float * src, uint8 comp_src)
{
	for (uint8 i = 0; i < 4; i++)
	{
		if (i < comp_src)
		{
			if(i==3)
				*dst = floatToHalf(1.f);
			else
				*dst = floatToHalf(*src);
			src++;
		}
		else if (i == 3)
		{
			*dst = floatToHalf(1.f);
		}
		else
		{
			*dst = floatToHalf(0.f);
		}
		dst++;
	}
}

void BearGraphics::BearTextureUtils::Uint8PixelToHalf4(uint16 * dst, uint8 * src, uint8 comp_src)
{
	for (uint8 i = 0; i < 4; i++)
	{
		if (i < comp_src)
		{
			if (i == 3)
				*dst = floatToHalf(1.f);
			else
			*dst = floatToHalf(static_cast<float>(*src / 255.f));
			src++;
		}
		else if (i == 3)
		{
			*dst = floatToHalf(1.f);
		}
		else
		{
			*dst = floatToHalf(0.f);
		}
		dst++;
	}
}

void BearGraphics::BearTextureUtils::SwapRB(uint32 & color)
{
		uint32 r = color & 0x000000FF;

		uint32 b = color & 0x00FF0000;
		uint32 g = color & 0x0000FF00;
		uint32 a = color & 0xFF000000;
		color = (b >> 16) | g | (r << 16) | a;
}

void BearGraphics::BearTextureUtils::FillUint8(uint8 * data, bsize x, bsize y, const BearCore::BearColor & color, BearGraphics::BearTexturePixelFormat format)
{
	auto vector_color = color.GetUint8();
	bsize size_pixel = GetSizePixel(format);
	for (bsize i = 0; i < x*y; i++)
	{
		BearCore::bear_copy(data + (size_pixel*i), vector_color.array, size_pixel);
	}
}

void BearGraphics::BearTextureUtils::FillFloat(uint8 * data, bsize x, bsize y, const BearCore::BearColor & color, BearGraphics::BearTexturePixelFormat format)
{
	auto vector_color = color.GetFloat();
	bsize size_pixel = GetSizePixel(format);
	for (bsize i = 0; i < x*y; i++)
	{
		BearCore::bear_copy(data + (size_pixel*i), vector_color.array, size_pixel);
	}
}

void BearGraphics::BearTextureUtils::Uint8ToHalf4(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToHalf4((uint16*)dst, src, comp_src);
		dst += 4*2;
		src += comp_src;
	}
}

void BearGraphics::BearTextureUtils::Uint8ToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToFloat((float*)dst, src, comp_dst, comp_src);
		dst += comp_dst * 4;
		src += comp_src;
	}
}

void BearGraphics::BearTextureUtils::Uint8ToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToUint8(dst, src, comp_dst, comp_src);
		dst += comp_dst ;
		src += comp_src;
	}
}

void BearGraphics::BearTextureUtils::Uint8ToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor, uint8 comp_src)
{
	uint8*in=(uint8*)StartCompressor(compressor,w,h);
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
		Uint8ToFloat(in, src, w, h, 3, comp_src);
		break;
	case BearGraphics::TPF_DXT_1_alpha:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_DXT_3:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_DXT_5:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_BC4:
		Uint8ToUint8(in, src, w, h, 1, comp_src);
		break;
	case BearGraphics::TPF_BC5:
		Uint8ToUint8(in, src, w, h, 2, comp_src);
		break;
	case BearGraphics::TPF_BC6:
		Uint8ToHalf4(in, src, w, h,  comp_src);
		break;
	case BearGraphics::TPF_BC7:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	default:
		BEAR_ASSERT(false)
	}

	EndCompressor(compressor, w, h, in, dst);
}

void BearGraphics::BearTextureUtils::FloatToHalf4(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToHalf4((uint16*)dst, src, comp_src);
		dst += 4 * 2;
		src += comp_src*4;
	}
}

void BearGraphics::BearTextureUtils::FloatToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		FloatPixelToUint8(dst, (float*)src, comp_dst, comp_src);
		dst += comp_dst ;
		src += comp_src * 4;
	}
}

void BearGraphics::BearTextureUtils::FloatToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		FloatPixelToFloat((float*)dst, (float*)src, comp_dst, comp_src);
		dst += comp_dst * 4;
		src += comp_src * 4;
	}
}

void BearGraphics::BearTextureUtils::FloatToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor, uint8 comp_src)
{
	uint8*in = (uint8*)StartCompressor(compressor, w, h);
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
		FloatToFloat(in, src, w, h, 3, comp_src);
		break;
	case BearGraphics::TPF_DXT_1_alpha:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_DXT_3:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_DXT_5:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case BearGraphics::TPF_BC4:
		FloatToUint8(in, src, w, h, 1, comp_src);
		break;
	case BearGraphics::TPF_BC5:
		FloatToUint8(in, src, w, h, 2, comp_src);
		break;
	case BearGraphics::TPF_BC6:
		FloatToHalf4(in, src, w, h, comp_src);
		break;
	case BearGraphics::TPF_BC7:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	default:
		BEAR_ASSERT(false)
	}

	EndCompressor(compressor, w, h, in, dst);
}

void BearGraphics::BearTextureUtils::CompressorToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor_dst, BearGraphics::BearTexturePixelFormat compressor_src)
{

	uint8*in_dst = (uint8*)StartCompressor(compressor_dst, w, h);
	switch (compressor_dst)
	{
	case BearGraphics::TPF_DXT_1:
		CompressorToFloat(in_dst, src, w, h, 4, compressor_src);
		break;
	case BearGraphics::TPF_DXT_1_alpha:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case BearGraphics::TPF_DXT_3:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case BearGraphics::TPF_DXT_5:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case BearGraphics::TPF_BC4:
		CompressorToUint8(in_dst, src, w, h, 1, compressor_src);
		break;
	case BearGraphics::TPF_BC5:
		CompressorToUint8(in_dst, src, w, h, 2, compressor_src);
		break;
	case BearGraphics::TPF_BC6:
	{		
	float*temp = BearCore::bear_alloc<float>(w*h * 3);
	CompressorToFloat((uint8*)temp, src, w, h, 3, compressor_src);
	FloatToHalf4(dst, (uint8*)temp, w, h, 3);
	BearCore::bear_free(temp);
	}
		break;
	case BearGraphics::TPF_BC7:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndCompressor(compressor_dst, w, h, in_dst, dst);
}

void BearGraphics::BearTextureUtils::CompressorToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, BearGraphics::BearTexturePixelFormat compressor)
{
	uint8*in=(uint8*)StartDecompressor(compressor, w, h, src);
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
		FloatToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_1_alpha:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_3:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_5:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_BC4:
		Uint8ToUint8(dst, in, w, h, comp_dst, 1);
		break;
	case BearGraphics::TPF_BC5:
		Uint8ToUint8(dst, in, w, h, comp_dst, 2);
		break;
	case BearGraphics::TPF_BC6:
		FloatToUint8(dst, in, w, h, comp_dst, 3);
		break;
	case BearGraphics::TPF_BC7:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndDecompressor(in);
}

void BearGraphics::BearTextureUtils::CompressorToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, BearGraphics::BearTexturePixelFormat compressor)
{
	uint8*in = (uint8*)StartDecompressor(compressor, w, h, src);
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
		FloatToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_1_alpha:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_3:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_DXT_5:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case BearGraphics::TPF_BC4:
		Uint8ToFloat(dst, in, w, h, comp_dst, 1);
		break;
	case BearGraphics::TPF_BC5:
		Uint8ToFloat(dst, in, w, h, comp_dst, 2);
		break;
	case BearGraphics::TPF_BC6:
		FloatToFloat(dst, in, w, h, comp_dst, 3);
		break;
	case BearGraphics::TPF_BC7:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndDecompressor(in);
}

void * BearGraphics::BearTextureUtils::StartCompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h)
{
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R32G32B32F)*h);
	case BearGraphics::TPF_DXT_1_alpha:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
	case BearGraphics::TPF_DXT_3:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
	case BearGraphics::TPF_DXT_5:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
	case BearGraphics::TPF_BC4:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8)*h);
	case BearGraphics::TPF_BC5:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8)*h);
	case BearGraphics::TPF_BC6:
		return BearCore::bear_alloc<uint8>(w*2*4*h);
	case BearGraphics::TPF_BC7:
		return BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearGraphics::BearTextureUtils::EndCompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h, void*in, void*out)
{
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT1);

		const uint32 bw =static_cast<uint32>( (w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);
		nv::CompressorDXT1 compressor;
		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				float wa[16];
				nv::Vector4 block[16];
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						wa[x + y * 4] = 1.f;

						block[x + y * 4].component[0] = *GetPixelFloat( bx * 4+x,  by * 4+y, w, 3,0,(uint8*) in);
						block[x + y * 4].component[1] = *(GetPixelFloat( bx * 4+x,  by * 4+y, w, 3, 1,(uint8*)in));
						block[x + y * 4].component[2] = *(GetPixelFloat( bx * 4+x,  by * 4+y, w, 3, 2,(uint8*)in));
						block[x + y * 4].component[3] = 1;


					}
				}
				compressor.compressBlock(block, wa, compOpt.m, (uint8*)out + 8 * (bx + (by * bw)));
			}
		}
	}
	break;
	case BearGraphics::TPF_DXT_1_alpha:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT1a);

		const uint32 bw = static_cast<uint32>((w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);
		nv::CompressorDXT1a compressor;
		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(x, y);
						color.r = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 0, (uint8*)in);
						color.g = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 1, (uint8*)in);
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 2, (uint8*)in);
						color.a = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 3, (uint8*)in);
						color.a = color.a > 127 ? 255 : 0;
					}
				}
				compressor.compressBlock(block, nvtt::AlphaMode_Transparency, compOpt.m, (uint8*)out + 8 * (bx + (by * bw)));
			}
		}
	}
	break;
	case BearGraphics::TPF_DXT_3:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT3);
		const uint32 bw = static_cast<uint32>((w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);
		nv::CompressorDXT3 compressor;
		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(x, y);
						color.r = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 0, (uint8*)in);
						color.g = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 1, (uint8*)in);
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 2, (uint8*)in);
						color.a = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 3, (uint8*)in);

					}
				}
				compressor.compressBlock(block, nvtt::AlphaMode_Transparency, compOpt.m, (uint8*)out + 16 * (bx + by * bw));
			}
		}
	}
	break;
	case BearGraphics::TPF_DXT_5:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT5);

		const uint32 bw = static_cast<uint32>((w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);
		nv::CompressorDXT5 compressor;
		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(x, y);
						color.r = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 0, (uint8*)in);
						color.g = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 1, (uint8*)in);
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 2, (uint8*)in);
						color.a = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 4, 3, (uint8*)in);

					}
				}
				compressor.compressBlock(block, nvtt::AlphaMode_Transparency, compOpt.m, (uint8*)out + 16 * (bx + by * bw));
			}
		}
	}
	break;
	case BearGraphics::TPF_BC4:
	{
		const uint32 bw = static_cast<uint32>((w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);

		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				nv::AlphaBlock4x4 alpha1;
				nv::AlphaBlockDXT5 alphaBlock1;
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(x, y);
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 1, 0, (uint8*)in);
					}
				}
				alpha1.init(block, 2);
				nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
				BearCore::bear_copy((uint8*)out + 8 * (bx + by * bw), &alphaBlock1.u, 8);
			}
		}
		break;
	}
	case BearGraphics::TPF_BC5:
	{
		const uint32 bw = static_cast<uint32>((w + 3) / 4);
		const uint32 bh = static_cast<uint32>((h + 3) / 4);

		for (uint32 by = 0; by < bh; by++)
		{
			for (uint32 bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				nv::AlphaBlock4x4 alpha1, alpha2;
				nv::AlphaBlockDXT5 alphaBlock1, alphaBlock2;
				for (uint y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(x, y);
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 2, 0, (uint8*)in);
						color.g = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 2,1, (uint8*)in);
						//in = (uint8*)in + 2;
					}
				}
				alpha1.init(block, 2);
				alpha2.init(block, 1);
				nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
				nv::QuickCompress::compressDXT5A(alpha2, &alphaBlock2, 8);
				BearCore::bear_copy((uint8*)out + 16 * (bx + by * bw), &alphaBlock1.u, 8);
				BearCore::bear_copy((uint8*)out + 16 * (bx + by * bw) + 8, &alphaBlock2.u, 8);
			}
		}
	}
	break;
	case BearGraphics::TPF_BC6:
	{
		rgba_surface surface;
		surface.height = static_cast<uint32>(h);
		surface.width = static_cast<uint32>(w);
		surface.ptr = (uint8*)in;
		surface.stride = static_cast<uint32>(w * 2 * 4);
		bc6h_enc_settings str;
		GetProfile_bc6h_veryslow(&str);
		CompressBlocksBC6H(&surface, (uint8*)out, &str);
	}
	break;
	case BearGraphics::TPF_BC7:
	{
		rgba_surface surface;
		surface.height = static_cast<uint32>(h);
		surface.width = static_cast<uint32>(w);
		surface.ptr = (uint8*)in;
		surface.stride = static_cast<uint32>(w * 4);
		bc7_enc_settings str;
		GetProfile_alpha_slow(&str);
		CompressBlocksBC7(&surface, (uint8*)out, &str);
		break;
	}
	default:
		BEAR_ASSERT(false);
	}
	BearCore::bear_free(in);
}

void * BearGraphics::BearTextureUtils::StartDecompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h, void * in)
{
	switch (compressor)
	{
	case BearGraphics::TPF_DXT_1_alpha:
	case BearGraphics::TPF_DXT_1:
	{

		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT1 dx1;
				nv::ColorBlock cl;
				BearCore::bear_copy(&dx1.col0, (uint8*)in + 8 * (bx + (by*bw)), 4);
				BearCore::bear_copy(&dx1.col1, (uint8*)in + 8 * (bx + (by*bw)) + 4, 4);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 0, new_img) = cl.color(x, y).r;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 1, new_img) = cl.color(x, y).g;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 2, new_img) = cl.color(x, y).b;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 3, new_img) = cl.color(x, y).a;

					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_DXT_3:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT3 dx1;
				nv::ColorBlock cl;
				BearCore::bear_copy(&dx1.color.col0, (uint8*)in + 16 * (bx + (by*bw)), 4);
				BearCore::bear_copy(&dx1.color.col1, (uint8*)in + 16 * (bx + (by*bw)) + 4, 4);
				BearCore::bear_copy(&dx1.alpha.row, (uint8*)in + 16 * (bx + (by*bw)) + 8, 16);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 0, new_img) = cl.color(x, y).r;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 1, new_img) = cl.color(x, y).g;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 2, new_img) = cl.color(x, y).b;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 3, new_img) = cl.color(x, y).a;

					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_DXT_5:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT5 dx1;
				nv::ColorBlock cl;
				BearCore::bear_copy(&dx1.color.col0, (uint8*)in + 16 * (bx + (by*bw)), 4);
				BearCore::bear_copy(&dx1.color.col1, (uint8*)in + 16 * (bx + (by*bw)) + 4, 4);
				BearCore::bear_copy(&dx1.alpha.u, (uint8*)in + 16 * (bx + (by*bw)) + 8, 16);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 0, new_img) = cl.color(x, y).r;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 1, new_img) = cl.color(x, y).g;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 2, new_img) = cl.color(x, y).b;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 3, new_img) = cl.color(x, y).a;

					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_BC4:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockATI1 ATI1;
				nv::ColorBlock cl;
				BearCore::bear_copy(&ATI1.alpha, (uint8*)in + 8 * (bx + (by*bw)), 8);
				ATI1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 1, 0, new_img) = cl.color(x, y).r;

					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_BC5:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockATI2 ATI2;
				nv::ColorBlock cl;
				BearCore::bear_copy(&ATI2.x, (uint8*)in + 16 * (bx + (by*bw)), 8);
				BearCore::bear_copy(&ATI2.y, (uint8*)in + 16 * (bx + (by*bw)) + 8, 8);
				ATI2.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 2, 0, new_img) = cl.color(x, y).r;
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 2, 1, new_img) = cl.color(x, y).g;
					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_BC6:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R32G32B32F)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockBC6 b6;
				nv::Vector3 cl[16];
				BearCore::bear_copy(b6.data, (uint8*)in + 16 * (bx + (by*bw)), 16);
				b6.decodeBlock(cl);

				for (bsize y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						BearCore::bear_copy(GetPixelFloat(x + bx * 4, y + by * 4, w, 3, 0, new_img), cl[x + y * 4].component, 3);
						//swapRG(*reinterpret_cast<uint32*>(getPixelComp((uint8*)out, w, x + bx * 4, y + by * 4, out_comp, 0));
					}
				}
			}
		}
		return new_img;
	}
	break;
	case BearGraphics::TPF_BC7:
	{
		uint8*new_img = BearCore::bear_alloc<uint8>(GetSizeWidth(w, BearGraphics::TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockBC7 b7;
				nv::ColorBlock cl;
				BearCore::bear_copy(b7.data, (uint8*)in + 16 * (bx + (by*bw)), 16);
				b7.decodeBlock(&cl);

				for (uint32 y = 0; y < BearCore::bear_min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearCore::bear_min(bsize(4), w - 4 * bx); x++)
					{
						SwapRB(*reinterpret_cast<uint32*>((uint8*)cl.color(x, y).component));
						BearCore::bear_copy(GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 0, new_img), cl.color(x, y).component, 4);
					}
				}
			}
		}
		return new_img;
	}
	break;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearGraphics::BearTextureUtils::EndDecompressor(void * in)
{
	BearCore::bear_free(in);
}

