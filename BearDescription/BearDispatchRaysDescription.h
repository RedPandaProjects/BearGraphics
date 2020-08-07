#pragma once
class BEARGRAPHICS_API BearDispatchRaysDescription
{
public:
	BearDispatchRaysDescription()
	{
		Depth = 1;
		Width = 1;
		Height = 1;
	}
	inline ~BearDispatchRaysDescription() {}
	BearDispatchRaysDescription(const BearDispatchRaysDescription& Right) { Copy(Right); }
	BearDispatchRaysDescription(BearDispatchRaysDescription&& Right) { Swap(Right); }
	inline void Copy(const BearDispatchRaysDescription& Right)
	{
		RayGeneration.copy(Right.RayGeneration);
		Miss.copy(Right.Miss);
		HitGroup.copy(Right.HitGroup);
		Depth = Right.Depth;
		Width = Right.Width;
		Height = Right.Height;
	}
	inline void Swap(BearDispatchRaysDescription& Right)
	{
		RayGeneration.swap(Right.RayGeneration);
		Miss.swap(Right.Miss);
		HitGroup.swap(Right.HitGroup);
		bear_swap(Depth, Right.Depth);
		bear_swap(Width , Right.Width);
		bear_swap(Height , Right.Height);
	}
	inline BearDispatchRaysDescription& operator=(const BearDispatchRaysDescription& Right) { Copy(Right); return*this; }
	inline BearDispatchRaysDescription& operator=(BearDispatchRaysDescription&& Right) { Swap(Right); return*this; }

	BearFactoryPointer<BearRHI::BearRHIRayTracingShaderTable>	RayGeneration;
	BearFactoryPointer<BearRHI::BearRHIRayTracingShaderTable>	Miss;
	BearFactoryPointer<BearRHI::BearRHIRayTracingShaderTable>	HitGroup;

	bsize Depth;
	bsize Width;
	bsize Height;

};