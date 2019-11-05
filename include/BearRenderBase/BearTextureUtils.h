#pragma once
namespace BearGraphics
{
	class BEARGRAPHICS_API BearTextureUtils
	{
	public:
		static void Fill(uint8*data, bsize x, bsize y, bsize mip, const BearCore::BearColor&color, BearGraphics::BearTexturePixelFormat format);
		static void GenerateMip(uint8*dst, uint8*src, bsize w_src, bsize h_src, BearGraphics::BearTexturePixelFormat format);
		static void Scale(uint8*dst, bsize w_dst, bsize h_dst, uint8*src, bsize w_src, bsize h_src, BearGraphics::BearTexturePixelFormat format);
		static void Append(uint8*dst, bsize w_dst, bsize h_dst, bsize x_dst, bsize y_dst, uint8*src, bsize w_src, bsize h_src, BearCore::BearVector4<bsize> squard_src, BearGraphics::BearTexturePixelFormat dst_format, BearGraphics::BearTexturePixelFormat src_format);


		static bsize GetSizeWidth(bsize w,BearGraphics::BearTexturePixelFormat format);
		static bsize GetSizeDepth(bsize w,bsize h, BearGraphics::BearTexturePixelFormat format);
		static bsize GetSizePixel(BearGraphics::BearTexturePixelFormat format);
		static bsize GetCountMips(bsize w, bsize h);
		static bsize GetMip(bsize w, bsize level);
		static uint8*GetPixelUint8(bsize x, bsize y, bsize w, bsize comps,bsize comp_id,uint8*data);
		static float*GetPixelFloat(bsize x, bsize y, bsize w, bsize comps, bsize comp_id, uint8*data);
		static bool isFloatPixel(BearGraphics::BearTexturePixelFormat format);
		static bool isCompressor(BearGraphics::BearTexturePixelFormat format);
		static bsize GetSizeInMemory(bsize w, bsize h, bsize mips, BearGraphics::BearTexturePixelFormat format);
		static void Convert( BearGraphics::BearTexturePixelFormat dst_format, BearGraphics::BearTexturePixelFormat src_format,uint8*dst,uint8*src,bsize w,bsize h);
		static bsize GetCountBlock(bsize w);
		static bsize GetSizeBlock(BearGraphics::BearTexturePixelFormat format);
		static uint8 GetCountComp(BearGraphics::BearTexturePixelFormat format);
		static uint8*GetImage(uint8*data, bsize w, bsize h, bsize mips,bsize depth, bsize mip, BearGraphics::BearTexturePixelFormat format);

		static void  GetPixel(BearCore::BearColor&color,uint8*data,bsize x,bsize y, bsize depth, bsize w, bsize h, bsize mips, BearGraphics::BearTexturePixelFormat format);
		static void  SetPixel(const BearCore::BearColor&color, uint8*data, bsize x, bsize y, bsize depth, bsize w, bsize h, bsize mips, BearGraphics::BearTexturePixelFormat format);
	private:
		static void ScaleFloat(uint8*dst, bsize w_dst, bsize h_dst, uint8*src, bsize w_src, bsize h_src, uint8 comp);
		static void ScaleUint8(uint8*dst, bsize w_dst, bsize h_dst, uint8*src, bsize w_src, bsize h_src, uint8 comp);


		static void GenerateMipFloat(uint8*dst, uint8*src, bsize w_src, bsize h_src, bsize comps);
		static void GenerateMipUint8(uint8*dst, uint8*src, bsize w_src, bsize h_src,bsize comps);

		static void FloatPixelToUint8(uint8*dst, float*src, uint8 comp_dst, uint8 comp_src);
		static void FloatPixelToFloat(float*dst, float*src, uint8 comp_dst, uint8 comp_src);
		static void Uint8PixelToFloat( float*dst, uint8*src, uint8 comp_dst, uint8 comp_src);
		static void Uint8PixelToUint8(uint8*dst, uint8*src, uint8 comp_dst, uint8 comp_src);

		static void FloatPixelToHalf4(uint16*dst, float*src, uint8 comp_src);
		static void Uint8PixelToHalf4(uint16*dst, uint8*src,  uint8 comp_src);

		static void SwapRB(uint32&a);

		static void FillUint8(uint8*data, bsize x, bsize y, const BearCore::BearColor&color, BearGraphics::BearTexturePixelFormat format);
		static void FillFloat(uint8*data, bsize x, bsize y, const BearCore::BearColor&color, BearGraphics::BearTexturePixelFormat format);

		static void Uint8ToHalf4(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_src);
		static void Uint8ToFloat(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src);
		static void Uint8ToUint8(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src);
		static void Uint8ToCompressor(uint8*dst, uint8*src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor, uint8 comp_src);

		static void FloatToHalf4(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_src);
		static void FloatToUint8(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src);
		static void FloatToFloat(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, uint8 comp_src);
		static void FloatToCompressor(uint8*dst, uint8*src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor, uint8 comp_src);

		static void CompressorToCompressor(uint8*dst, uint8*src, bsize w, bsize h, BearGraphics::BearTexturePixelFormat compressor_dst, BearGraphics::BearTexturePixelFormat compressor_src);
		static void CompressorToUint8(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, BearGraphics::BearTexturePixelFormat compressor);
		static void CompressorToFloat(uint8*dst, uint8*src, bsize w, bsize h, uint8 comp_dst, BearGraphics::BearTexturePixelFormat compressor);

		static void*StartCompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h);
		static void EndCompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h,void*in,void*out);

		static void*StartDecompressor(BearGraphics::BearTexturePixelFormat compressor, bsize w, bsize h,void*in);
		static void EndDecompressor(void*in);

		static void GetBlock(BearCore::BearColor(&color)[16], uint8*data, bsize w, bsize h, bsize x, bsize y, BearGraphics::BearTexturePixelFormat px);
		static void SetBlock(BearCore::BearColor(&color)[16], uint8*data, bsize w, bsize h, bsize x, bsize y, BearGraphics::BearTexturePixelFormat px);
		static bool CompressorAsFloat(BearGraphics::BearTexturePixelFormat px);
		static uint8*TempUncompressor(uint8*data, bsize w, bsize h, BearGraphics::BearTexturePixelFormat px, BearGraphics::BearTexturePixelFormat&out_px);
		static void TempCompress(uint8*in, uint8*out, bsize w, bsize h, BearGraphics::BearTexturePixelFormat px);
	};
}