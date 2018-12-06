#pragma once 
namespace BearRHI
{
	class BearRHIVertexShaderCompiler
	{
	public:
		virtual bool CompileFromText(const bchar*text,BearCore::BearString&out_error)=0;
		virtual void*GetPointerBuffer()=0;
		virtual bsize GetSizeBuffer()=0;
	};
}