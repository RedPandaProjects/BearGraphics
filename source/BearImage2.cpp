#include "BearGraphics.hpp"
#include "BearTextureUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

extern "C"
{
	void* Malloc(bsize a)
	{
		return BearCore::BearMemory::Malloc(a
#ifdef DEBUG
			, "stb_image"
#endif
		);
	}
	void Free(void* a)
	{
		if (!a)return;
		BearCore::BearMemory::Free(a);

	}
	void* Realloc(void* x, bsize n)
	{
		return  BearCore::BearMemory::Realloc(x, n
#ifdef DEBUG
			, "stb_image"
#endif
		);
	}
}
#include "stb_image.h"
#include "stb_image_write.h"
bool BearGraphics::BearImage::LoadFromFile(const bchar * str)
{
	BearCore::BearFileStream stream;
	if (!stream.Open(str))
		return false;
	return LoadFromStream(stream);
}

bool BearGraphics::BearImage::LoadFromStream(const BearCore::BearInputStream & stream)
{
	BearCore::BearMemoryTranslationStream memory(stream);
	return LoadFromBuffer(memory);
}

bool BearGraphics::BearImage::LoadFromBuffer(const BearCore::BearBufferedReader & stream)
{
	Clear();
	int w, h, comp;
	stbi_uc*data1 = stbi_load_from_memory((const stbi_uc*)stream.Begin(), (int)((uint8*)stream.End() - (uint8*)stream.Begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data1) {
		return false;
	}
	Create(w, h);
	BearCore::bear_copy(m_images, data1, BearTextureUtils::GetSizeInMemory(w, h, 1, m_px));
	BearCore::bear_free(data1);
	return true;
}

bool BearGraphics::BearImage::LoadFromFile(bsize depth, const bchar * str)
{
	if (Empty())return false;
	BearCore::BearFileStream stream;
	if (!stream.Open(str))
		return false;
	return LoadFromStream(depth, stream);
}

bool BearGraphics::BearImage::LoadFromStream(bsize depth, const BearCore::BearInputStream & stream)
{
	if (Empty())return false;
	BearCore::BearMemoryTranslationStream memory(stream);
	return LoadFromBuffer(depth, memory);
}

bool BearGraphics::BearImage::LoadFromBuffer(bsize depth, const BearCore::BearBufferedReader & stream)
{
	if (Empty())return false;
	int w, h, comp;
	stbi_uc*data = stbi_load_from_memory((const stbi_uc*)stream.Begin(), (int)((uint8*)stream.End() - (uint8*)stream.Begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data)
	{
		return false;
	}
	Resize(w, h, depth, TPF_R8G8B8A8);
	bsize size = BearTextureUtils::GetSizeInMemory(w, h, m_mips, m_px);
	BearCore::bear_copy(m_images + (depth*size), data, BearTextureUtils::GetSizeInMemory(w, h, 1, m_px));
	BearCore::bear_free(data);
	return true;
}
bool BearGraphics::BearImage::SaveToJpg(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearTextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearTextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));

	return stbi_write_jpg(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 100);
}

bool BearGraphics::BearImage::SaveToPng(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearTextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearTextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));

	return stbi_write_png(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 0);

}

bool BearGraphics::BearImage::SaveToBmp(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearTextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearTextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));
	return stbi_write_bmp(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));

}

bool BearGraphics::BearImage::SaveToTga(const bchar * name, bsize depth)
{
	BEAR_FATALERROR(m_depth > depth, TEXT("Значение глубены [%llu] вышло за пределы [%llu] масива"), depth, m_depth);
	BEAR_FATALERROR(!BearTextureUtils::isCompressor(m_px), TEXT("BlockCompressor нередактируеться"));
	BEAR_FATALERROR(!BearTextureUtils::isFloatPixel(m_px), TEXT("BlockFloat нередактируеться"));
	return stbi_write_tga(*BearCore::BearEncoding::ToANSI(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));

}