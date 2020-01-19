#pragma once

struct  BearRootSignatureDescription
{

	struct UniformBuffer
	{
		UniformBuffer() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	UniformBuffers[16];

	struct SRVResource
	{
		SRVResource() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	SRVResources[16];
	struct Sampler
	{
		Sampler() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	Samplers[16];
};