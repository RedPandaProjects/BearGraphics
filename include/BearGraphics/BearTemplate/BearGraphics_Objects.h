#ifndef REGISTER_OBJECT
#define REGISTER_OBJECT(EType,Class,Parent)
#endif
REGISTER_OBJECT(BearGraphics::GOT_ShaderResourceView, BearRenderShaderResourceViewBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_UnorderedAccessView, BearRenderUnorderedAccessViewBase, BearRenderShaderResourceViewBase)
REGISTER_OBJECT(BearGraphics::GOT_Texture2D,BearRenderTexture2DBase, BearRenderShaderResourceViewBase)
REGISTER_OBJECT(BearGraphics::GOT_Texture2DUAV, BearRenderTexture2DUAVBase, BearRenderUnorderedAccessViewBase)
REGISTER_OBJECT(BearGraphics::GOT_RenderTargetView,BearRenderTargetViewBase, BearRenderShaderResourceViewBase)
REGISTER_OBJECT(BearGraphics::GOT_FrameBuffer, BearRenderFrameBufferBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_Viewport,BearRenderViewportBase,BearRenderTargetViewBase)
REGISTER_OBJECT(BearGraphics::GOT_Shader, BearRenderShaderBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_Pipeline, BearRenderPipelineBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_IndexBuffer,BearRenderIndexBufferBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_UniformBuffer, BearRenderUniformBufferBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_VertexBuffer, BearRenderVertexBufferBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_RootSignature, BearRenderRootSignatureBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_DescriptorHeap, BearRenderDescriptorHeapBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_SamplerState, BearRenderSamplerStateBase, BearRenderObject)
REGISTER_OBJECT(BearGraphics::GOT_AccelerationStructures, BearRenderAccelerationStructuresBase, BearRenderShaderResourceViewBase)
#undef REGISTER_OBJECT