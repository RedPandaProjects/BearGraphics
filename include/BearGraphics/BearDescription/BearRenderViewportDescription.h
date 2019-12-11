#pragma once 
struct BearRenderViewportDescription
{
	BearRenderViewportDescription() :Clear(false) {}
	bool Clear;
	BearColor ClearColor;
};