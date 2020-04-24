#include "BearGraphics.hpp"
#include "BearRHI/BearTextureUtils.h"
#ifdef DEVELOPER_VERSION
#include "IntelCompressor/ispc_texcomp.h"
#include "Nvtt/nvimage\ColorBlock.h"
#include "Nvtt/nvimage\BlockDXT.h"
#include "Nvtt/nvtt/CompressorDX9.h"
#include "Nvtt/nvtt/QuickCompressDXT.h"
#endif
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "StbImage/stb_image_resize.h"
bsize BearTextureUtils::GetSizeWidth(bsize w, BearTexturePixelFormat format)
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

bsize BearTextureUtils::GetSizeDepth(bsize w, bsize h, BearTexturePixelFormat format)
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

bsize BearTextureUtils::GetSizePixel(BearTexturePixelFormat format)
{
	switch (format)
	{
	case TPF_R8:
		return 1;
		break;
	case TPF_R8G8:
		return 2;
		break;
	case TPF_R8G8B8:
		return 3;
		break;
	case TPF_R8G8B8A8:
		return 4;
		break;
	case TPF_R32F:
		return 4;
		break;
	case TPF_R32G32F:
		return 8;
		break;
	case TPF_R32G32B32F:
		return 12;
		break;
	case TPF_R32G32B32A32F:
		return 16;
		break;
	default:
		BEAR_ASSERT(false);
		break;

	}
	return 0;
}

