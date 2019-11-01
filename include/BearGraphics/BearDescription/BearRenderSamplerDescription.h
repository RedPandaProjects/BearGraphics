#pragma once 
namespace BearGraphics
{
	struct BearRenderSamplerDescription
	{
		BearRenderSamplerDescription
		(
			BearSamplerAddressMode addressU = SAM_WRAP,
			BearSamplerAddressMode addressV = SAM_WRAP,
			BearSamplerAddressMode addressW = SAM_WRAP,
			bsize mipBias = 0,
			bsize maxAnisotropy = 1,
			BearSamplerFilter filter = SF_MAG_MIP_POINT,
			BearCore::BearColor borderColor = BearCore::BearColor::Transparent
		)
			:AddressU(addressU),
			AddressV(addressV),
			AddressW(addressW),
			MipBias(mipBias),
			MaxAnisotropy(maxAnisotropy),
			Filter(filter),
			BorderColor(borderColor)
		{}
		BearSamplerAddressMode AddressU;
		BearSamplerAddressMode AddressV;
		BearSamplerAddressMode AddressW;
		bsize MipBias;
		bsize MaxAnisotropy;
		BearSamplerFilter Filter;
		BearCore::BearColor BorderColor;
	};
}