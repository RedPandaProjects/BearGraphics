#include "BearGraphics.hpp"

static void(*FInitialize)(void);
static void(*FDestroy)(void);
BEARPROJECT_EXPORT BearRenderBase::BearRenderFactoryBase*GRenderFactoty;
bool BearGraphics::BearRenderInterface::Initialize(const bchar * name)
{
	Destroy();
	if (!BearCore::BearProjectTool::CheckProject(name))
	{
		return false;
	}
	FInitialize = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RenderInitialize"));
	FDestroy = BearCore::BearProjectTool::GetFunctionInProject<void(*)(void)>(name, TEXT("RenderDestroy"));
	if (!FInitialize || !FDestroy)return false;
	FInitialize();
	if (!GRenderFactoty)
	{
		Destroy();
		return false;

	}
	return true;
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderContextBase> BearGraphics::BearRenderInterface::CreateContext()
{
	if(Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderContextBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderContextBase>(GRenderFactoty->CreateContext());
}

BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderViewportBase> BearGraphics::BearRenderInterface::CreateViewport(const BearWindow&Window)
{
	if (Empty()|| Window.Empty())
		return BearFactoryPointer<BearRenderBase::BearRenderViewportBase>();
	return BearFactoryPointer<BearRenderBase::BearRenderViewportBase>(GRenderFactoty->CreateViewport(Window.GetWindowHandle(), Window.GetSize().x, Window.GetSize().y, Window.IsFullScreen(),false));
}

void BearGraphics::BearRenderInterface::Destroy()
{
	if (FDestroy)
	{
		FDestroy();
		FDestroy = 0;
		FInitialize = 0;
	}
}

bool BearGraphics::BearRenderInterface::Empty()
{
	return GRenderFactoty==0;
}
