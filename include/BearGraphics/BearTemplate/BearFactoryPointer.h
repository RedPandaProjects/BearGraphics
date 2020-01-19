#pragma once
template<typename T>
class BearFactoryPointer
{
	
	struct Data
	{
		Data():Object(0), Count(1){}
		Data(void *object, BearGraphicsObjectType objectType):Object(object), ObjectType(objectType), Count(1){}
		~Data() { Impl::BearRemoverObject::Remove<T>(Object, ObjectType); Object = 0; }
		void *Object;
		BearGraphicsObjectType          ObjectType;
		bsize Count;
	} 
	*m_data;
	void *m_CurObject;
	BearGraphicsObjectType          m_CurrentType;
protected:
	inline T*get_object() { if (m_CurObject) return reinterpret_cast<T*>(m_CurObject); if (m_data) return reinterpret_cast<T*>(m_data->Object); return 0; }
	const inline T*get_object()  const  { if (m_CurObject) return reinterpret_cast<T*>(m_CurObject); if (m_data) return reinterpret_cast<T*>(m_data->Object); return 0; }
public:
	BearFactoryPointer(void*data, void*CurObj) :m_data(reinterpret_cast<Data*>(data)), m_CurObject(CurObj), m_CurrentType(Impl::BearTypeManager::GetType<T>()) {  }
public:
	BearFactoryPointer() :m_data(0), m_CurObject(0){}
	BearFactoryPointer(T*c) :m_data(0), m_CurObject(0) { m_data = bear_new< Data>(reinterpret_cast<T*>(c), Impl::BearTypeManager::GetType<T>()); m_CurrentType = Impl::BearTypeManager::GetType<T>(); }
	inline void clear() 
	{ 
		if (m_data)
		{
			m_data->Count--;
			if (m_data->Count == 0)
			{
				bear_delete(m_data);
			}
			m_data = 0; m_CurObject= 0;
		}
	}
	inline ~BearFactoryPointer() { clear(); }
	inline	bool empty()const { if (m_data)return m_data->Object==0; return m_data == 0; }

	inline T*get() { return get_object(); }
	inline const T*get()const { return get_object(); }
	inline T&operator*() { BEAR_ASSERT(empty() == false)  return *get_object();}
	inline const T&operator*() const{ BEAR_ASSERT(empty() == false)   return *get_object();}
	inline T*operator->() {BEAR_ASSERT(empty()==false)   return get_object();}
	inline const T*operator->() const { BEAR_ASSERT(empty() == false)  return get_object();}

	template<typename C>
	inline BearFactoryPointer<C> cast() const
	{
		if (empty())
		{
			return  BearFactoryPointer<C>();
		}
		void* out = Impl::BearCasterObject::Cast(m_data->Object, m_data->ObjectType, Impl::BearTypeManager::GetType<C>());
		if (out)
		{
			m_data->Count++;

			BearFactoryPointer<C> result(reinterpret_cast<void*>(const_cast<Data*>(m_data)), out);
			return result;
		}
		else
		{
			BearFactoryPointer<C> result;
			return result;
		}
		
	}
		
	inline void replace(BearFactoryPointer&right)
	{
		if(right.empty()&& empty())return ;

		if (right.empty())
		{
			right.m_data = m_data =bear_new< Data>();
		}
		if (empty())
		{
				m_data = bear_new< Data>();
		}
		bear_swap(right.m_data->Object, m_data->Object);
		bear_swap(right.m_data->ObjectType, m_data->ObjectType);
	}
	inline void copy(const BearFactoryPointer&right)
	{
		clear();
		m_CurrentType = right.m_CurrentType;
		if (right.empty())return;
		m_data = right.m_data;
		m_data->Count++;
		m_CurObject = right.m_CurObject;
	}
	inline void swap(BearFactoryPointer&right)
	{
		bear_swap(m_CurrentType, right.m_CurrentType);
		bear_swap(m_data, right.m_data);
		bear_swap(m_CurObject, right.m_CurObject);
	}
	template<class C>
	BearFactoryPointer(const BearFactoryPointer<C>& right) :m_data(0) { auto temp = right.template  cast<T>(); swap(temp); ; }
	BearFactoryPointer(const BearFactoryPointer&right) :m_data(0) { copy(right); }
	BearFactoryPointer(BearFactoryPointer&&right) :m_data(0) { swap(right); }
	BearFactoryPointer&operator=(const BearFactoryPointer&right) { copy(right); return*this; }
	BearFactoryPointer&operator=(BearFactoryPointer&&right) { swap(right); return*this; }
	inline bool operator==(const BearFactoryPointer&right)const { return right.m_data == m_data; };
	inline bool operator!=(const BearFactoryPointer&right)const { return right.m_data != m_data; };
	inline bool operator<(const BearFactoryPointer&right)const { return right.m_data < m_data; };
	template<class C>
	inline C*StaticCast() { return static_cast<C*>(get_object()); }
};