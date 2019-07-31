#include "BearGraphics.hpp"
#include "dds.h"
#pragma warning(disable:4005)
#include "directx/DXGI.h"
static void maskShiftAndSize(bsize mask, uint32 * shift, uint32 * size)
{
	if (!mask)
	{
		*shift = 0;
		*size = 0;
		return;
	}

	*shift = 0;
	while ((mask & 1) == 0) {
		++(*shift);
		mask >>= 1;
	}

	*size = 0;
while ((mask & 1) == 1) {
	++(*size);
	mask >>= 1;
}
}

static uint32 ñonvertÑolor(uint32 c, uint32 inbits, uint32 outbits)
{
	if (inbits == 0)
	{
		return 0;
	}
	else if (inbits >= outbits)
	{
		return c >> (inbits - outbits);
	}
	else
	{
		return (c << (outbits - inbits)) | ñonvertÑolor(c, inbits, outbits - inbits);
	}
}
bool BearGraphics::BearImage::LoadDDSFromStream(const BearCore::BearInputStream & stream)
{
	Clear();

	if (stream.ReadUint32() == MAKEFOURCC('D', 'D', 'S', ' '))
	{
		bsize size = stream.ReadUint32();
		DDS_HEADER header;
		BearCore::bear_fill(header);
		stream.Seek(4);
		if (size > sizeof(DDS_HEADER) || size < 4)
			return false;

		stream.Read(&header, size);
		if (!(header.dwHeaderFlags&DDSD_WIDTH) || !(header.dwHeaderFlags&DDSD_HEIGHT) || !(header.dwHeaderFlags&DDSD_PIXELFORMAT))
			return false;
		m_depth = header.dwHeaderFlags&DDSD_DEPTH ? header.dwDepth : 1;
		m_mips = header.dwHeaderFlags&DDSD_MIPMAPCOUNT ? header.dwMipMapCount : 1;
		m_h = header.dwHeight;
		m_w = header.dwWidth;
		if (m_mips==0)
		{
			Clear();
			return false;
		}
		if (header.ddspf.dwFlags != DDS_FOURCC)
		{
			bool alpha = header.ddspf.dwFlags&(DDS_RGBA&(~DDS_RGB));
			if (header.ddspf.dwRGBBitCount % 8 || header.ddspf.dwRGBBitCount > 64)
			{
				Clear();
				return false;
			}
			bsize byte_size_pixel = header.ddspf.dwRGBBitCount / 8;
			uint32 size_bit[4], shift_bit[4];
			for (bsize x = 0; x < 4; x++)
				maskShiftAndSize(header.ddspf.dwBitsMask[x], shift_bit + x, size_bit + x);
			if (header.ddspf.dwRBitMask&&header.ddspf.dwGBitMask&&header.ddspf.dwBBitMask)
				m_px = alpha ? TPF_R8G8B8A8 : TPF_R8G8B8;
			else	if (header.ddspf.dwRBitMask&&header.ddspf.dwGBitMask)
				m_px = TPF_R8G8;
			else
				m_px = TPF_R8;
			uint8 coutComp = BearRHI::BearRHITextureUtils::GetCountComp(m_px);
			uint32 pixel = 0;
			Create(m_w, m_h, m_mips, m_depth, m_px);
			for (bsize d = 0; d < m_depth; d++)
			{
				for (bsize m = 0; m < m_mips; m++)
				{
					bsize h = BearRHI::BearRHITextureUtils::GetMip(m_h, m);
					bsize w = BearRHI::BearRHITextureUtils::GetMip(m_w, m);
					uint8*data = BearRHI::BearRHITextureUtils::GetImage(m_images, m_w, m_h, m_mips, d, m, m_px);
					for (bsize x = 0; x < w*h; x++)
					{
						stream.Read(&pixel, byte_size_pixel);
						for (bsize a = 0; a < coutComp; a++)
						{
							*BearRHI::BearRHITextureUtils::GetPixelUint8(x, 0, 0, coutComp, a, data)= static_cast<uint8>(ñonvertÑolor((pixel & header.ddspf.dwBitsMask[a]) >> shift_bit[a], size_bit[a], 8));;
						}
					}
				}
			}
			return true;
		}
		else
		{

			
			if (header.ddspf.dwFourCC == MAKEFOURCC('D', 'X', '1', '0'))
			{
				if (size + sizeof(DDSHeader10) == sizeof(DDS_HEADER))
				{
					stream.Seek(4);
					stream.Read(&header, size += sizeof(DDSHeader10));
				}
				switch (header.Header10.dxgiFormat)
				{
				case DXGI_FORMAT_R32G32B32A32_FLOAT:
					m_px = TPF_R32G32B32A32F;
					break;
				case DXGI_FORMAT_R32G32B32_FLOAT:
					m_px = TPF_R32G32B32F;
					break;
				case DXGI_FORMAT_R32G32_FLOAT:
					m_px = TPF_R32G32F;
					break;
				case DXGI_FORMAT_R32_FLOAT:
					m_px = TPF_R32F;
					break;
				case DXGI_FORMAT_R8G8B8A8_UNORM:
					m_px = TPF_R8G8B8A8;
					break;
				case DXGI_FORMAT_R8G8_UNORM:
					m_px = TPF_R8G8;
					break;
				case DXGI_FORMAT_R8_UNORM:
					m_px = TPF_R8;
					break;
				case DXGI_FORMAT_BC1_UNORM:
					m_px = TPF_BC1;
					break;
				case DXGI_FORMAT_BC2_UNORM:
					m_px = TPF_BC2;
					break;
				case DXGI_FORMAT_BC3_UNORM:
					m_px = TPF_BC3;
					break;
				case DXGI_FORMAT_BC4_UNORM:
					m_px = TPF_BC4;
					break;
				case DXGI_FORMAT_BC5_UNORM:
					m_px = TPF_BC5;
					break;
				case DXGI_FORMAT_BC6H_SF16:
					m_px = TPF_BC6;
					break;
				case DXGI_FORMAT_BC7_UNORM:
					m_px = TPF_BC7;
					break;
				default:
					Clear();
					return false;
				}
			}
			else
			{
				switch (header.ddspf.dwFourCC)
				{
				case  MAKEFOURCC('D', 'X', 'T', '1'):
					m_px = TPF_BC1;
					break;
				case  MAKEFOURCC('D', 'X', 'T', '2'):
				case  MAKEFOURCC('D', 'X', 'T', '3'):
					m_px = TPF_BC2;
					break;
				case  MAKEFOURCC('D', 'X', 'T', '4'):
				case  MAKEFOURCC('D', 'X', 'T', '5'):
					m_px = TPF_BC3;
					break;
				case  MAKEFOURCC('A', 'T', 'I', '1'):
					m_px = TPF_BC4;
					break;
				case  MAKEFOURCC('A', 'T', 'I', '2'):
					m_px = TPF_BC5;
					break;
				default:
					Clear();
					return false;
				}
			}
			Create(m_w, m_h, m_mips , m_depth, m_px);
			stream.Read(m_images, GetSizeInMemory());
			return true;
		}
		
	}
	return false;
}
bool BearGraphics::BearImage::LoadDDSFromFile(const bchar * str)
{
	BearCore::BearFileStream stream;
	if (!stream.Open(str))
		return false;
	return LoadDDSFromStream(stream);
}
bool BearGraphics::BearImage::LoadDDSFromBuffer(const BearCore::BearBufferedReader & stream)
{
	return LoadDDSFromStream(stream);
}