void BearTextureUtils::Append(uint8*dst, bsize w_dst, bsize h_dst, bsize x_dst, bsize y_dst, uint8*src, bsize w_src, bsize h_src, BearVector4<bsize> squard_src, BearTexturePixelFormat dst_format, BearTexturePixelFormat src_format)
{
	if (isCompressor(dst_format))
	{
		BearTexturePixelFormat px_out;
		uint8*dst_temp = TempUncompressor(dst, w_dst, h_dst, dst_format, px_out);
		Append(dst_temp, w_dst, h_dst, x_dst, y_dst, src, w_src, h_src, squard_src, px_out, src_format);
		TempCompress(dst_temp, dst, w_dst, h_dst, dst_format);
		return;
	}
	if (isCompressor(src_format))
	{
		BearTexturePixelFormat px_out;
		uint8*src_temp = TempUncompressor(src, w_src, h_src, src_format, px_out);
		Append(dst, w_dst, h_dst, x_dst, y_dst, src_temp, w_src, h_src, squard_src, dst_format, px_out );
		TempCompress(src_temp, 0, w_src, h_src, src_format);
		return;
	}
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
	else if (isFloatPixel(dst_format) )
	{
		for (bsize iy = 0; iy<squard_src.y1; iy++)
			for (bsize ix = 0; ix < squard_src.x1; ix++)
			{
				Uint8PixelToFloat(GetPixelFloat(ix + x_dst, iy + y_dst, w_dst, dst_comp, 0, dst), GetPixelUint8(ix + squard_src.x, iy + squard_src.y, w_src, src_comp, 0, src), dst_comp, src_comp);
			}
	}
	else if (isFloatPixel(src_format))
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


bsize BearTextureUtils::GetCountMips(bsize w, bsize h)
{
	bsize max_size = BearMath::max(w, h);
	return static_cast<bsize>(log2f(static_cast<float>(max_size))+1);
}

bsize BearTextureUtils::GetMip(bsize w, bsize level)
{
	bsize mip = static_cast<bsize>((w ) / pow(2, static_cast<double>(level)));
	return BearMath::max(mip, bsize(1));
}

uint8 * BearTextureUtils::GetPixelUint8(bsize x, bsize y, bsize w, bsize comps, bsize comp_id, uint8 * data)
{
	return  &data[(x + (y * w))*comps+comp_id];
}

float * BearTextureUtils::GetPixelFloat(bsize x, bsize y, bsize w, bsize comps, bsize comp_id, uint8 * data)
{
	return (float*)&data[y*w*comps*4+x*4*comps+comp_id*4];
}

bool BearTextureUtils::isFloatPixel(BearTexturePixelFormat format)
{
	switch (format)
	{
	case TPF_R8:
	case TPF_R8G8:
	case TPF_R8G8B8:
	case TPF_R8G8B8A8:
		return false;;
		break;
	case TPF_R32F:
	case TPF_R32G32F:
	case TPF_R32G32B32F:
	case TPF_R32G32B32A32F:
		return true;
	case TPF_DXT_1:
	case TPF_DXT_1_alpha:
	case TPF_DXT_3:
	case TPF_DXT_5:
	case TPF_BC4:
	case TPF_BC5:
	case TPF_BC6:
	case TPF_BC7:
		return false;

		break;
	default:
		BEAR_ASSERT(false);
	}
	return false;
}

bool BearTextureUtils::isCompressor(BearTexturePixelFormat format)
{
	switch (format)
	{
	case TPF_R8:
	case TPF_R8G8:
	case TPF_R8G8B8:
	case TPF_R8G8B8A8:
	case TPF_R32F:
	case TPF_R32G32F:
	case TPF_R32G32B32F:
	case TPF_R32G32B32A32F:
		return false;
		break;
	case TPF_DXT_1:
	case TPF_DXT_1_alpha:
	case TPF_DXT_3:
	case TPF_DXT_5:
	case TPF_BC4:
	case TPF_BC5:
	case TPF_BC6:
	case TPF_BC7:
		return true;
	default:
		break;
	}
	return false;
}

void BearTextureUtils::Fill(uint8 * data, bsize w, bsize h, bsize mip, const BearColor & color, BearTexturePixelFormat format)
{	
	if (isCompressor(format))
	{
		BearTexturePixelFormat  px_out;
		bsize pixel_size = GetSizeBlock(format);
		for (bsize i = 0; i < mip; i++) 
		{

			bsize mip_w = GetMip(w, i);
			bsize mip_h = GetMip(h, i);
			uint8*temp = TempUncompressor(0, mip_w, mip_h, format, px_out);

			if (isFloatPixel(px_out))
			{
				FillFloat(temp, mip_w, mip_h, color, px_out);
			}
			else
			{
				FillUint8(temp, mip_w, mip_h, color, px_out);
			}
		
			TempCompress(temp, data, mip_w, mip_h, format);
			data += pixel_size * GetCountBlock(mip_w)*GetCountBlock(mip_h);
		}

	}
	
	else if (isFloatPixel(format))
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

bsize BearTextureUtils::GetSizeInMemory(bsize w, bsize h, bsize mips, BearTexturePixelFormat format)
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

void BearTextureUtils::Convert(BearTexturePixelFormat dst_format, BearTexturePixelFormat src_format, uint8 * dst, uint8 * src, bsize w, bsize h)
{
	if (src_format == dst_format) { bear_copy(dst, src, GetSizeInMemory(w, h, 1, dst_format)); return; }
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

bsize BearTextureUtils::GetCountBlock(bsize w)
{
	return (w + 3) / 4;
}

bsize BearTextureUtils::GetCountBlock(bsize w, BearTexturePixelFormat format)
{
	if (isCompressor(format))
	{
		return GetCountBlock(w);
	}
	else
	{
		return w;
	}
}

bsize BearTextureUtils::GetSizeBlock(BearTexturePixelFormat format)
{
	switch (format)
	{
	case TPF_DXT_1:
		return 8;
	case TPF_DXT_1_alpha:
		return 8;
	case TPF_DXT_3:
		return 16;
	case TPF_DXT_5:
		return 16;
	case TPF_BC4:
		return 8;
		break;
	case TPF_BC5:
		return 16;
		break;
	case TPF_BC6:
		return 16;
		break;
	case TPF_BC7:
		return 16;
		break;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}	

uint8 BearTextureUtils::GetCountComp(BearTexturePixelFormat format)
{
	switch (format)
	{
	case TPF_R8:
		return 1;
		break;
	case TPF_R8G8:
		return 2;
		break;
	case TPF_R8G8B8:
		return 3;
		break;
	case TPF_R8G8B8A8:
		return 4;
		break;
	case TPF_R32F:
		return 1;
		break;
	case TPF_R32G32F:
		return 2;
		break;
	case TPF_R32G32B32F:
		return 3;
		break;
	case TPF_R32G32B32A32F:
		return 4;
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearTextureUtils::GenerateMip(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, BearTexturePixelFormat format)
{
	if (isCompressor(format))
	{
		BearTexturePixelFormat px_out;
		uint8*scr_temp = TempUncompressor(src, w_src, h_src, format, px_out);
		uint8*dst_temp = TempUncompressor(0, w_src/2, h_src/2, format, px_out);
		GenerateMip(dst_temp, scr_temp, w_src, h_src, px_out);
		TempCompress(scr_temp, 0, w_src, h_src, format);
		TempCompress(dst_temp, dst, w_src / 2, h_src / 2, format);
	}
	else if (isFloatPixel(format))
	{
		GenerateMipFloat(dst, src, w_src, h_src,GetCountComp(format));
	}
	else
	{
		GenerateMipUint8(dst, src, w_src, h_src, GetCountComp(format));
	}
}

void BearTextureUtils::Scale(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, BearTexturePixelFormat format)
{
	if (isCompressor(format))
	{
		BearTexturePixelFormat px_out;
		uint8*scr_temp = TempUncompressor(src, w_src, h_src, format, px_out);
		uint8*dst_temp = TempUncompressor(0, w_dst, h_dst, format, px_out);
		Scale(dst_temp, w_dst, h_dst, scr_temp, w_src, h_src, px_out);
		TempCompress(scr_temp, 0, w_src, h_src, format);
		TempCompress(dst_temp, dst, w_dst, h_dst, format);
	}
	else if (isFloatPixel(format))
	{
		ScaleFloat(dst, w_dst, h_dst, src, w_src, h_src, GetCountComp(format));
	}
	else
	{
		ScaleUint8(dst, w_dst, h_dst, src, w_src, h_src, GetCountComp(format));
	}
}

uint8 * BearTextureUtils::GetImage(uint8 * data, bsize w, bsize h, bsize mips, bsize depth, bsize mip, BearTexturePixelFormat format)
{
	return data + BearTextureUtils::GetSizeInMemory(w, h, mips, format)*depth + BearTextureUtils::GetSizeInMemory(w, h, mip, format);
}

void BearTextureUtils::GetPixel(BearColor & color,  uint8*data, bsize x, bsize y, bsize depth, bsize w, bsize h, bsize mips, BearTexturePixelFormat format)
{
	color = BearColor::Black;
	uint8*img = data + BearTextureUtils::GetSizeInMemory(w, h, mips, format)*depth;
	if (isCompressor(format))
	{
		BearColor colors[16];
		GetBlock(colors, img, w, h, x, y, format);
		color = colors[x % 4 +( 4 * (y % 4))];
	}
	else if (isFloatPixel(format))
	{
		float* pixels = GetPixelFloat(x, y, w, GetCountComp(format), 0, data);
		switch ( GetCountComp(format))
		{
		case 1:
			color.SetAsFloat(  pixels[0],0,0);
			break;
		case 2:
			color.SetAsFloat(pixels[0], pixels[1], 0);
			break;
		case 3:
			color.SetAsFloat(pixels[0], pixels[1], pixels[2]);
			break;
		case 4:
			color.SetAsFloat(pixels[0], pixels[1], pixels[2], pixels[3]);
			break;
		default:
			BEAR_CHECK(false);
			break;
		}
	}
	else 
	{
		uint8* pixels = GetPixelUint8(x, y, w, GetCountComp(format), 0, data);
		switch (GetCountComp(format))
		{
		case 1:
			color.SetAsUint8(pixels[0], 0, 0);
			break;
		case 2:
			color.SetAsUint8(pixels[0], pixels[1], 0);
			break;
		case 3:
			color.SetAsUint8(pixels[0], pixels[1], pixels[2]);
			break;
		case 4:
			color.SetAsUint8(pixels[0], pixels[1], pixels[2], pixels[3]);
			break;
		default:
			BEAR_CHECK(false);
			break;
		}
	}

	return;
}

void BearTextureUtils::SetPixel(const BearColor & color, uint8 * data, bsize x, bsize y,bsize depth, bsize w, bsize h, bsize mips, BearTexturePixelFormat format)
{
	uint8*img = data + BearTextureUtils::GetSizeInMemory(w, h, mips, format)*depth;
	if (isCompressor(format))
	{
		BearColor colors[16];
		GetBlock(colors, img, w, h, x, y, format);
		colors[x % 4 + (4 * (y % 4))] = color;
		SetBlock(colors, img, w, h, x, y, format);
	}
	else if (isFloatPixel(format))
	{
		float* pixels = GetPixelFloat(x, y, w, GetCountComp(format), 0, data);
		switch (GetCountComp(format))
		{
		case 1:
			bear_copy(pixels, color.R32G32B32A32, 1);
			break;
		case 2:
			bear_copy(pixels, color.R32G32B32A32,2);
			break;
		case 3:
			bear_copy(pixels, color.R32G32B32A32, 3);
			break;
		case 4:
			bear_copy(pixels, color.R32G32B32A32, 4);
			break;
		default:
			BEAR_CHECK(false);
			break;
		}
	}
	else
	{
		uint8* pixels = GetPixelUint8(x, y, w, GetCountComp(format), 0, data);
		switch (GetCountComp(format))
		{
		case 1:
			bear_copy(pixels, &color.R8G8B8A8, 1);
			break;
		case 2:
			bear_copy(pixels, &color.R8G8B8A8, 2);
			break;
		case 3:
			bear_copy(pixels, &color.R8G8B8A8,3);
			break;
		case 4:
			bear_copy(pixels, &color.R8G8B8A8, 4);
			break;
		default:
			BEAR_CHECK(false);
			break;
		}
	}

	return;
}

void BearTextureUtils::ScaleFloat(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, uint8 comp)
{
	stbir_resize_float(reinterpret_cast<float*>(src),static_cast<int>( w_src), static_cast<int>(h_src), 0, reinterpret_cast<float*>(dst), static_cast<int>(w_dst), static_cast<int>(h_dst), 0, comp);
}

void BearTextureUtils::ScaleUint8(uint8 * dst, bsize w_dst, bsize h_dst, uint8 * src, bsize w_src, bsize h_src, uint8 comp)
{

	stbir_resize_uint8(src, static_cast<int>(w_src), static_cast<int>(h_src), 0, dst, static_cast<int>(w_dst), static_cast<int>(h_dst),0, comp);

}



void BearTextureUtils::GenerateMipFloat(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, uint8 comps)
{
	ScaleFloat(dst, w_src / 2, h_src / 2, src, w_src, h_src, comps);
}

void BearTextureUtils::GenerateMipUint8(uint8 * dst, uint8 * src, bsize w_src, bsize h_src, uint8 comps)
{
	ScaleUint8(dst, w_src / 2, h_src / 2, src, w_src, h_src, comps);
}

void BearTextureUtils::FloatPixelToUint8(uint8 * dst, float * src, uint8 comp_dst, uint8 comp_src)
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

void BearTextureUtils::FloatPixelToFloat(float * dst, float * src, uint8 comp_dst, uint8 comp_src)
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

void BearTextureUtils::Uint8PixelToFloat(float * dst, uint8 * src, uint8 comp_dst, uint8 comp_src)
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
void BearTextureUtils::Uint8PixelToUint8(uint8 * dst, uint8 * src, uint8 comp_dst, uint8 comp_src)
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

void BearTextureUtils::FloatPixelToHalf4(uint16 * dst, float * src, uint8 comp_src)
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

void BearTextureUtils::Uint8PixelToHalf4(uint16 * dst, uint8 * src, uint8 comp_src)
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

void BearTextureUtils::SwapRB(uint32 & color)
{
		uint32 r = color & 0x000000FF;

		uint32 b = color & 0x00FF0000;
		uint32 g = color & 0x0000FF00;
		uint32 a = color & 0xFF000000;
		color = (b >> 16) | g | (r << 16) | a;
}

void BearTextureUtils::FillUint8(uint8 * data, bsize x, bsize y, const BearColor & color, BearTexturePixelFormat format)
{
	bsize size_pixel = GetSizePixel(format);
	for (bsize i = 0; i < x*y; i++)
	{
		bear_copy(data + (size_pixel*i), &color.R8G8B8A8, size_pixel);
	}
}

void BearTextureUtils::FillFloat(uint8 * data, bsize x, bsize y, const BearColor & color, BearTexturePixelFormat format)
{
	bsize size_pixel = GetSizePixel(format);
	for (bsize i = 0; i < x*y; i++)
	{
		bear_copy(data + (size_pixel*i), color.R32G32B32A32, size_pixel);
	}
}

void BearTextureUtils::Uint8ToHalf4(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToHalf4((uint16*)dst, src, comp_src);
		dst += 4*2;
		src += comp_src;
	}
}

void BearTextureUtils::Uint8ToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToFloat((float*)dst, src, comp_dst, comp_src);
		dst += comp_dst * 4;
		src += comp_src;
	}
}

void BearTextureUtils::Uint8ToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToUint8(dst, src, comp_dst, comp_src);
		dst += comp_dst ;
		src += comp_src;
	}
}

void BearTextureUtils::Uint8ToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearTexturePixelFormat compressor, uint8 comp_src)
{
	uint8*in=(uint8*)StartCompressor(compressor,w,h);
	switch (compressor)
	{
	case TPF_DXT_1:
		Uint8ToFloat(in, src, w, h, 3, comp_src);
		break;
	case TPF_DXT_1_alpha:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_DXT_3:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_DXT_5:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_BC4:
		Uint8ToUint8(in, src, w, h, 1, comp_src);
		break;
	case TPF_BC5:
		Uint8ToUint8(in, src, w, h, 2, comp_src);
		break;
	case TPF_BC6:
		Uint8ToHalf4(in, src, w, h,  comp_src);
		break;
	case TPF_BC7:
		Uint8ToUint8(in, src, w, h, 4, comp_src);
		break;
	default:
		BEAR_ASSERT(false)
	}

	EndCompressor(compressor, w, h, in, dst);
}

