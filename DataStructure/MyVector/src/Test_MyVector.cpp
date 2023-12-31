#include <gtest/gtest.h>
#include "MyVector.hpp"
#include "Test_MyVector.hpp"

constexpr std::size_t TEST_DATA_COUNT = 100;
constexpr int TEST_INT_DATA = 20;

// [기본 타입] count 개의 value 를 갖는 객체를 정상적으로 생성하는가?
TEST_F( Test_MyVector, MY_VECTOR_01 )
{
	MyVector<int> test_Vector{ TEST_DATA_COUNT, TEST_INT_DATA };
	EXPECT_EQ( test_Vector.size(), TEST_DATA_COUNT );

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == TEST_INT_DATA );
	}
}

// [사용자정의 타입] count 개의 value 를 갖는 객체를 정상적으로 생성하는가?
TEST_F( Test_MyVector, MY_VECTOR_02 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT, m_TestData };

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// 매개 변수 없이 객체 생성이 가능한가?
TEST_F( Test_MyVector, MY_VECTOR_03 )
{
	MyVector<int> empty_Vector;
	EXPECT_EQ( 0, empty_Vector.size() );
}

// 복사 생성자가 정상적으로 동작하는가?
TEST_F( Test_MyVector, MY_VECTOR_04 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT,m_TestData };
	MyVector<SimpleStruct> copy_Vector{ test_Vector };

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// 이동 생성자가 정상적으로 동작하는가?
TEST_F( Test_MyVector, MY_VECTOR_05 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT, m_TestData };
	MyVector<SimpleStruct> move_Vector{ std::move( test_Vector ) };

	EXPECT_EQ( move_Vector.size(), TEST_DATA_COUNT );

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( move_Vector[ i ] == m_TestData );
	}

	// Expired 객체 상태가 정의한 대로 Set 되었는지 체크.
	EXPECT_EQ( test_Vector.size(), 0 );
	EXPECT_EQ( test_Vector.capacity(), 0 );
	EXPECT_EQ( test_Vector.begin(), nullptr );
}

// [l-value]push_back 함수가 정상적으로 동작하는가?
TEST_F( Test_MyVector, MY_VECTOR_06 )
{
	MyVector<SimpleStruct> test_Vector; // capacity : 20

	for ( int i = 0; i < 40; ++i )
	{
		// push_back(l-value)
		test_Vector.push_back( m_TestData );
	}

	// capacity 는 2배가 되어 있어야 하고,
	EXPECT_EQ( test_Vector.capacity(), 40 );

	// 데이터 또한 정상적으로 적재되어야 함.
	for ( int i = 0; i < 20; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// [r-value]push_back 함수가 정상적으로 동작하는가?
TEST_F( Test_MyVector, MY_VECTOR_07 )
{
	MyVector<SimpleStruct> test_Vector; // capacity : 20

	for ( int i = 0; i < 40; ++i )
	{
		// push_back(r-value)
		test_Vector.push_back( SimpleStruct{ 1,2,"SampleStr" } );
	}

	// capacity 는 2배가 되어 있어야 하고,
	EXPECT_EQ( test_Vector.capacity(), 40 );

	// 데이터 또한 정상적으로 적재되어야 함.
	for ( int i = 0; i < 40; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}