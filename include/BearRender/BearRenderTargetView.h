#pragma once 

namespace BearGraphics
{
	
	
	class BEARGRAPHICS_API BearRenderTargetViewRef
	{
	public:
		friend class BearRenderInterface;
		BearRenderTargetViewRef();
		~BearRenderTargetViewRef();
		void Copy(const BearRenderTargetViewRef&right);
		void Swap(BearRenderTargetViewRef&right);
		BearRenderTargetViewRef&operator=(const BearRenderTargetViewRef&right);
		BearRenderTargetViewRef(const BearRenderTargetViewRef&right);
		void Create(bsize w, bsize h, BearRenderTargetFormat format);
		void ClearColor(const BearCore::BearColor&color);
		void Resize(bsize w, bsize h);
		void GenetateMips();
		void Clear();
		inline bool Empty()const { return m_data.empty(); }
		inline bool IsOne()const { return m_data.is_one(); }
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