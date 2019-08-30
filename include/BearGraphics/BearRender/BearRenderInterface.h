#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearRenderInterface
	{
	public:
		static bool Initialize(const bchar*name);
		static void Destroy();
	};
}
