#include "BearGraphics.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

extern "C"
{
	void* Malloc(bsize a)
	{
		return BearCore::BearMemory::Malloc(a, "stb_image");
	}
	void Free(void* a)
	{
		if (!a)return;
		BearCore::BearMemory::Free(a);

	}
	void* Realloc(void* x, bsize n)
	{
		return  BearCore::BearMemory::Realloc(x, n, "stb_image");
	}
}
#include "stb_image.h"
#include "stb_image_write.h"
bool BearGraphics::BearImage::loadFromFile(const bchar * str)
{
	BearCore::BearFileStream stream;
	if (!stream.open(str))
		return false;
	return loadFromInput(stream);
}

bool BearGraphics::BearImage::loadFromInput(const BearCore::BearInputStream & stream)
{
	BearCore::BearMemoryTranslationStream memory(stream);
	return loadFromBuffer(memory);
}

bool BearGraphics::BearImage::loadFromBuffer(const BearCore::BearBufferedReader & stream)
{
	clear();
	int w, h, comp;
	stbi_uc*data1 = stbi_load_from_memory((const stbi_uc*)stream.begin(), (int)((uint8*)stream.end() - (uint8*)stream.begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data1) {
		return false;
	}
	create(w, h);
	BearCore::bear_copy(m_images, data1, BearRHI::BearRHITexture2D::GetSizeInMemory(w, h, 1, m_px));
	BearCore::bear_free(data1);
	return true;
}

bool BearGraphics::BearImage::loadFromFile(bsize depth, const bchar * str)
{
	if (empty())return false;
	BearCore::BearFileStream stream;
	if (!stream.open(str))
		return false;
	return loadFromInput(depth, stream);
}

bool BearGraphics::BearImage::loadFromInput(bsize depth, const BearCore::BearInputStream & stream)
{
	if (empty())return false;
	BearCore::BearMemoryTranslationStream memory(stream);
	return loadFromBuffer(depth, memory);
}

bool BearGraphics::BearImage::loadFromBuffer(bsize depth, const BearCore::BearBufferedReader & stream)
{
	if (empty())return false;
	int w, h, comp;
	stbi_uc*data = stbi_load_from_memory((const stbi_uc*)stream.begin(), (int)((uint8*)stream.end() - (uint8*)stream.begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data)
	{
		return false;
	}
	resize(w, h, depth, TPF_R8G8B8A8);
	bsize size = BearRHI::BearRHITexture2D::GetSizeInMemory(w, h, m_mips, m_px);
	BearCore::bear_copy(m_images + (depth*size), data, BearRHI::BearRHITexture2D::GetSizeInMemory(w, h, 1, m_px));
	BearCore::bear_free(data);
	return true;
}
bool BearGraphics::BearImage::saveToJpg(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));

	return stbi_write_jpg(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearRHI::BearRHITextureUtils::GetCountComp(m_px)), m_images + depth * BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 100);
}

bool BearGraphics::BearImage::saveToPng(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));

	return stbi_write_png(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearRHI::BearRHITextureUtils::GetCountComp(m_px)), m_images + depth * BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 0);

}

bool BearGraphics::BearImage::saveToBmp(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));
	return stbi_write_bmp(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearRHI::BearRHITextureUtils::GetCountComp(m_px)), m_images + depth * BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));

}

bool BearGraphics::BearImage::saveToTga(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearRHI::BearRHITextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));
	return stbi_write_tga(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearRHI::BearRHITextureUtils::GetCountComp(m_px)), m_images + depth * BearRHI::BearRHITextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));

}