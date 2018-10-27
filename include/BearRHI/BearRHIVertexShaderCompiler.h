#pragma once 
namespace BearRHI
{
	class BearRHIVertexShaderCompiler
	{
	public:
		virtual bool compileFromText(const bchar*text,BearCore::BearString&out_error)=0;
		virtual void*getPointerBuffer()=0;
		virtual bsize getSizeBuffer()=0;
	};
}