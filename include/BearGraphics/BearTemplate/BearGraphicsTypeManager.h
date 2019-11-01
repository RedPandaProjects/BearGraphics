#pragma once
namespace BearRenderBase
{
	class BearRenderContextBase;
};
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
			
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderPipelineBase>()
			{
				return GOT_Pipeline;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderContextBase>()
			{
				return GOT_Context;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderIndexBufferBase>()
			{
				return GOT_IndexBuffer;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderVertexBufferBase>()
			{
				return GOT_VertexBuffer;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderUniformBufferBase>()
			{
				return GOT_UniformBuffer;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderRootSignatureBase>()
			{
				return GOT_RootSignature;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderDescriptorHeapBase>()
			{
				return GOT_DescriptorHeap;
			}
			template<>
			static	BearGraphicsObjectType GetType<BearRenderBase::BearRenderSamplerStateBase>()
			{
				return GOT_SamplerState;
			}
		private:

		};
	}
}