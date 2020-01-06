#pragma once

struct  BearRootSignatureDescription
{

	struct UniformBuffer
	{
		UniformBuffer() :Shader(ST_Null) {}
		BearShaderType Shader;
	}
	UniformBuffers[16];

};