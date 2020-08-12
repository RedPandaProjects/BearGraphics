#pragma once

struct  BearRootSignatureDescription
{
	BearRootSignatureDescription()
	{
		Local = false;
	}
	struct UniformBuffer
	{
		UniformBuffer() :Shader(BearShaderType::Null) {}
		BearShaderType Shader;
	}
	UniformBuffers[16];

	struct SRVResource
	{
		SRVResource() :Shader(BearShaderType::Null), DescriptorType(BearSRVDescriptorType::Image){}
		BearSRVDescriptorType DescriptorType;
		BearShaderType Shader;
	}
	SRVResources[16];
	struct Sampler
	{
		Sampler() :Shader(BearShaderType::Null) {}
		BearShaderType Shader;
	}
	Samplers[16];

	struct UAVResource
	{
		UAVResource() :Shader(BearShaderType::Null), DescriptorType(BearUAVDescriptorType::Image) {}
		BearUAVDescriptorType DescriptorType;
		BearShaderType Shader;
	}
	UAVResources[16];

	bool Local;

	inline bool operator== (const BearRootSignatureDescription& Right)const
	{
		if (Local != Right.Local)return false;
		if (memcmp(UniformBuffers, Right.UniformBuffers, 16 * sizeof(UniformBuffer)))return false;
		if (memcmp(SRVResources, Right.SRVResources, 16 * sizeof(SRVResource)))return false;
		if (memcmp(Samplers, Right.Samplers, 16 * sizeof(Sampler)))return false;
		if (memcmp(UAVResources, Right.UAVResources, 16 * sizeof(UAVResource)))return false;
		return true;
	}
	inline bool operator!= (const BearRootSignatureDescription& Right)const { return !((*this) == Right); }
	inline bool operator<(const BearRootSignatureDescription& Right)const
	{
		if (Local != Right.Local)return Local < Right.Local;
		int result = memcmp(UniformBuffers, Right.UniformBuffers, 16 * sizeof(UniformBuffer));
		if(result!=0)return result<0;
		result = memcmp(SRVResources, Right.SRVResources, 16 * sizeof(SRVResource));
		if (result != 0)return result < 0;
		result = memcmp(UAVResources, Right.UAVResources, 16 * sizeof(UAVResource));
		if (result != 0)return result < 0;
		return memcmp(Samplers, Right.Samplers, 16 * sizeof(Sampler)) < 0;
	}
};