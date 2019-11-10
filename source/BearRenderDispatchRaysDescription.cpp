#include "BearGraphics.hpp"

void BearGraphics::BearRenderDispatchRaysDescription::Copy(const BearRenderDispatchRaysDescription & Right)
{
	Width = Right.Width;
	Height = Right.Height;
	Depth = Right.Depth;

	RayGeneration.Buffer.copy(Right.RayGeneration.Buffer);
	RayGeneration.Size = Right.RayGeneration.Size;

	Miss.Buffer.copy(Right.Miss.Buffer);
	Miss.Size = Right.Miss.Size;
	Miss.Stride = Right.Miss.Stride;

	HitGroup.Buffer.copy(Right.HitGroup.Buffer);
	HitGroup.Size = Right.HitGroup.Size;
	HitGroup.Stride = Right.HitGroup.Stride;

	Callable.Buffer.copy(Right.Callable.Buffer);
	Callable.Size = Right.Callable.Size;
	Callable.Stride = Right.Callable.Stride;
}

void BearGraphics::BearRenderDispatchRaysDescription::Swap(BearRenderDispatchRaysDescription & Right)
{
	BearCore::bear_swap(Width , Right.Width);
	BearCore::bear_swap(Height , Right.Height);
	BearCore::bear_swap(Depth , Right.Depth);

	RayGeneration.Buffer.swap(Right.RayGeneration.Buffer);
	BearCore::bear_swap(RayGeneration.Size, Right.RayGeneration.Size);

	Miss.Buffer.swap(Right.Miss.Buffer);
	BearCore::bear_swap(Miss.Size , Right.Miss.Size);
	BearCore::bear_swap(Miss.Stride , Right.Miss.Stride);

	HitGroup.Buffer.swap(Right.HitGroup.Buffer);
	BearCore::bear_swap(HitGroup.Size, Right.HitGroup.Size);
	BearCore::bear_swap(HitGroup.Stride, Right.HitGroup.Stride);

	Callable.Buffer.swap(Right.Callable.Buffer);
	BearCore::bear_swap(Callable.Size, Right.Callable.Size);
	BearCore::bear_swap(Callable.Stride, Right.Callable.Stride);
}
