#pragma once
class BEARGRAPHICS_API BearRenderInterface
{
	BEAR_CLASS_STATIC(BearRenderInterface);
public:
	static bool Initialize(const bchar* name);
	static BearFactoryPointer<BearRHI::BearRHIViewport> CreateViewport(BearWindow&Window,const BearRenderViewportDescription& Description, bool Vsync=false);
	static BearFactoryPointer<BearRHI::BearRHIContext> CreateContext();
	static bool RTXSupport();
	static void Destroy();
	static bool Empty();
};