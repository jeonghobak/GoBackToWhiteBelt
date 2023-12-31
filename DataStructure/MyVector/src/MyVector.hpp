#pragma once
#include <algorithm>
#include <memory>
#include <new>

template<typename T, typename Allocator = std::allocator<T>>
class MyVector
{
private:
	static constexpr size_t DEFAULT_CAPACITY_SIZE = 10;

public:
	using value_type = T;
	using iterator = value_type*;

	explicit MyVector( const size_t count,
					   const value_type value,
					   const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( count );		
		m_Size = count;
		std::uninitialized_fill( begin(), end(), value );
	}

	explicit MyVector( const size_t count = DEFAULT_CAPACITY_SIZE,
					   const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( count );
	}

	MyVector( const MyVector& _Other,
			  const Allocator& alloc = Allocator() )
		: m_Allocator( alloc )
	{
		AllocCapacity( _Other.m_CapacitySize );
		std::uninitialized_copy( _Other.begin(), _Other.end(), m_pData );
		m_Size = _Other.size();
	}

	MyVector( MyVector&& _Other ) noexcept
	{
		std::swap( m_CapacitySize, _Other.m_CapacitySize );
		std::swap( m_Size, _Other.m_Size );
		std::swap( m_pData, _Other.m_pData );
		std::swap( m_Allocator, _Other.m_Allocator );
	}

	~MyVector()
	{
		DeAllocateCapacity();
	}

	MyVector& operator=( const MyVector& _Other )
	{
		if ( this != &_Other )
		{
			DeAllocateCapacity();

			m_pData = m_Allocator.allocate( _Other.m_CapacitySize );
			std::uninitialized_copy( _Other.begin(), _Other.end(), m_pData );
			m_CapacitySize = _Other.m_CapacitySize;
			m_Size = _Other.m_Size;
		}
		return *this;
	}
	
	MyVector& operator=( MyVector&& _Other ) noexcept
	{
		if ( this != &_Other )
		{
			std::swap( m_CapacitySize, _Other.m_CapacitySize );
			std::swap( m_Size, _Other.m_Size );
			std::swap( m_pData, _Other.m_pData );
			std::swap( m_Allocator, _Other.m_Allocator );
		}
		return *this;
	}

	T& operator[]( const size_t idx )
	{
		return m_pData[ idx ];
	}

	const T& operator[]( const size_t idx ) const
	{
		return m_pData[ idx ];
	}

	template<class... ArgTypes>
	auto emplace_back( ArgTypes&&... args )
	{
		if ( ( m_Size + 1 ) > m_CapacitySize )
		{
			ExpendCapacity();
		}

		::new( end() )T( std::forward<ArgTypes>( args )... );
		m_Size++;
	}

	auto push_back( const T& data ) -> void
	{
		if ( ( m_Size + 1 ) > m_CapacitySize )
		{
			ExpendCapacity();
		}

		emplace_back( data );
	}

	auto push_back( T&& data ) -> void
	{
		if ( ( m_Size + 1 ) > m_CapacitySize )
		{
			ExpendCapacity();
		}

		emplace_back( std::forward<T>( data ) );
	}

	auto begin() const noexcept->iterator
	{
		return m_pData;
	}
	
	auto end() const noexcept->iterator
	{
		return m_pData + m_Size;
	}

	auto size() const noexcept->size_t
	{
		return m_Size;
	}

	auto capacity() const noexcept->size_t
	{
		return m_CapacitySize;
	}

private:
	auto AllocCapacity( const size_t count ) -> void
	{
		m_pData = m_Allocator.allocate( count );
		m_CapacitySize = count;
	}

	auto DeAllocateCapacity() -> void
	{
		std::destroy( begin(), end() );
		m_Allocator.deallocate( begin(), m_CapacitySize );
	}

	auto ExpendCapacity() -> void
	{
		const size_t newCapacitySize = m_CapacitySize * 2;
		value_type* pNew = m_Allocator.allocate( newCapacitySize );

		if constexpr ( std::is_move_constructible<T>::value )
		{
			std::uninitialized_move( begin(), end(), pNew );
		}
		else
		{
			std::uninitialized_copy( begin(), end(), pNew );
		}
		
		DeAllocateCapacity();

		m_pData = pNew;
		m_CapacitySize = newCapacitySize;
	}

	size_t m_CapacitySize{ 0 };
	size_t m_Size{ 0 };
	value_type* m_pData{ nullptr };
	Allocator m_Allocator;
};