#pragma once 
namespace BearGraphics
{

	class BEARGRAPHICS_API BearRenderAccelerationStructuresDescription
	{
	public:
		BearRenderAccelerationStructuresDescription():VertexFormat(RTVF_R32G32B32_FLOAT){}
		BearRenderAccelerationStructuresDescription(const BearRenderAccelerationStructuresDescription&Right) :VertexFormat(RTVF_R32G32B32_FLOAT) { Copy(Right); }
		BearRenderAccelerationStructuresDescription(BearRenderAccelerationStructuresDescription&&Right) :VertexFormat(RTVF_R32G32B32_FLOAT) { Swap(Right); }
		inline ~BearRenderAccelerationStructuresDescription() {}

		void Copy(const BearRenderAccelerationStructuresDescription&Right);
		void Swap(BearRenderAccelerationStructuresDescription&Right);
		inline BearRenderAccelerationStructuresDescription&operator=(const BearRenderAccelerationStructuresDescription&Right) { Copy(Right); return*this; }
		inline BearRenderAccelerationStructuresDescription&operator=(BearRenderAccelerationStructuresDescription&&Right) { Swap(Right); return*this; }

		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase> Index;
			BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase> Vertex;
		}Buffers;
	
		BearRTXVertexFormat VertexFormat;

	};
}
