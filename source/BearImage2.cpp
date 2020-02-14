#include "BearGraphics.hpp"
#include "BearRHI/BearTextureUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

extern "C"
{
	void* Malloc(bsize a)
	{
		return BearMemory::Malloc(a
#ifdef DEBUG
			, "stb_image"
#endif
		);
	}
	void Free(void* a)
	{
		if (!a)return;
		BearMemory::Free(a);

	}
	void* Realloc(void* x, bsize n)
	{
		return  BearMemory::Realloc(x, n
#ifdef DEBUG
			, "stb_image"
#endif
		);
	}
}
#include "stb_image.h"
#include "stb_image_write.h"
bool BearImage::LoadFromFile(const bchar * str)
{
	BearFileStream stream;
	if (!stream.Open(str))
		return false;
	return LoadFromStream(stream);
}

bool BearImage::LoadFromStream(const BearInputStream & stream)
{
	BearMemoryStream memory(stream);
	return LoadFromBuffer(memory);
}

bool BearImage::LoadFromBuffer(const BearBufferedReader & stream)
{
	Clear();
	int w, h, comp;
	stbi_uc*data1 = stbi_load_from_memory((const stbi_uc*)stream.Begin(), (int)((uint8*)stream.End() - (uint8*)stream.Begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data1) {
		return false;
	}
	Create(w, h);
	bear_copy(m_images, data1, BearTextureUtils::GetSizeInMemory(w, h, 1, m_px));
	bear_free(data1);
	return true;
}

bool BearImage::LoadFromFile(bsize depth, const bchar * str)
{
	if (!Empty())return false;
	BearFileStream stream;
	if (!stream.Open(str))
		return false;
	return LoadFromStream(depth, stream);
}

bool BearImage::LoadFromStream(bsize depth, const BearInputStream & stream)
{
	if (!Empty())return false;
	BearMemoryStream memory(stream);
	return LoadFromBuffer(depth, memory);
}

bool BearImage::LoadFromBuffer(bsize depth, const BearBufferedReader & stream)
{
	if (!Empty())return false;
	int w, h, comp;
	stbi_uc*data = stbi_load_from_memory((const stbi_uc*)stream.Begin(), (int)((uint8*)stream.End() - (uint8*)stream.Begin()), &w, &h, &comp, STBI_rgb_alpha);
	if (!data)
	{
		return false;
	}
	Resize(w, h, depth, TPF_R8G8B8A8);
	bsize size = BearTextureUtils::GetSizeInMemory(w, h, m_mips, m_px);
	bear_copy(m_images + (depth*size), data, BearTextureUtils::GetSizeInMemory(w, h, 1, m_px));
	bear_free(data);
	return true;
}
bool BearImage::SaveToJpg(const bchar * name, bsize depth)
{
	BEAR_ASSERT(m_depth > depth);
	BEAR_ASSERT(!BearTextureUtils::isCompressor(m_px));
	BEAR_ASSERT(!BearTextureUtils::isFloatPixel(m_px));
#ifdef UNICODE
	return stbi_write_jpg(*BearEncoding::ToAnsi(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 100);

#else
	return stbi_write_jpg(name, static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 100);

#endif
}

bool BearImage::SaveToPng(const bchar * name, bsize depth)
{
	BEAR_ASSERT(m_depth > depth);
	BEAR_ASSERT(!BearTextureUtils::isCompressor(m_px));
	BEAR_ASSERT(!BearTextureUtils::isFloatPixel(m_px));
#ifdef UNICODE
	return stbi_write_png(*BearEncoding::ToAnsi(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 0);
#else
	return stbi_write_png(name, static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px), 0);

#endif
}

bool BearImage::SaveToBmp(const bchar * name, bsize depth)
{
	BEAR_ASSERT(m_depth > depth);
	BEAR_ASSERT(!BearTextureUtils::isCompressor(m_px));
	BEAR_ASSERT(!BearTextureUtils::isFloatPixel(m_px));
#ifdef UNICODE
	return stbi_write_bmp(*BearEncoding::ToAnsi(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));
#else
	return stbi_write_bmp(name, static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));
#endif
}

bool BearImage::SaveToTga(const bchar * name, bsize depth)
{
	BEAR_ASSERT(m_depth > depth);
	BEAR_ASSERT(!BearTextureUtils::isCompressor(m_px));
	BEAR_ASSERT(!BearTextureUtils::isFloatPixel(m_px));
#ifdef UNICODE
	return stbi_write_tga(*BearEncoding::ToAnsi(name), static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));
#else
	return stbi_write_tga(name, static_cast<int>(m_w), static_cast<int>(m_h), static_cast<int>(BearTextureUtils::GetCountComp(m_px)), m_images + depth * BearTextureUtils::GetSizeInMemory(m_w, m_h, m_mips, m_px));

#endif
}