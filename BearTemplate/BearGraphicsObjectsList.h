#ifndef  RENDER_BEGIN_CLASS_REGISTRATION1
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)
#endif 
#ifndef  RENDER_BEGIN_CLASS_REGISTRATION2
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name,__VA_ARGS__)
#endif 

#ifndef  RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY
#define RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY(Name,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name,__VA_ARGS__)
#endif 
#ifndef  RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY
#define RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,__VA_ARGS__)
#endif 

#ifndef  RENDER_CONSTRUCTOR_REGISTRATION
#define RENDER_CONSTRUCTOR_REGISTRATION(Name,...) 
#endif 

#ifndef  RENDER_METHOD_REGISTRATION
#define RENDER_METHOD_REGISTRATION(RetVal,Name,...)
#endif 
#ifndef  RENDER_END_CLASS_REGISTRATION
#define RENDER_END_CLASS_REGISTRATION()
#endif 

#ifndef RENDER_LEVEL_0_REGISTER
#define RENDER_LEVEL_0_REGISTER 1
#endif
#ifndef RENDER_LEVEL_1_REGISTER
#define RENDER_LEVEL_1_REGISTER 1
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RENDER_LEVEL_0_REGISTER == 1

RENDER_BEGIN_CLASS_REGISTRATION2(Shader, Object, BearShaderType Type)

