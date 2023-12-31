#pragma once
#include <string>

struct SimpleStruct
{
	int a;
	int b;
	std::string sample_str;

	bool operator==( const SimpleStruct& other ) const noexcept
	{
		if ( ( this == &other ) ||
			 ( this->a == other.a && this->b == other.b && this->sample_str == other.sample_str ) )
		{
			return true;
		}

		return false;
	}
};

class Test_MyVector : public testing::Test
{
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}

	SimpleStruct m_TestData{ 1,2,"SampleStr" };
};