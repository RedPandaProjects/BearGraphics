#include "BearGraphics.hpp"

void BearGraphics::BearRenderAccelerationStructuresDescription::Copy(const BearRenderAccelerationStructuresDescription & Right)
{
	VertexFormat = Right.VertexFormat;
	Buffers.Index.copy(Right.Buffers.Index);
	Buffers.Vertex.copy(Right.Buffers.Vertex);
}

void BearGraphics::BearRenderAccelerationStructuresDescription::Swap(BearRenderAccelerationStructuresDescription & Right)
{
	BearCore::bear_swap(VertexFormat, Right.VertexFormat);
	Buffers.Index.swap(Right.Buffers.Index);
	Buffers.Vertex.swap(Right.Buffers.Vertex);
}