void BearTextureUtils::FloatToHalf4(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		Uint8PixelToHalf4((uint16*)dst, src, comp_src);
		dst += 4 * 2;
		src += comp_src*4;
	}
}

void BearTextureUtils::FloatToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		FloatPixelToUint8(dst, (float*)src, comp_dst, comp_src);
		dst += comp_dst ;
		src += comp_src * 4;
	}
}

void BearTextureUtils::FloatToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src)
{
	for (bsize i = 0; i < w*h; i++)
	{
		FloatPixelToFloat((float*)dst, (float*)src, comp_dst, comp_src);
		dst += comp_dst * 4;
		src += comp_src * 4;
	}
}

void BearTextureUtils::FloatToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearTexturePixelFormat compressor, uint8 comp_src)
{
	uint8*in = (uint8*)StartCompressor(compressor, w, h);
	switch (compressor)
	{
	case TPF_DXT_1:
		FloatToFloat(in, src, w, h, 3, comp_src);
		break;
	case TPF_DXT_1_alpha:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_DXT_3:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_DXT_5:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	case TPF_BC4:
		FloatToUint8(in, src, w, h, 1, comp_src);
		break;
	case TPF_BC5:
		FloatToUint8(in, src, w, h, 2, comp_src);
		break;
	case TPF_BC6:
		FloatToHalf4(in, src, w, h, comp_src);
		break;
	case TPF_BC7:
		FloatToUint8(in, src, w, h, 4, comp_src);
		break;
	default:
		BEAR_ASSERT(false)
	}

	EndCompressor(compressor, w, h, in, dst);
}

