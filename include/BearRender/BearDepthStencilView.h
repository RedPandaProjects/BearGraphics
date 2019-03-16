#pragma once 

namespace BearGraphics
{
	
	
	class BEARGRAPHICS_API BearDepthStencilViewRef
	{
	public:
		friend class BearRenderInterface;
		BearDepthStencilViewRef();
		~BearDepthStencilViewRef();
		void Copy(const BearDepthStencilViewRef&right);
		void Swap(BearDepthStencilViewRef&right);
		BearDepthStencilViewRef&operator=(const BearDepthStencilViewRef&right);
		BearDepthStencilViewRef(const BearDepthStencilViewRef&right);
		void Create(bsize w, bsize h, BearDepthStencilFormat format);
	//	void GenerateMips();
		void ClearDepth(float debpt=1.f);
		void ClearStencil(uint8 mask=255);
		void Resize(bsize w, bsize h);
		void Clear();
		inline bool Empty()const { return m_data.empty(); }
		inline bool IsOne()const { return m_data.is_one(); }
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