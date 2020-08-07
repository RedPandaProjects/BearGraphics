#pragma once
class BEARGRAPHICS_API BearRayTracingShaderTableDescription
{
public:
	BearRayTracingShaderTableDescription(){}
	inline ~BearRayTracingShaderTableDescription(){}
	BearRayTracingShaderTableDescription(const BearRayTracingShaderTableDescription& Right) { Copy(Right); }
	BearRayTracingShaderTableDescription(BearRayTracingShaderTableDescription&& Right) { Swap(Right); }
	inline void Copy(const BearRayTracingShaderTableDescription& Right)
	{
		Name = Right.Name;
		Pipeline.copy(Right.Pipeline);
	}
	inline void Swap(BearRayTracingShaderTableDescription& Right)
	{
		Name.swap(Right.Name);
		Pipeline.swap(Right.Pipeline);
	}
	inline BearRayTracingShaderTableDescription& operator=(const BearRayTracingShaderTableDescription& Right) { Copy(Right); return*this; }
	inline BearRayTracingShaderTableDescription& operator=(BearRayTracingShaderTableDescription&& Right) { Swap(Right); return*this; }
	
	BearFactoryPointer<BearRHI::BearRHIPipelineRayTracing>	Pipeline;
	BearStringConteniarUnicode								Name;
};