void BearTextureUtils::CompressorToCompressor(uint8 * dst, uint8 * src, bsize w, bsize h, BearTexturePixelFormat compressor_dst, BearTexturePixelFormat compressor_src)
{

	uint8*in_dst = (uint8*)StartCompressor(compressor_dst, w, h);
	switch (compressor_dst)
	{
	case TPF_DXT_1:
		CompressorToFloat(in_dst, src, w, h, 3, compressor_src);
		break;
	case TPF_DXT_1_alpha:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case TPF_DXT_3:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case TPF_DXT_5:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	case TPF_BC4:
		CompressorToUint8(in_dst, src, w, h, 1, compressor_src);
		break;
	case TPF_BC5:
		CompressorToUint8(in_dst, src, w, h, 2, compressor_src);
		break;
	case TPF_BC6:
	{		
	float*temp = bear_alloc<float>(w*h * 3);
	CompressorToFloat((uint8*)temp, src, w, h, 3, compressor_src);
	FloatToHalf4(dst, (uint8*)temp, w, h, 3);
	bear_free(temp);
	}
		break;
	case TPF_BC7:
		CompressorToUint8(in_dst, src, w, h, 4, compressor_src);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndCompressor(compressor_dst, w, h, in_dst, dst);
}

void BearTextureUtils::CompressorToUint8(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, BearTexturePixelFormat compressor)
{
	uint8*in=(uint8*)StartDecompressor(compressor, w, h, src);
	switch (compressor)
	{
	case TPF_DXT_1:
	case TPF_DXT_1_alpha:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_DXT_3:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_DXT_5:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_BC4:
		Uint8ToUint8(dst, in, w, h, comp_dst, 1);
		break;
	case TPF_BC5:
		Uint8ToUint8(dst, in, w, h, comp_dst, 2);
		break;
	case TPF_BC6:
		FloatToUint8(dst, in, w, h, comp_dst, 3);
		break;
	case TPF_BC7:
		Uint8ToUint8(dst, in, w, h, comp_dst, 4);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndDecompressor(in);
}

void BearTextureUtils::CompressorToFloat(uint8 * dst, uint8 * src, bsize w, bsize h, uint8 comp_dst, BearTexturePixelFormat compressor)
{
	uint8*in = (uint8*)StartDecompressor(compressor, w, h, src);
	switch (compressor)
	{
	case TPF_DXT_1:
	case TPF_DXT_1_alpha:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_DXT_3:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_DXT_5:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	case TPF_BC4:
		Uint8ToFloat(dst, in, w, h, comp_dst, 1);
		break;
	case TPF_BC5:
		Uint8ToFloat(dst, in, w, h, comp_dst, 2);
		break;
	case TPF_BC6:
		FloatToFloat(dst, in, w, h, comp_dst, 3);
		break;
	case TPF_BC7:
		Uint8ToFloat(dst, in, w, h, comp_dst, 4);
		break;
	default:
		BEAR_ASSERT(false)
	}
	EndDecompressor(in);
}

void * BearTextureUtils::StartCompressor(BearTexturePixelFormat compressor, bsize w, bsize h)
{
	switch (compressor)
	{
	case TPF_DXT_1:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R32G32B32F)*h);
	case TPF_DXT_1_alpha:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
	case TPF_DXT_3:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
	case TPF_DXT_5:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
	case TPF_BC4:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8)*h);
	case TPF_BC5:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8)*h);
	case TPF_BC6:
		return bear_alloc<uint8>(w*2*4*h);
	case TPF_BC7:
		return bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
	default:
		BEAR_ASSERT(false);
	}
	return 0;
}

