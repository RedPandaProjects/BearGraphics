#pragma once
namespace BearGraphics
{
	namespace Impl
	{
		class BearTypeManager
		{
			BEAR_CLASS_STATIC(BearTypeManager);
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
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderShaderBase>()
			{
				return GOT_Shader;
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