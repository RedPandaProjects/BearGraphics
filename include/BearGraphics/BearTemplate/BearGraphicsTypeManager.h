#pragma once
namespace BearGraphics
{
	namespace Impl
	{
		class BearGraphicsTypeManager
		{
			BEAR_CLASS_STATIC(BearGraphicsTypeManager);
		public:
			template<typename C>
			static	BearGraphicsObjectType GetType()
			{
				return GOT_None;
			}

			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderObject>()
			{
				return GOT_Object;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderShaderResource>()
			{
				return GOT_ShaderResource;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderTexture2DBase>()
			{
				return GOT_Texture2D;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderTargetViewBase>()
			{
				return GOT_RenderTargetView;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderViewportBase>()
			{
				return GOT_Viewport;
			}
		private:

		};
	}
}