#pragma once 
namespace BearRHI
{
	class BearRHIDefaultManager
	{
	public:
		virtual const bchar*GetPixelShader(BearGraphics::BearDefaultPixelShader type)=0;
		virtual const bchar*GetVertexShader(BearGraphics::BearDefaultVertexShader type)=0;
	};
}