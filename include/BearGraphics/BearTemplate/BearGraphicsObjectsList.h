#ifndef  RENDER_BEGIN_CLASS_REGISTRATION1
#define RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)
#endif 
#ifndef  RENDER_BEGIN_CLASS_REGISTRATION2
#define RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)
#endif 

#ifndef  RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY
#define RENDER_BEGIN_CLASS_REGISTRATION1_WITHOUT_FACTORY(Name,...) RENDER_BEGIN_CLASS_REGISTRATION1(Name,...)
#endif 
#ifndef  RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY
#define RENDER_BEGIN_CLASS_REGISTRATION2_WITHOUT_FACTORY(Name,Parent,...) RENDER_BEGIN_CLASS_REGISTRATION2(Name,Parent,...)
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
RENDER_BEGIN_CLASS_REGISTRATION2(Viewport,Object,const BearGraphics::BearRenderViewportDescription&Description)
RENDER_END_CLASS_REGISTRATION()
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RENDER_LEVEL_1_REGISTER == 1
RENDER_BEGIN_CLASS_REGISTRATION2(Context, Object)
RENDER_METHOD_REGISTRATION(void, AttachViewportAsFrameBuffer,BearGraphics::BearFactoryPointer<BearRHIViewport> Viewport)
RENDER_END_CLASS_REGISTRATION()
#endif


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