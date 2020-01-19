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
RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY(Object)
RENDER_END_CLASS_REGISTRATION()
RENDER_BEGIN_CLASS_REGISTRATION2(Shader, Object, BearShaderType Type)
#ifdef DEVELOPER_VERSION
RENDER_METHOD_REGISTRATION(bool, LoadAsText, const bchar* Text, const BearMap<BearString, BearString>& Defines, BearString& OutError, BearIncluder* Includer = 0)
RENDER_METHOD_REGISTRATION(void*, GetPointer)
RENDER_METHOD_REGISTRATION(bsize, GetSize)
#endif
RENDER_METHOD_REGISTRATION(void, LoadAsBinary, void* data, bsize size)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION2(VertexBuffer, Object)
RENDER_METHOD_REGISTRATION(void, Create, bsize Stride, bsize Count, bool Dynamic)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(void, Clear)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(IndexBuffer, Object)
RENDER_METHOD_REGISTRATION(void, Create, bsize Count, bool Dynamic)
RENDER_METHOD_REGISTRATION(uint32*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(void, Clear)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(UniformBuffer, Object)
RENDER_METHOD_REGISTRATION(void, Create, bsize Size, bool Dynamic)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_METHOD_REGISTRATION(void, Clear)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(Pipeline, Object, const BearPipelineDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(RootSignature, Object, const BearRootSignatureDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(DescriptorHeap, Object, const BearDescriptorHeapDescription& Description)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(Sampler, Object)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(Viewport, Object, void* Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync, const BearViewportDescription& Description)
RENDER_METHOD_REGISTRATION(void, SetVSync, bool Sync)
RENDER_METHOD_REGISTRATION(void, SetFullScreen, bool FullScreen)
RENDER_METHOD_REGISTRATION(void, Resize, bsize Width, bsize Height)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY(ShaderResource, Object)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(Texture2D, ShaderResource, bsize Width, bsize Height, bsize Mips, bsize Count, BearTexturePixelFormat PixelFormat, void* data = 0)
RENDER_END_CLASS_REGISTRATION()
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RENDER_LEVEL_1_REGISTER == 1
RENDER_BEGIN_CLASS_REGISTRATION1(Context)
RENDER_METHOD_REGISTRATION(void, SetDescriptorHeap, BearFactoryPointer<BearRHIDescriptorHeap> DescriptorHeap  )
RENDER_METHOD_REGISTRATION(void, SetPipeline, BearFactoryPointer<BearRHIPipeline> Pipeline)
RENDER_METHOD_REGISTRATION(void, SetVertexBuffer,BearFactoryPointer<BearRHIVertexBuffer> Buffer) 
RENDER_METHOD_REGISTRATION(void, SetIndexBuffer,BearFactoryPointer<BearRHIIndexBuffer> buffer) 
RENDER_METHOD_REGISTRATION(void, SetViewport,float x, float y, float width, float height, float minDepth = 0.f, float maxDepth = 1.f) 
RENDER_METHOD_REGISTRATION(void, SetScissor,bool Enable, float x, float y, float x1, float y1) 
RENDER_METHOD_REGISTRATION(void, Draw,bsize count, bsize offset = 0)
RENDER_METHOD_REGISTRATION(void, DrawIndex,bsize count, bsize offset_index = 0, bsize offset_vertex  = 0)
RENDER_METHOD_REGISTRATION(void, AttachViewportAsFrameBuffer,BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_METHOD_REGISTRATION(void, DetachFrameBuffer)
RENDER_METHOD_REGISTRATION(void, ClearFrameBuffer)
RENDER_METHOD_REGISTRATION(void, Flush, bool Wait)
RENDER_METHOD_REGISTRATION(void, Wait)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIIndexBuffer> Dst, BearFactoryPointer<BearRHIIndexBuffer> Src)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIVertexBuffer> Dst, BearFactoryPointer<BearRHIVertexBuffer> Src)
RENDER_METHOD_REGISTRATION(void, Copy, BearFactoryPointer<BearRHIUniformBuffer> Dst, BearFactoryPointer<BearRHIUniformBuffer> Src)
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