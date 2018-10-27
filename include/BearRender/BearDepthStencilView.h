#pragma once 

namespace BearGraphics
{
	
	
	class BEARGRAPHICS_API BearDepthStencilViewRef
	{
	public:
		friend class BearRenderInterface;
		BearDepthStencilViewRef();
		~BearDepthStencilViewRef();
		void copy(const BearDepthStencilViewRef&right);
		void swap(BearDepthStencilViewRef&right);
		BearDepthStencilViewRef&operator=(const BearDepthStencilViewRef&right);
		BearDepthStencilViewRef(const BearDepthStencilViewRef&right);
		void create(bsize w, bsize h, BearDepthStencilFormat format);
		void generateMips();
		void clearDepth(float debpt=1.f);
		void clearStencill(uint8 mask=255);
		void resize(bsize w, bsize h);
		void clear();
		bool empty()const;
	private:
		struct data
		{
			BearRHI::BearRHIDepthStencilView*resource;
			data();
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;

	};
}