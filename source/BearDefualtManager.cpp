#include "BearGraphics.hpp"

extern BearRHI::BearRHIDefaultManager*DefualtManager;
BearGraphics::BearVertexShaderRef* GDVertexShaders[BearGraphics::DVS_COUNT];
BearGraphics::BearPixelShaderRef* GDPixelShaders[BearGraphics::DPS_COUNT];
BearGraphics::BearVertexStateRef* GDVertexState=0;
BearGraphics::BearSamplerStateRef* GDSamplerState = 0;
BearGraphics::BearTexture2DRef* GDTexture2D = 0;
BearGraphics::BearBlendStateRef* GDBlendAlpha = 0;
BearGraphics::BearRasterizerStateRef* GDRasterizerState = 0;

const BearGraphics::BearVertexShaderRef & BearGraphics::BearDefaultManager::GetVertexShader(BearDefaultVertexShader type)
{
	if (!GDVertexShaders[type]&& DefualtManager)
	{
		GDVertexShaders[type] = BearCore::bear_new< BearVertexShaderRef>();
		BearCore::BearString out_text;
		BEAR_ASSERT(GDVertexShaders[type]->CompileText(DefualtManager->GetVertexShader(type), out_text));
	}
	return *GDVertexShaders[type];
}

const BearGraphics::BearPixelShaderRef & BearGraphics::BearDefaultManager::GetPixelShader(BearDefaultPixelShader type)
{
	if (!GDPixelShaders[type] && DefualtManager)
	{
		GDPixelShaders[type] = BearCore::bear_new< BearPixelShaderRef>();
		BearCore::BearString out_text;
		BEAR_ASSERT(GDPixelShaders[type]->CompileText(DefualtManager->GetPixelShader(type), out_text));
	}
	return *GDPixelShaders[type];
}

const BearGraphics::BearVertexStateRef & BearGraphics::BearDefaultManager::GetVertexState()
{
	if (!GDVertexState)
	{
		BearShaderVertexCompilerRef compiler;
		BearCore::BearString out_text;
		BEAR_ASSERT(compiler.CompileText(DefualtManager->GetVertexShader(DVS_Default), out_text));

		BearVertexStateInitializer initializer;
		initializer.Elements[0].Name = "POSITION";
		initializer.Elements[0].Offset = 0;
		initializer.Elements[0].Type = VF_R32G32B32_FLOAT;
		initializer.Elements[1].Name = "TEXTUREUV";
		initializer.Elements[1].Offset = sizeof(float)*3;
		initializer.Elements[1].Type = VF_R32G32_FLOAT;

		GDVertexState = BearCore::bear_new< BearVertexStateRef>(BearVertexStateRef(initializer,compiler.Begin(), compiler.GetSize()));
	}
	return *GDVertexState;
}

const BearGraphics::BearSamplerStateRef & BearGraphics::BearDefaultManager::GetSamplerState()
{
	if (!GDSamplerState)
	{
		BearGraphics::BearSamplerStateInitializer sampler_intialize;
		sampler_intialize.Filter = BearGraphics::SF_MAG_MIP_LINEAR;
		GDSamplerState =BearCore::bear_new< BearSamplerStateRef>( BearSamplerStateRef(sampler_intialize));
	}
	return *GDSamplerState;
}

const  BearGraphics::BearTexture2DRef & BearGraphics::BearDefaultManager::GetTexture2D()
{
	if (!GDTexture2D)
	{
		BearImage img;
		img.Create(1, 1);
		img.Fill(BearCore::BearColor::White);
		GDTexture2D = BearCore::bear_new< BearTexture2DRef>();
		GDTexture2D->Create(img);
	}
	return *GDTexture2D;
}

const BearGraphics::BearBlendStateRef & BearGraphics::BearDefaultManager::GetBlendAlpha()
{
	if (!GDBlendAlpha)
	{
		BearGraphics::BearBlendStateInitializer blend_intialize;
		blend_intialize.RenderTarget[0].ColorSrc = BearGraphics::BF_SRC_ALPHA;
		blend_intialize.RenderTarget[0].ColorDst = BearGraphics::BF_INV_SRC_ALPHA;
		GDBlendAlpha = BearCore::bear_new< BearBlendStateRef>(blend_intialize);

	}
	return*GDBlendAlpha;
	// TODO: вставьте здесь оператор return
}

const BearGraphics::BearRasterizerStateRef & BearGraphics::BearDefaultManager::GetRasterizerState()
{
	if (!GDRasterizerState)
	{
		BearGraphics::BearRasterizerStateInitializer r_intialize;
		GDRasterizerState = BearCore::bear_new< BearRasterizerStateRef>(r_intialize);
	}
	return *GDRasterizerState;
}

void BearGraphics::BearDefaultManager::Clear()
{
	for (bsize i = 0; i < DVS_COUNT; i++)
	{
		if (GDVertexShaders[i])BearCore::bear_delete(GDVertexShaders[i]);
	}
	BearCore::bear_fill(GDVertexShaders);
	for (bsize i = 0; i < DPS_COUNT; i++)
	{
		if (GDPixelShaders[i])BearCore::bear_delete(GDPixelShaders[i]);
	}
	BearCore::bear_fill(GDPixelShaders);
	if(GDVertexState)BearCore::bear_delete(GDVertexState);
	if(GDSamplerState)BearCore::bear_delete(GDSamplerState);
	if(GDTexture2D)BearCore::bear_delete(GDTexture2D);
	if (GDBlendAlpha)BearCore::bear_delete(GDBlendAlpha);
	if(GDRasterizerState)BearCore::bear_delete(GDRasterizerState);
	GDBlendAlpha = 0; GDVertexState = 0; GDSamplerState = 0; GDTexture2D = 0; GDRasterizerState = 0;
}