bool BearGraphics::BearImage::SaveToDds(const bchar * name)
{
	BearCore::BearFileStream dds;
	if (!dds.Open(name, BearCore::BearFileStream::M_Write))
		return false;
	dds.Seek(0);
	DDS_HEADER ddsh;
	BearCore::bear_fill(ddsh);
	ddsh.dwSize = sizeof(ddsh) - sizeof(ddsh.Header10);
	ddsh.dwHeaderFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT | DDSD_DEPTH;
	ddsh.dwWidth = static_cast<DWORD>(m_w);
	ddsh.dwHeight = static_cast<DWORD>(m_h);
	ddsh.dwMipMapCount = static_cast<DWORD>(m_mips);
	ddsh.dwDepth = static_cast<DWORD>(m_depth);
	char*ddst = "DDS ";
	dds.Write(ddst, 4);
	switch (m_px)
	{
	case BearGraphics::TPF_R8:
		ddsh.ddspf = DDSPF_R8G8B8;
		ddsh.ddspf.dwBBitMask = 0;
		ddsh.ddspf.dwGBitMask = 0;
		ddsh.ddspf.dwRBitMask = 255;
		ddsh.ddspf.dwRGBBitCount = 8;
		break;
	case BearGraphics::TPF_R8G8:
		ddsh.ddspf = DDSPF_R8G8B8;
		ddsh.ddspf.dwBBitMask = 0;
		ddsh.ddspf.dwGBitMask = 0xFF<<8;
		ddsh.ddspf.dwRBitMask = 0xFF;
		ddsh.ddspf.dwRGBBitCount =16;
		break;
	case BearGraphics::TPF_R8G8B8:
		ddsh.ddspf = DDSPF_R8G8B8;
		ddsh.ddspf.dwBBitMask = 0xFF << 16;
		ddsh.ddspf.dwGBitMask = 0xFF << 8;
		ddsh.ddspf.dwRBitMask = 0xFF;
		ddsh.ddspf.dwRGBBitCount = 24;
		break;
	case BearGraphics::TPF_R8G8B8A8:
		ddsh.ddspf = DDSPF_A8R8G8B8;
		ddsh.ddspf.dwBBitMask = 0xFF << 16;
		ddsh.ddspf.dwGBitMask = 0xFF << 8;
		ddsh.ddspf.dwRBitMask = 0xFF;
		ddsh.ddspf.dwABitMask = DWORD(0xFF << 24);
		ddsh.ddspf.dwRGBBitCount = 32;
		break;
	case BearGraphics::TPF_R32F:
		ddsh.ddspf = DDSPF_DX10;
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_R32_FLOAT;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	case BearGraphics::TPF_R32G32F:
		ddsh.ddspf = DDSPF_DX10;
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	case BearGraphics::TPF_R32G32B32F:
		ddsh.ddspf = DDSPF_DX10;
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	case BearGraphics::TPF_R32G32B32A32F:
		ddsh.ddspf = DDSPF_DX10;
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	case BearGraphics::TPF_DXT_1:
	case BearGraphics::TPF_DXT_1_alpha:
		ddsh.ddspf = DDSPF_DXT1;
		break;
	case BearGraphics::TPF_DXT_3:
		ddsh.ddspf = DDSPF_DXT3;
		break;
	case BearGraphics::TPF_DXT_5:
		ddsh.ddspf = DDSPF_DXT5;
		break;
	case BearGraphics::TPF_BC4:
		ddsh.ddspf = DDSPF_ATI1;
		break;
	case BearGraphics::TPF_BC5:
		ddsh.ddspf = DDSPF_ATI2;
		break;
	case BearGraphics::TPF_BC6:
		ddsh.ddspf = DDSPF_DX10;			
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_BC6H_UF16;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	case BearGraphics::TPF_BC7:
		ddsh.ddspf = DDSPF_DX10;
		ddsh.Header10.dxgiFormat = DXGI_FORMAT_BC7_UNORM;
		ddsh.Header10.arraySize = static_cast<DWORD>(m_depth);
		ddsh.Header10.resourceDimension = 3;
		break;
	default:
		return false;
	}
	
	dds.Write(&ddsh, ddsh.dwSize + (ddsh.ddspf.dwFourCC == MAKEFOURCC('D', 'X', '1', '0') ? sizeof(ddsh.Header10) : 0));
	dds.Write(m_images, BearRHI::BearRHITexture2D::GetSizeInMemory(m_w, m_h, m_mips, m_px)*m_depth);
	dds.Close();
	return true;
}