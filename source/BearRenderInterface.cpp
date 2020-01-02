#include "BearGraphics.hpp"
#include "BearRHI/BearRHIFactory.h"
#include "BearRHI/BearRenderHardwareInterface.h"
BEARGRAPHICS_API BearRHI::BearRHIFactory* GFactory=0;
BEARGRAPHICS_API BearRHI::BearRenderHardwareInterface* GRenderHardwareInterface=0;
static BearStringConteniar LProjectName;
bool BearRenderInterface::Initialize(const bchar* name)
{
	Destroy();
	if (!BearManagerProjects::CheckProject(name))
	{
		Destroy();
		return false;
	}
	auto RHIInitialize = BearManagerProjects::GetFunctionInProject<void(*)(void)>(name, TEXT("RHIInitialize"));
	RHIInitialize();
	if (!GFactory)
	{
		Destroy();
		return false;
	}
	BearLog::Printf(TEXT("BearGraphics build %s"), *BearLog::GetBuild(2016, 11, 27));
	LProjectName = name;
	return true;
}

BearFactoryPointer<BearRHI::BearRHIViewport> BearRenderInterface::CreateViewport(BearWindow& Window, const BearRenderViewportDescription& Description, bool Vsync)
{
	if (GFactory)return GFactory->CreateViewport(Window.GetWindowHandle(), Window.GetSize().x,Window.GetSize().y, Window.IsFullScreen(),Vsync,Description);
	return BearFactoryPointer<BearRHI::BearRHIViewport>();
}

BearFactoryPointer<BearRHI::BearRHIContext> BearRenderInterface::CreateContext()
{
	if (GFactory)return GFactory->CreateContext();
	return BearFactoryPointer<BearRHI::BearRHIContext>();
}


bool BearRenderInterface::RTXSupport()
{
	return false;
}

void BearRenderInterface::Destroy()
{
	if (LProjectName.size() == 0)return;
	if (GFactory)bear_delete(GFactory);
	if (GRenderHardwareInterface)bear_delete(GRenderHardwareInterface);
	GRenderHardwareInterface = nullptr;
	GFactory = nullptr;
	BearManagerProjects::UnLoad(LProjectName);
	LProjectName = TEXT("");
}

bool BearRenderInterface::Empty()
{
	return GFactory==nullptr;
}