#ifdef DEVELOPER_VERSION	
RENDER_METHOD_REGISTRATION(bool, LoadAsText, const bchar* Text, const BearMap<BearStringConteniar, BearStringConteniar>& Defines, BearString& OutError, BearIncluder*Includer)
RENDER_METHOD_REGISTRATION(void*, GetPointer)
RENDER_METHOD_REGISTRATION(bsize, GetSize)
#endif
RENDER_METHOD_REGISTRATION(void, LoadAsBinary, void* data, bsize size)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION2(VertexBuffer, Object)
RENDER_METHOD_REGISTRATION(void, Create, bsize Stride, bsize Count, bool Dynamic, void* data = 0)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(void, Clear)
RENDER_METHOD_REGISTRATION(bsize, GetCount)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(IndexBuffer, Object)
RENDER_METHOD_REGISTRATION(void, Create, bsize Count, bool Dynamic, void* data = 0)
RENDER_METHOD_REGISTRATION(uint32*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(void, Clear)
RENDER_METHOD_REGISTRATION(bsize, GetCount)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(UniformBuffer, Object, bsize Stride, bsize Count, bool Dynamic)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(bsize, GetCount)
RENDER_METHOD_REGISTRATION(bsize, GetStride)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(Pipeline, Object)
RENDER_METHOD_REGISTRATION(BearPipelineType, GetType)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(PipelineGraphics, Pipeline, const BearPipelineGraphicsDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(PipelineMesh, Pipeline, const BearPipelineMeshDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(PipelineRayTracing, Pipeline, const BearPipelineRayTracingDescription& Description)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION2(Sampler, Object, const BearSamplerDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(RenderPass, Object, const BearRenderPassDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(FrameBuffer, Object, const BearFrameBufferDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(RootSignature, Object, const BearRootSignatureDescription& Description)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(ShaderResource, Object)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(UnorderedAccess, ShaderResource)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(Texture2D, UnorderedAccess, bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage = TU_STATIC, void* data = 0,bool UAV=false)
RENDER_CONSTRUCTOR_REGISTRATION(Texture2D, bsize Width, bsize Height, BearRenderTargetFormat Format)
RENDER_CONSTRUCTOR_REGISTRATION(Texture2D, bsize Width, bsize Height, BearDepthStencilFormat Format)
RENDER_METHOD_REGISTRATION(void*, Lock, bsize mip = 0, bsize depth = 0)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(BearTextureType, GetType)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(TextureCube, ShaderResource, bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, BearTextureUsage TypeUsage = TU_STATIC, void* data = 0)
RENDER_METHOD_REGISTRATION(void*, Lock, bsize mip = 0, bsize depth = 0)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(StructuredBuffer, UnorderedAccess,bsize Size,void* Data = 0, bool UAV = false)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(BottomLevel, UnorderedAccess, const BearBottomLevelDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(TopLevel, UnorderedAccess, const BearTopLevelDescription& Description)
RENDER_END_CLASS_REGISTRATION()
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RENDER_LEVEL_1_REGISTER == 1


RENDER_BEGIN_CLASS_REGISTRATION1(DescriptorHeap, const BearDescriptorHeapDescription& Description)
RENDER_METHOD_REGISTRATION(void, SetUniformBuffer, bsize slot, BearFactoryPointer<BearRHIUniformBuffer> UniformBuffer, bsize offset = 0)
RENDER_METHOD_REGISTRATION(void, SetShaderResource, bsize slot, BearFactoryPointer<BearRHIShaderResource> ShaderResource, bsize offset = 0)
RENDER_METHOD_REGISTRATION(void, SetSampler, bsize slot, BearFactoryPointer<BearRHISampler> Sampler)
RENDER_METHOD_REGISTRATION(void, SetUnorderedAccess, bsize slot, BearFactoryPointer<BearRHIUnorderedAccess> UnorderedAccess, bsize offset = 0)
RENDER_END_CLASS_REGISTRATION()



RENDER_BEGIN_CLASS_REGISTRATION1(Viewport, void* Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync, const BearViewportDescription& Description)
RENDER_METHOD_REGISTRATION(void, SetVSync, bool Sync)
RENDER_METHOD_REGISTRATION(BearRenderTargetFormat, GetFormat)
RENDER_METHOD_REGISTRATION(void, SetFullScreen, bool FullScreen)
RENDER_METHOD_REGISTRATION(void, Resize, bsize Width, bsize Height)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION1(Context)
RENDER_METHOD_REGISTRATION(void, Reset)
RENDER_METHOD_REGISTRATION(void, ClearState)
RENDER_METHOD_REGISTRATION(void, SetStencilRef, uint32 Ref)
RENDER_METHOD_REGISTRATION(void, SetDescriptorHeap, BearFactoryPointer<BearRHIDescriptorHeap> DescriptorHeap)
RENDER_METHOD_REGISTRATION(void, SetPipeline, BearFactoryPointer<BearRHIPipeline> Pipeline)
RENDER_METHOD_REGISTRATION(void, SetVertexBuffer, BearFactoryPointer<BearRHIVertexBuffer> Buffer)
RENDER_METHOD_REGISTRATION(void, SetIndexBuffer, BearFactoryPointer<BearRHIIndexBuffer> buffer)
RENDER_METHOD_REGISTRATION(void, SetViewport, float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f)
RENDER_METHOD_REGISTRATION(void, SetScissor, bool Enable, float x, float y, float x1, float y1)
RENDER_METHOD_REGISTRATION(void, Draw, bsize count, bsize offset = 0)
RENDER_METHOD_REGISTRATION(void, DispatchMesh,bsize CountX, bsize CountY, bsize CountZ)
RENDER_METHOD_REGISTRATION(void, DrawIndex, bsize count, bsize offset_index = 0, bsize offset_vertex = 0)
RENDER_METHOD_REGISTRATION(void, SetViewportAsFrameBuffer, BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_METHOD_REGISTRATION(void, SetFrameBuffer, BearFactoryPointer<BearRHIFrameBuffer> FrameBuffer)
RENDER_METHOD_REGISTRATION(void, Flush, BearFactoryPointer<BearRHIViewport> Viewport, bool Wait)
RENDER_METHOD_REGISTRATION(void, Flush, bool Wait)
RENDER_METHOD_REGISTRATION(void, Wait)
RENDER_METHOD_REGISTRATION(void, BeginEvent, char const* name, BearColor color = BearColor::White)
RENDER_METHOD_REGISTRATION(void, EndEvent)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIIndexBuffer> Dst, BearFactoryPointer<BearRHIIndexBuffer> Src)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIVertexBuffer> Dst, BearFactoryPointer<BearRHIVertexBuffer> Src)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIUniformBuffer> Dst, BearFactoryPointer<BearRHIUniformBuffer> Src)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHITexture2D> Dst, BearFactoryPointer<BearRHITexture2D> Src)
RENDER_METHOD_REGISTRATION(void, Lock, BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_METHOD_REGISTRATION(void, Lock, BearFactoryPointer<BearRHIFrameBuffer> FrameBuffer)
RENDER_METHOD_REGISTRATION(void, Unlock, BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_METHOD_REGISTRATION(void, Unlock, BearFactoryPointer<BearRHIFrameBuffer> FrameBuffer)
RENDER_METHOD_REGISTRATION(void, Lock, BearFactoryPointer<BearRHIUnorderedAccess> UnorderedAccess)
RENDER_METHOD_REGISTRATION(void, Unlock, BearFactoryPointer<BearRHIUnorderedAccess> UnorderedAccess)
RENDER_END_CLASS_REGISTRATION()
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef RENDER_LEVEL_0_REGISTER
#undef RENDER_LEVEL_0_REGISTER 
#endif
#ifdef RENDER_LEVEL_1_REGISTER
#undef RENDER_LEVEL_1_REGISTER 
#endif


#ifdef  RENDER_BEGIN_CLASS_REGISTRATION1
#undef RENDER_BEGIN_CLASS_REGISTRATION1
#endif 
#ifdef  RENDER_BEGIN_CLASS_REGISTRATION2
#undef RENDER_BEGIN_CLASS_REGISTRATION2
#endif 
#ifdef  RENDER_METHOD_REGISTRATION
#undef RENDER_METHOD_REGISTRATION
#endif 
#ifdef  RENDER_END_CLASS_REGISTRATION
#undef RENDER_END_CLASS_REGISTRATION
#endif 
#ifdef RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY
#undef RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY
#endif
#ifdef RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY
#undef RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY
#endif
#ifdef RENDER_CONSTRUCTOR_REGISTRATION
#undef RENDER_CONSTRUCTOR_REGISTRATION
#endif