void BearTextureUtils::EndCompressor(BearTexturePixelFormat compressor_, bsize w, bsize h, void*in, void*out)
{

#ifdef DEVELOPER_VERSION
	switch (compressor_)
	{
	case TPF_DXT_1:
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
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
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
	case TPF_DXT_1_alpha:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT1a);

		const bsize bw = static_cast<bsize>((w + 3) / 4);
		const bsize bh = static_cast<bsize>((h + 3) / 4);
		nv::CompressorDXT1a compressor;
		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						auto&color = block.color(static_cast<uint>(x), static_cast<uint>(y));
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
	case TPF_DXT_3:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT3);
		const bsize bw = static_cast<bsize>((w + 3) / 4);
		const bsize bh = static_cast<bsize>((h + 3) / 4);
		nv::CompressorDXT3 compressor;
		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						auto& color = block.color(static_cast<uint>(x), static_cast<uint>(y));
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
	case TPF_DXT_5:
	{
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, true);

		compOpt.setFormat(nvtt::Format_DXT5);

		const bsize bw = static_cast<bsize>((w + 3) / 4);
		const bsize bh = static_cast<bsize>((h + 3) / 4);
		nv::CompressorDXT5 compressor;
		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						auto& color = block.color(static_cast<uint>(x), static_cast<uint>(y));
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
	case TPF_BC4:
	{
		const bsize bw = static_cast<bsize>((w + 3) / 4);
		const bsize bh = static_cast<bsize>((h + 3) / 4);

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				nv::AlphaBlock4x4 alpha1;
				nv::AlphaBlockDXT5 alphaBlock1;
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						auto& color = block.color(static_cast<uint>(x), static_cast<uint>(y));
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 1, 0, (uint8*)in);
					}
				}
				alpha1.init(block, 2);
				nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
				bear_copy((uint8*)out + 8 * (bx + by * bw), &alphaBlock1.u, 8);
			}
		}
		break;
	}
	case TPF_BC5:
	{
		const bsize bw = static_cast<bsize>((w + 3) / 4);
		const bsize bh = static_cast<bsize>((h + 3) / 4);

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::ColorBlock block;
				nv::AlphaBlock4x4 alpha1, alpha2;
				nv::AlphaBlockDXT5 alphaBlock1, alphaBlock2;
				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						auto& color = block.color(static_cast<uint>(x), static_cast<uint>(y));
						color.b = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 2, 0, (uint8*)in);
						color.g = *GetPixelUint8(bx * 4 + x, by * 4 + y, w, 2,1, (uint8*)in);
						//in = (uint8*)in + 2;
					}
				}
				alpha1.init(block, 2);
				alpha2.init(block, 1);
				nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
				nv::QuickCompress::compressDXT5A(alpha2, &alphaBlock2, 8);
				bear_copy((uint8*)out + 16 * (bx + by * bw), &alphaBlock1.u, 8);
				bear_copy((uint8*)out + 16 * (bx + by * bw) + 8, &alphaBlock2.u, 8);
			}
		}
	}
	break;
	case TPF_BC6:
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
	case TPF_BC7:
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
	bear_free(in);
#else
BEAR_ASSERT(false);
#endif
}

