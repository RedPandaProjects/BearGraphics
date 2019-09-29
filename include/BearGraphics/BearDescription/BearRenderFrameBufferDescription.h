#pragma once 
namespace BearGraphics
{

	
	class BEARGRAPHICS_API BearRenderFrameBufferDescription
	{
	public:
		/*BearRenderFrameBufferDescription();
		BearRenderFrameBufferDescription(const BearRenderFrameBufferDescription&Right);
		BearRenderFrameBufferDescription(BearRenderFrameBufferDescription&&Right);*/
		inline ~BearRenderFrameBufferDescription() {}



		/*void Copy(const BearRenderFrameBufferDescription&Right);
		void Swap(BearRenderFrameBufferDescription&Right);
		inline BearRenderFrameBufferDescription&operator=(const BearRenderFrameBufferDescription&Right) { Copy(Right); return*this; }
		inline BearRenderFrameBufferDescription&operator=(BearRenderFrameBufferDescription&&Right) { Swap(Right); return*this; }*/

		BearCore::BearColor ClearingColor[8];
		bool ClearBits[8];

		

	};
}
