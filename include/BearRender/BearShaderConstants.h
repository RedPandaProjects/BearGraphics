#pragma once 
namespace BearGraphics
{
	struct BearShaderConstantsInitializer
	{
		BearCore::BearVector <BearConstantFormat> Constants;
	};
	class BEARGRAPHICS_API BearShaderConstantsRef
	{
	public:
		friend class BearRenderInterface;
		BearShaderConstantsRef();
		BearShaderConstantsRef(const BearShaderConstantsInitializer&initializer,bool dynamic=false);
		~BearShaderConstantsRef();
		void Copy(const BearShaderConstantsRef&right);
		void Swap(BearShaderConstantsRef&right);
		BearShaderConstantsRef&operator=(const BearShaderConstantsRef&right);
		BearShaderConstantsRef(const BearShaderConstantsRef&right);
		inline bool Empty()const { return m_data.empty(); }
		inline bool IsOne()const { return m_data.is_one(); }
		void*Lock();
		void Unlock();
		void Clear();
	private:
		struct data
		{
			BearRHI::BearRHIShaderConstants*resource;
			data() :resource(0) {}
			~data();
		};
		BearCore::BearMemoryMultiRef<data> m_data;

	};
};