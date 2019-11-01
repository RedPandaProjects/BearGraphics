#pragma once
namespace BearRenderBase
{
	class BEARGRAPHICS_API BearRenderContextBase
	{
		BEAR_CLASS_NO_COPY(BearRenderContextBase);
	public:
		BearRenderContextBase() {}
		virtual void Flush(bool wait) = 0;
		virtual void Wait() = 0;
		virtual void AttachViewportAsFrameBuffer(BearGraphics::BearFactoryPointer<BearRenderViewportBase> Viewport) = 0;
		virtual void DetachFrameBuffer() = 0;
		virtual void ClearFrameBuffer() = 0;
		virtual void SetPipeline(BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderPipelineBase> Pipeline)=0;
		virtual void SetRootSignature(BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderRootSignatureBase> RootSignature)=0;
		virtual void SetVertexBuffer(BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderVertexBufferBase> buffer)=0;
		virtual void SetIndexBuffer(BearGraphics::BearFactoryPointer<BearRenderBase::BearRenderIndexBufferBase> buffer) = 0;
		virtual void SetViewport(float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f) = 0;
		virtual void SetScissor(bool Enable, float x, float y, float x1, float y1) = 0;
		virtual void Draw(bsize count,bsize offset=0)=0;
		virtual void DrawIndex(bsize count, bsize offset = 0)=0;
		virtual ~BearRenderContextBase() = 0;

	};
}