void * BearTextureUtils::StartDecompressor(BearTexturePixelFormat compressor, bsize w, bsize h, void * in)
{

#ifdef DEVELOPER_VERSION
	switch (compressor)
	{
	case TPF_DXT_1_alpha:
	case TPF_DXT_1:
	{

		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT1 dx1;
				nv::ColorBlock cl;
				bear_copy(&dx1.col0.u, (uint8*)in + 8 * (bx + (by*bw)), 2);
				bear_copy(&dx1.col1.u, (uint8*)in + 8 * (bx + (by*bw)) + 2, 2);
				bear_copy(&dx1.indices, (uint8*)in + 8 * (bx + (by*bw)) + 4, 4);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
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
	case TPF_DXT_3:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT3 dx1;
				nv::ColorBlock cl;
				bear_copy(&dx1.color.col0.u, (uint8*)in + 16 * (bx + (by*bw)) + 8, 2);
				bear_copy(&dx1.color.col1.u, (uint8*)in + 16 * (bx + (by*bw)) + 2 + 8, 2);
				bear_copy(&dx1.color.indices, (uint8*)in + 16 * (bx + (by*bw)) + 4 + 8, 4);
				bear_copy(&dx1.alpha.row, (uint8*)in + 16 * (bx + (by*bw)) , 8);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
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
	case TPF_DXT_5:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockDXT5 dx1;
				nv::ColorBlock cl;
				bear_copy(&dx1.color.col0.u, (uint8*)in + 16 * (bx + (by*bw)) + 8, 2);
				bear_copy(&dx1.color.col1.u, (uint8*)in + 16 * (bx + (by*bw)) + 2 + 8, 2);
				bear_copy(&dx1.color.indices, (uint8*)in + 16 * (bx + (by*bw)) + 4+ 8, 4);
				bear_copy(&dx1.alpha.u, (uint8*)in + 16 * (bx + (by*bw)) , 8);
				dx1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
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
	case TPF_BC4:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockATI1 ATI1;
				nv::ColorBlock cl;
				bear_copy(&ATI1.alpha, (uint8*)in + 8 * (bx + (by*bw)), 8);
				ATI1.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						*GetPixelUint8(x + bx * 4, y + by * 4, w, 1, 0, new_img) = cl.color(x, y).r;

					}
				}
			}
		}
		return new_img;
	}
	break;
	case TPF_BC5:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockATI2 ATI2;
				nv::ColorBlock cl;
				bear_copy(&ATI2.x, (uint8*)in + 16 * (bx + (by*bw)), 8);
				bear_copy(&ATI2.y, (uint8*)in + 16 * (bx + (by*bw)) + 8, 8);
				ATI2.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
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
	case TPF_BC6:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R32G32B32F)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockBC6 b6;
				nv::Vector3 cl[16];
				bear_copy(b6.data, (uint8*)in + 16 * (bx + (by*bw)), 16);
				b6.decodeBlock(cl);

				for (bsize y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (bsize x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						bear_copy(GetPixelFloat(x + bx * 4, y + by * 4, w, 3, 0, new_img), cl[x + y * 4].component, 3);
						//swapRG(*reinterpret_cast<uint32*>(getPixelComp((uint8*)out, w, x + bx * 4, y + by * 4, out_comp, 0));
					}
				}
			}
		}
		return new_img;
	}
	break;
	case TPF_BC7:
	{
		uint8*new_img = bear_alloc<uint8>(GetSizeWidth(w, TPF_R8G8B8A8)*h);
		const bsize bw = (w + 3) / 4;
		const bsize bh = (h + 3) / 4;

		for (bsize by = 0; by < bh; by++)
		{
			for (bsize bx = 0; bx < bw; bx++)
			{
				nv::BlockBC7 b7;
				nv::ColorBlock cl;
				bear_copy(b7.data, (uint8*)in + 16 * (bx + (by*bw)), 16);
				b7.decodeBlock(&cl);

				for (uint32 y = 0; y < BearMath::min(bsize(4), h - 4 * by); y++)
				{
					for (uint32 x = 0; x < BearMath::min(bsize(4), w - 4 * bx); x++)
					{
						SwapRB(*reinterpret_cast<uint32*>((uint8*)cl.color(x, y).component));
						bear_copy(GetPixelUint8(x + bx * 4, y + by * 4, w, 4, 0, new_img), cl.color(x, y).component, 4);
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
#else
BEAR_ASSERT(false);
return 0;
#endif
}

void BearTextureUtils::EndDecompressor(void * in)
{
	bear_free(in);
}

void BearTextureUtils::GetBlock(BearColor(&color)[16], uint8 * data, bsize w, bsize h, bsize x_, bsize y, BearTexturePixelFormat px)
{
#ifdef DEVELOPER_VERSION

	uint8*block = data + ((x_ / 4) + ((w + 3) / 4)*(y / 4))*(px == BearTexturePixelFormat::TPF_BC1 || px == BearTexturePixelFormat::TPF_BC1a || px == BearTexturePixelFormat::TPF_BC4 ? 8 : 16);
	nv::ColorBlock cl;
	switch (px)
	{

	case BearTexturePixelFormat::TPF_BC1:
	{
		nv::BlockDXT1 dxt1;

		bear_copy(&dxt1.col0, block, 8);
		dxt1.decodeBlock(&cl);

		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC1a:
	{
		nv::BlockDXT1 dxt1;

		bear_copy(&dxt1.col0, block, 8);
		dxt1.decodeBlock(&cl);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC2:
	{
		nv::BlockDXT3 dxt3;

		bear_copy(&dxt3.alpha, block, 8);
		bear_copy(&dxt3.color, block + 8, 8);
		dxt3.decodeBlock(&cl);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC3:
	{
		nv::BlockDXT5 dxt5;

		bear_copy(&dxt5.alpha, block, 8);
		bear_copy(&dxt5.color, block+8, 8);
		dxt5.decodeBlock(&cl);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC4:
	{
		nv::BlockATI1 at1;

		bear_copy(&at1.alpha, block, 8);
		at1.decodeBlock(&cl);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC5:
	{
		nv::BlockATI2 at2;

		bear_copy(&at2.x, block, 8);
		bear_copy(&at2.y, block+8, 8);
		at2.decodeBlock(&cl);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	case BearTexturePixelFormat::TPF_BC6:
	{
		nv::BlockBC6 bc6;
		nv::Vector3 color_float[16];

		bear_copy(&bc6.data, block, 16);
		bc6.decodeBlock(color_float);
		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsFloat(color_float[x].x, color_float[x].y, color_float[x].z, 1.f);
		}
		return;
	}
	break;
	case BearTexturePixelFormat::TPF_BC7:
	{
		nv::BlockBC7 bc7;

		bear_copy(&bc7.data, block, 16);
		bc7.decodeBlock(&cl);

		for (uint x = 0; x < 16; x++)
		{
			color[x].SetAsUint8(cl.color(x).r, cl.color(x).g, cl.color(x).b, cl.color(x).a);
		}
	}
	break;
	default:
		break;
	}
#else
BEAR_ASSERT(false);
#endif
	
}

void BearTextureUtils::SetBlock(BearColor(&color)[16], uint8 * data, bsize w, bsize h, bsize x_, bsize y, BearTexturePixelFormat px)
{
#ifdef DEVELOPER_VERSION
	uint8*block = data + ((x_ / 4) + ((w + 3) / 4)*(y / 4))*(px == BearTexturePixelFormat::TPF_BC1 || px == BearTexturePixelFormat::TPF_BC1a || px == BearTexturePixelFormat::TPF_BC4 ? 8 : 16);
	uint8 imagePixel16UInt8[16 * 4];
//	float imagePixel16Float[16 * 4];
	uint16 imagePixel16UInt16[16 * 4];
	switch (px)
	{
	case BearTexturePixelFormat::TPF_BC1:
	{
		nv::CompressorDXT1 compressor;
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, false);

		compOpt.setFormat(nvtt::Format_DXT1);

		float wa[16];
		nv::Vector4 blockColor[16];
		for (bsize x = 0; x < 16; x++)
		{
			wa[x] = 1.f;
			blockColor[x].x = color[x].R32F;
			blockColor[x].y = color[x].B32F;
			blockColor[x].z = color[x].G32F;
			blockColor[x].w = color[x].A32F;
		}
		compressor.compressBlock(blockColor, wa, compOpt.m, block);
	}

	break;
	case BearTexturePixelFormat::TPF_BC1a:
	{
		nv::CompressorDXT1a compressor;
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, false);

		compOpt.setFormat(nvtt::Format_DXT1a);

		nv::ColorBlock blockColor;
		for (uint x = 0; x < 16; x++)
		{
			blockColor.color(x).setRGBA(color[x].R8U, color[x].G8U, color[x].B8U, color[x].A8U );
		}
		compressor.compressBlock(blockColor, nvtt::AlphaMode_Transparency, compOpt.m, block);
	}
	break;
	case BearTexturePixelFormat::TPF_BC2:
	{
		nv::CompressorDXT3 compressor;
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, false);

		compOpt.setFormat(nvtt::Format_DXT1a);

		nv::ColorBlock blockColor;
		for (uint x = 0; x < 16; x++)
		{
			blockColor.color(x).setRGBA(color[x].R8U, color[x].G8U, color[x].B8U, color[x].A8U);
		}
		compressor.compressBlock(blockColor, nvtt::AlphaMode_Transparency, compOpt.m, block);
	}
	break;
	case BearTexturePixelFormat::TPF_BC3:
	{
		nv::CompressorDXT5 compressor;
		nvtt::CompressionOptions compOpt;
		compOpt.setQuality(nvtt::Quality_Highest);
		compOpt.setQuantization(false, false, false);

		compOpt.setFormat(nvtt::Format_DXT1a);

		nv::ColorBlock blockColor;
		for (uint x = 0; x < 16; x++)
		{
			blockColor.color(x).setRGBA(color[x].R8U, color[x].G8U, color[x].B8U, color[x].A8U);
		}
		compressor.compressBlock(blockColor, nvtt::AlphaMode_Transparency, compOpt.m, block);
	}
	break;
	case BearTexturePixelFormat::TPF_BC4:
	{
		nv::ColorBlock blockColor;
		nv::AlphaBlock4x4 alpha1;
		nv::AlphaBlockDXT5 alphaBlock1;
		for (uint x = 0; x < 16; x++)
		{
			blockColor.color(x).setRGBA(color[x].R8U, color[x].G8U, color[x].B8U, color[x].A8U);
		}
		alpha1.init(blockColor, 2);
		nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
		bear_copy(block, &alphaBlock1.u, 8);

	}
	break;
	case BearTexturePixelFormat::TPF_BC5:
	{
		nv::ColorBlock blockColor;
		nv::AlphaBlock4x4 alpha1, alpha2;
		nv::AlphaBlockDXT5 alphaBlock1, alphaBlock2;
		for (uint x = 0; x < 16; x++)
		{
			blockColor.color(x).setRGBA(color[x].R8U, color[x].G8U, color[x].B8U, color[x].A8U);
		}
		alpha1.init(blockColor, 2);
		alpha2.init(blockColor, 1);
		nv::QuickCompress::compressDXT5A(alpha1, &alphaBlock1, 8);
		nv::QuickCompress::compressDXT5A(alpha2, &alphaBlock2, 8);
		bear_copy(block, &alphaBlock1.u, 8);
		bear_copy(block + 8, &alphaBlock2.u, 8);
	}
	break;
	case BearTexturePixelFormat::TPF_BC6:
		for (uint x = 0; x < 16; x++)
		{
			imagePixel16UInt16[x * 4] = floatToHalf(color[x].R32F);
			imagePixel16UInt16[x * 4 + 1] = floatToHalf(color[x].G32F);
			imagePixel16UInt16[x * 4 + 2] = floatToHalf(color[x].B32F);
			imagePixel16UInt16[x * 4 + 3] = floatToHalf(color[x].A32F);

		}
		{

			rgba_surface surface;
			surface.height = static_cast<int32>(h);
			surface.width = static_cast<int32>(w);
			surface.ptr = (uint8*)imagePixel16UInt16;
			/*for (bsize i = 0; i < w*h; i++)
			*(img + i * 4) = 0;*/
			surface.stride = static_cast<int32>(w) * 2 * 4;
			bc6h_enc_settings str;
			GetProfile_bc6h_veryslow(&str);
			CompressBlocksBC6H(&surface, (uint8*)block, &str);
		}
		break;
	case BearTexturePixelFormat::TPF_BC7:
		for (bsize x = 0; x < 16; x++)
		{
			imagePixel16UInt8[x * 4] = color[x].R8U;
			imagePixel16UInt8[x * 4 + 1] = color[x].G8U;
			imagePixel16UInt8[x * 4 + 2] = color[x].B8U;
			imagePixel16UInt8[x * 4 + 3] = color[x].A8U;

		}
		{
			rgba_surface surface;
			surface.height = static_cast<int32>(h);
			surface.width = static_cast<int32>(w);
			surface.ptr = imagePixel16UInt8;
			surface.stride = static_cast<int32>(w) * 4;
			bc7_enc_settings str;
			if (GetCountComp(px) == 4)
				GetProfile_alpha_slow(&str);
			else
				GetProfile_slow(&str);
			CompressBlocksBC7(&surface, (uint8*)block, &str);
		}
		break;
	default:
		break;
	}
#else
BEAR_ASSERT(false);
#endif
}

bool BearTextureUtils::CompressorAsFloat(BearTexturePixelFormat px)
{
	switch (px)
	{
	case TPF_BC6:
		return true;
		break;
	}
	return false;
}

uint8 * BearTextureUtils::TempUncompressor(uint8 * data, bsize w, bsize h, BearTexturePixelFormat px, BearTexturePixelFormat & out_px)
{
	switch (px)
	{
	case TPF_BC1:
		out_px = BearTexturePixelFormat::TPF_R32G32B32F;
		break;
	case TPF_BC1a:
	case TPF_BC2:
	case TPF_BC3:
		out_px = BearTexturePixelFormat::TPF_R8G8B8A8;
		break;
	case TPF_BC4:
		out_px = BearTexturePixelFormat::TPF_R8;
		break;
	case TPF_BC5:
		out_px = BearTexturePixelFormat::TPF_R8G8;
		break;
	case TPF_BC6:
		out_px = BearTexturePixelFormat::TPF_R32G32B32F;
		break;
	case TPF_BC7:
		out_px = BearTexturePixelFormat::TPF_R8G8B8A8;
		break;
	default:
		break;
	}

	uint8*data_out = bear_alloc<uint8>(GetSizeWidth(w, out_px)*h);
	if(data!=0)
	Convert(out_px, px, data_out,data , w, h);
	return data_out;
}

void BearTextureUtils::TempCompress(uint8 * in, uint8 * out, bsize w, bsize h, BearTexturePixelFormat px)
{
	BearTexturePixelFormat in_px;
	switch (px)
	{
	case TPF_BC1:
		in_px = BearTexturePixelFormat::TPF_R32G32B32F;
		break;
	case TPF_BC1a:
	case TPF_BC2:
	case TPF_BC3:
		in_px = BearTexturePixelFormat::TPF_R8G8B8A8;
		break;
	case TPF_BC4:
		in_px = BearTexturePixelFormat::TPF_R8;
		break;
	case TPF_BC5:
		in_px = BearTexturePixelFormat::TPF_R8G8;
		break;
	case TPF_BC6:
		in_px = BearTexturePixelFormat::TPF_R32G32B32F;
		break;
	case TPF_BC7:
		in_px = BearTexturePixelFormat::TPF_R8G8B8A8;
		break;
	default:
		in_px = BearTexturePixelFormat::TPF_R8;
		break;
	}
	if(out!=0)
		Convert(px, in_px,out, in, w, h);
	bear_free(in);
}

