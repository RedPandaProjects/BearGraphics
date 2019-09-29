#pragma once 
namespace BearGraphics
{
	struct BearRenderViewportDescription
	{
		BearRenderViewportDescription() :Clear(false) {}
		bool Clear;
		BearCore::BearColor ClearColor;
	};
}
