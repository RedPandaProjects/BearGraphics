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


RENDER_BEGIN_CLASS_REGISTRATION2(VertexBuffer, Object,  bsize Stride, bsize Count, bool Dynamic)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_END_CLASS_REGISTRATION()

RENDER_BEGIN_CLASS_REGISTRATION2(IndexBuffer, Object,  bsize Count, bool Dynamic)
RENDER_METHOD_REGISTRATION(void*, Lock)
RENDER_METHOD_REGISTRATION(void, Unlock)
RENDER_END_CLASS_REGISTRATION()


RENDER_BEGIN_CLASS_REGISTRATION2(Viewport,Object,void* Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync, const BearRenderViewportDescription&Description)
RENDER_METHOD_REGISTRATION(void, SetVSync,bool Sync)
RENDER_METHOD_REGISTRATION(void, SetFullScreen,bool FullScreen)
RENDER_METHOD_REGISTRATION(void, Resize ,bsize Width, bsize Height)
RENDER_END_CLASS_REGISTRATION()
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RENDER_LEVEL_1_REGISTER == 1
RENDER_BEGIN_CLASS_REGISTRATION1(Context)
RENDER_METHOD_REGISTRATION(void, AttachViewportAsFrameBuffer,BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_METHOD_REGISTRATION(void, DetachFrameBuffer)
RENDER_METHOD_REGISTRATION(void, ClearFrameBuffer)
RENDER_METHOD_REGISTRATION(void, Flush, bool Wait)
RENDER_METHOD_REGISTRATION(void, Wait)
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