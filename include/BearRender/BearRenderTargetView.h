#pragma once 

namespace BearGraphics
{
	
	
	class BEARGRAPHICS_API BearRenderTargetViewRef
	{
	public:
		friend class BearRenderInterface;
		BearRenderTargetViewRef();
		~BearRenderTargetViewRef();
		void copy(const BearRenderTargetViewRef&right);
		void swap(BearRenderTargetViewRef&right);
		BearRenderTargetViewRef&operator=(const BearRenderTargetViewRef&right);
		BearRenderTargetViewRef(const BearRenderTargetViewRef&right);
		void create(bsize w, bsize h, BearRenderTargetFormat format);
		void clearColor(const BearCore::BearColor&color);
		void resize(bsize w, bsize h);
		void genetateMips();
		void clear();
		bool empty()const;
	private:
		struct data
		{
			BearRHI::BearRHIRenderTargetView*resource;
			data();
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;

	};
}