#pragma once 
namespace BearGraphics
{
	struct BearRenderDispatchRaysDescription
	{
		BearRenderDispatchRaysDescription() {}

		BearRenderDispatchRaysDescription(const BearRenderDispatchRaysDescription&Right) { Copy(Right); }
		BearRenderDispatchRaysDescription(BearRenderDispatchRaysDescription&&Right) { Swap(Right); }
		inline ~BearRenderDispatchRaysDescription() {}
		void Copy(const BearRenderDispatchRaysDescription&Right);
		void Swap(BearRenderDispatchRaysDescription&Right);
		inline BearRenderDispatchRaysDescription&operator=(const BearRenderDispatchRaysDescription&Right) { Copy(Right); return*this; }
		inline BearRenderDispatchRaysDescription&operator=(BearRenderDispatchRaysDescription&&Right) { Swap(Right); return*this; }

		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
			bsize Size;
		}		RayGeneration;
		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
			bsize Size;
			bsize Stride;
		}Miss;
		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
			bsize Size;
			bsize Stride;
		}HitGroup;
		struct
		{
			BearFactoryPointer<BearRenderBase::BearRenderUniformBufferBase> Buffer;
			bsize Size;
			bsize Stride;
		} Callable;

		bsize Width;
		bsize Height;
		bsize Depth;
	};
}
