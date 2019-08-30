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

void BearGraphics::BearRenderInterface::Destroy()
{
	if (FDestroy)
	{
		FDestroy();
		FDestroy = 0;
		FInitialize = 0;
	}
}
