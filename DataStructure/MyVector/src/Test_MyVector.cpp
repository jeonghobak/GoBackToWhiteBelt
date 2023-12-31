#include <gtest/gtest.h>
#include "MyVector.hpp"
#include "Test_MyVector.hpp"

constexpr std::size_t TEST_DATA_COUNT = 100;
constexpr int TEST_INT_DATA = 20;

// [�⺻ Ÿ��] count ���� value �� ���� ��ü�� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_01 )
{
	MyVector<int> test_Vector{ TEST_DATA_COUNT, TEST_INT_DATA };
	EXPECT_EQ( test_Vector.size(), TEST_DATA_COUNT );

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == TEST_INT_DATA );
	}
}

// [��������� Ÿ��] count ���� value �� ���� ��ü�� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_02 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT, m_TestData };

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// �Ű� ���� ���� ��ü ������ �����Ѱ�?
TEST_F( Test_MyVector, MY_VECTOR_03 )
{
	MyVector<int> empty_Vector;
	EXPECT_EQ( 0, empty_Vector.size() );
}

// ���� �����ڰ� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_04 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT,m_TestData };
	MyVector<SimpleStruct> copy_Vector{ test_Vector };

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// �̵� �����ڰ� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_05 )
{
	MyVector<SimpleStruct> test_Vector{ TEST_DATA_COUNT, m_TestData };
	MyVector<SimpleStruct> move_Vector{ std::move( test_Vector ) };

	EXPECT_EQ( move_Vector.size(), TEST_DATA_COUNT );

	for ( int i = 0; i < TEST_DATA_COUNT; ++i )
	{
		EXPECT_TRUE( move_Vector[ i ] == m_TestData );
	}

	// Expired ��ü ���°� ������ ��� Set �Ǿ����� üũ.
	EXPECT_EQ( test_Vector.size(), 0 );
	EXPECT_EQ( test_Vector.capacity(), 0 );
	EXPECT_EQ( test_Vector.begin(), nullptr );
}

// [l-value]push_back �Լ��� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_06 )
{
	MyVector<SimpleStruct> test_Vector; // capacity : 20

	for ( int i = 0; i < 40; ++i )
	{
		// push_back(l-value)
		test_Vector.push_back( m_TestData );
	}

	// capacity �� 2�谡 �Ǿ� �־�� �ϰ�,
	EXPECT_EQ( test_Vector.capacity(), 40 );

	// ������ ���� ���������� ����Ǿ�� ��.
	for ( int i = 0; i < 20; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}

// [r-value]push_back �Լ��� ���������� �����ϴ°�?
TEST_F( Test_MyVector, MY_VECTOR_07 )
{
	MyVector<SimpleStruct> test_Vector; // capacity : 20

	for ( int i = 0; i < 40; ++i )
	{
		// push_back(r-value)
		test_Vector.push_back( SimpleStruct{ 1,2,"SampleStr" } );
	}

	// capacity �� 2�谡 �Ǿ� �־�� �ϰ�,
	EXPECT_EQ( test_Vector.capacity(), 40 );

	// ������ ���� ���������� ����Ǿ�� ��.
	for ( int i = 0; i < 40; ++i )
	{
		EXPECT_TRUE( test_Vector[ i ] == m_TestData );
	}
}