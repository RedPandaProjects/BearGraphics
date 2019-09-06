#pragma once 
namespace BearGraphics
{
	class BEARGRAPHICS_API BearRenderInterface
	{
		BEAR_CLASS_STATIC(BearRenderInterface);
	public:
		static bool Initialize(const bchar*name);
		static BearFactoryPointer<BearRenderBase::BearRenderContextBase> CreateContext();
		static BearFactoryPointer<BearRenderBase::BearRenderViewportBase> CreateViewport(const BearWindow&Window);
		static void Destroy();
		static bool Empty();
	};
}
