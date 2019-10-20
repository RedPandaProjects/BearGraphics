#include "BearGraphics.hpp"

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription()
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
	m_CRC32 = 0;
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(const BearRenderPipelineDescription & Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
	Copy(Right);
}

BearGraphics::BearRenderPipelineDescription::BearRenderPipelineDescription(BearRenderPipelineDescription && Right)
{
	BearCore::bear_fill(RenderTargets.Formats, 16, 0);
	Swap(Right);
}

bool BearGraphics::BearRenderPipelineDescription::operator<(const BearRenderPipelineDescription & Right) const
{
	if (m_CRC32 == Right.m_CRC32)
	{
		for (bsize i = 0; i < 16; i++)
		{
			if (InputLayout.Elements[i] == Right.InputLayout.Elements[i])
				continue;
			return InputLayout.Elements[i] < Right.InputLayout.Elements[i];
		}
		if (Shaders.Pixel != Right.Shaders.Pixel)return Shaders.Pixel < Right.Shaders.Pixel;
		if (Shaders.Vertex != Right.Shaders.Vertex)return Shaders.Vertex < Right.Shaders.Vertex;
		return BearCore::bear_compare(RenderTargets.Formats, Right.RenderTargets.Formats, 8) < 0;
	}
	return m_CRC32 < Right.m_CRC32;
}

bool BearGraphics::BearRenderPipelineDescription::operator==(const BearRenderPipelineDescription & Right) const
{
	if (m_CRC32 != Right.m_CRC32)return false;
	bool result = true;
	for (bsize i = 0; i < 16; i++)
	{
		result = result&&InputLayout.Elements[i] == Right.InputLayout.Elements[i];
	}
	result = result && Shaders.Pixel == Right.Shaders.Pixel;
	result = result && Shaders.Vertex == Right.Shaders.Vertex;
	result = result && (BearCore::bear_compare(RenderTargets.Formats, Right.RenderTargets.Formats, 8)==0);
	return result;
}

void BearGraphics::BearRenderPipelineDescription::Copy(const BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		InputLayout.Elements[16] = Right.InputLayout.Elements[16];
	BearCore::bear_copy(RenderTargets.Formats, Right.RenderTargets.Formats, 16);
	Shaders.Pixel = Right.Shaders.Pixel;
	Shaders.Vertex = Right.Shaders.Vertex;
}

void BearGraphics::BearRenderPipelineDescription::Swap(BearRenderPipelineDescription & Right)
{
	for (bsize i = 0; i < 16; i++)
		BearCore::bear_swap(InputLayout.Elements[16], Right.InputLayout.Elements[16]);
	BearCore::bear_swap(RenderTargets.Formats, Right.RenderTargets.Formats, 16);
	Shaders.Pixel.swap( Right.Shaders.Pixel);
	Shaders.Pixel.swap( Right.Shaders.Vertex);
}
