#pragma once
class BEARGRAPHICS_API BearBottomLevelDescription
{
public:
	BearBottomLevelDescription(){}
	inline ~BearBottomLevelDescription(){}
	BearBottomLevelDescription(const BearBottomLevelDescription& Right) { Copy(Right); }
	BearBottomLevelDescription(BearBottomLevelDescription&& Right) { Swap(Right); }
	inline void Copy(const BearBottomLevelDescription& Right)
	{
		GeometryDescriptions.copy(Right.GeometryDescriptions);
		BuildFlags.copy(Right.BuildFlags);
	}
	inline void Swap(BearBottomLevelDescription& Right)
	{
		GeometryDescriptions.swap(Right.GeometryDescriptions);
		BuildFlags.swap(Right.BuildFlags);
	}
	inline BearBottomLevelDescription& operator=(const BearBottomLevelDescription& Right) { Copy(Right); return*this; }
	inline BearBottomLevelDescription& operator=(BearBottomLevelDescription&& Right) { Swap(Right); return*this; }
	struct GeometryDescription
	{
		GeometryDescription() { Type = BearRaytracingGeometryType::Triangles; }
		BearRaytracingGeometryType Type;
		BearFlags<uint32>  Flags;
		struct TrianglesDescription
		{
			TrianglesDescription() { VertexCount = 0; VertexOffset = 0; VertexFormat = VF_R32G32B32_FLOAT; IndexCount = 0; IndexOffset = 0; }
			BearFactoryPointer<BearRHI::BearRHIVertexBuffer> VertexBuffer;
			bsize VertexCount;
			bsize VertexOffset;
			BearVertexFormat VertexFormat;

			BearFactoryPointer<BearRHI::BearRHIIndexBuffer> IndexBuffer;
			bsize IndexCount;
			bsize IndexOffset;

		} Triangles;
		struct AABBDescription
		{
			AABBDescription() { Stride = 0; Count = 0; Offset = 0; }
			BearFactoryPointer<BearRHI::BearRHIStructuredBuffer> Buffer;
			bsize Stride;
			bsize Count;
			bsize Offset;
		}AABB;
	};
	BearVector<GeometryDescription> GeometryDescriptions;
	BearFlags<uint32>  BuildFlags;
	
};