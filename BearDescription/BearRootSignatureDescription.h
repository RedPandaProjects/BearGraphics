#pragma once

struct  BearRootSignatureDescription
{
	BearRootSignatureDescription()
	{
		Local = false;
	}
	struct UniformBuffer
	{
		UniformBuffer() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	UniformBuffers[16];

	struct SRVResource
	{
		SRVResource() :Shader(ST_Null), DescriptorType(DT_Image){}
		BearDescriptorType DescriptorType;
		BearShaderType Shader;
	}
	SRVResources[16];
	struct Sampler
	{
		Sampler() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	Samplers[16];
	bool Local;

	inline bool operator== (const BearRootSignatureDescription& Right)const
	{
		if (Local != Right.Local)return false;
		if (memcmp(UniformBuffers, Right.UniformBuffers, 16 * sizeof(UniformBuffer)))return false;
		if (memcmp(SRVResources, Right.SRVResources, 16 * sizeof(UniformBuffer)))return false;
		if (memcmp(Samplers, Right.Samplers, 16 * sizeof(UniformBuffer)))return false;
		return true;
	}
	inline bool operator!= (const BearRootSignatureDescription& Right)const { return !((*this) == Right); }
	inline bool operator<(const BearRootSignatureDescription& Right)const
	{
		if (Local != Right.Local)return Local < Right.Local;
		int result = memcmp(UniformBuffers, Right.UniformBuffers, 16 * sizeof(UniformBuffer));
		if(result!=0)return result<0;
		result = memcmp(SRVResources, Right.SRVResources, 16 * sizeof(UniformBuffer));
		if (result != 0)return result < 0;
		return memcmp(Samplers, Right.Samplers, 16 * sizeof(UniformBuffer)) < 0;
	}
};