#pragma once
namespace BearGraphics
{
	template<typename T>
	class BearFactoryPointer
	{
	
		struct Data
		{
			Data():Object(0), Count(1){}
			Data(void *object, BearGraphicsObjectType objectType):Object(object), Count(1), ObjectType(objectType){}
			~Data() { if(Object)  BearCore::bear_delete(Object); }
			void *Object;
			BearGraphicsObjectType          ObjectType;
			bsize Count;
		} 
		*m_data;
		BearGraphicsObjectType          m_CurrentType;
	public:
		BearFactoryPointer() :m_data(0) {}
		BearFactoryPointer(void*object, BearGraphicsObjectType type, bsize count = 1) :m_data(0) { m_data = BearCore::bear_new< Data>(object, type); m_data->Count = count; m_CurrentType = Impl::BearTypeManager::GetType<T>(); }
		BearFactoryPointer(T*c) :m_data(0) { m_data = BearCore::bear_new< Data>(reinterpret_cast<T*>(c), Impl::BearTypeManager::GetType<T>()); m_CurrentType = Impl::BearTypeManager::GetType<T>(); }
		inline void clear() { if (m_data) { m_data->Count--; if (m_data->Count == 0) { BearCore::bear_delete(m_data);  } m_data = 0;} }
		inline ~BearFactoryPointer() { clear(); }
		inline	bool empty()const { if (m_data)return m_data->Object==0; return m_data == 0; }

		inline T*get() { if (empty())return 0; return reinterpret_cast<T*>(m_data->Object); }
		inline const T*get()const { if (empty())return 0; return reinterpret_cast<T*>(m_data->Object); }
		inline T&operator*() { BEAR_ASSERT(empty() == false)   return *reinterpret_cast<T*>(m_data->Object); }
		inline const T&operator*() const{ BEAR_ASSERT(empty() == false)   return *reinterpret_cast<T*>(m_data->Object); }
		inline T*operator->() {BEAR_ASSERT(empty()==false)   return reinterpret_cast<T*>(m_data->Object);}
		inline const T*operator->() const { BEAR_ASSERT(empty() == false)   return reinterpret_cast<T*>(m_data->Object); }

		template<typename C>
		inline BearFactoryPointer<C> cast() const
		{
			if (empty())return  BearFactoryPointer<C>();
			m_data->Count++;
			void* out = Impl::BearCasterObject::Cast(m_data->Object,m_data->ObjectType, Impl::BearTypeManager::GetType<C>());
			BearFactoryPointer<C> result(out, m_data->ObjectType, m_data->Count);
			return result;
		}
		
		inline void replace(BearFactoryPointer&right)
		{
			if(right.empty()&& empty())return ;

			if (right.empty())
			{
				right.m_data = m_data = BearCore::bear_new< Data>();
			}
			if (empty())
			{
				m_data = m_data = BearCore::bear_new< Data>();
			}
			BearCore::bear_swap(right.m_data->Object, m_data->Object);
			BearCore::bear_swap(right.m_data->ObjectType, m_data->ObjectType);
		}
		inline void copy(const BearFactoryPointer&right)
		{
			clear();
			m_CurrentType = right.m_CurrentType;
			if (right.empty())return;
			m_data = right.m_data;
			m_data->Count++;
		}
		inline void swap(BearFactoryPointer&right)
		{
			BearCore::bear_swap(m_CurrentType, right.m_CurrentType);
			BearCore::bear_swap(m_data, right.m_data);
		}
		template<class C>
		BearFactoryPointer(const BearFactoryPointer<C>&right) :m_data(0) {swap(right.cast<T>());; }
		BearFactoryPointer(const BearFactoryPointer&right) :m_data(0) { copy(right); }
		BearFactoryPointer(BearFactoryPointer&&right) :m_data(0) { swap(right); }
		BearFactoryPointer&operator=(const BearFactoryPointer&right) { copy(right); return*this; }
		BearFactoryPointer&operator=(BearFactoryPointer&&right) { swap(right); return*this; }
	};
}