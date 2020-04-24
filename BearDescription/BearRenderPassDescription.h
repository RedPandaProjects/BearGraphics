#pragma once
struct BearRenderPassDescription
{
	BearRenderPassDescription()
	{
		DepthStencil.Format = DSF_NONE;
		DepthStencil.Clear = false;
	}
	struct RenderTarget
	{
		RenderTarget()
		{
			Clear = false;
			Format = RTF_NONE;
		}
		BearRenderTargetFormat Format;
		bool Clear;
		BearColor Color;
	}
	RenderTargets[8];
	struct
	{
		BearDepthStencilFormat Format;
		bool Clear;
		uint8 Stencil;
		float Depth;
	}
	DepthStencil;
};