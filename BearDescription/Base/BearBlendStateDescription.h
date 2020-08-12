#pragma once
struct BearBlendStateDescription
{
	BearBlendStateDescription() { IndependentBlendEnable = false; }
	struct RenderTarget
	{
		RenderTarget(
			bool enable = false,
			BearBlendOp color = BearBlendOp::Add,
			BearBlendFactor color_src = BearBlendFactor::One,
			BearBlendFactor color_dst = BearBlendFactor::Zero,
			BearBlendOp alpha = BearBlendOp::Add,
			BearBlendFactor alpha_src = BearBlendFactor::One,
			BearBlendFactor alpha_dst = BearBlendFactor::Zero,
			BearColorWriteMask color_write_mask = BearColorWriteMask::RGBA
		) :Enable(enable), Color(color), ColorSrc(color_src), ColorDst(color_dst), Alpha(alpha), AlphaSrc(alpha_src), AlphaDst(alpha_dst), ColorWriteMask(color_write_mask) {}

		bool Enable;
		BearBlendOp Color;
		BearBlendFactor ColorSrc;
		BearBlendFactor ColorDst;
		BearBlendOp Alpha;
		BearBlendFactor AlphaSrc;
		BearBlendFactor AlphaDst;
		BearColorWriteMask ColorWriteMask;
	};
	RenderTarget RenderTarget[8];
	bool IndependentBlendEnable;
};