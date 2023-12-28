# N과 M (1)  



### 문제 출처

 [15649번: N과 M (1) (acmicpc.net)](https://www.acmicpc.net/problem/15649)



### 풀이

N개의 수들 중에서 M개를 뽑았을 때 만들 수 있는 모든 경우의 수(수열) 을 출력해야 하는 문제.

- 매 depth 마다 `nextIndex` 번째 해당하는 수를 선택하는 DFS 함수를 제작
- M+1 번째 수를 선택하게 되는 상황에 도달했을 때, 선택한 수열을 출력

```cpp
#include <iostream>
#include <vector>

std::size_t g_N;
std::size_t g_M;
std::vector<bool> g_IsSelect( 9, false );
std::vector<std::size_t> g_Choices( 9, 0 );

static void DFS( const std::size_t nextIndex ) 
{
	if ( nextIndex > g_M )
	{
		for ( std::size_t i = 1; i <= g_M; ++i )
		{
			std::cout << g_Choices[ i ] << ' ';
		}
		std::cout << '\n';
		return;
	}

	for ( std::size_t i = 1; i <= g_N; ++i )
	{
		if ( ! g_IsSelect[ i ] )
		{
			g_IsSelect[ i ] = true;
			g_Choices[ nextIndex ] = i;
			DFS( nextIndex + 1 );
			g_IsSelect[ i ] = false;
		}
	}
}

int main()
{
	std::cin >> g_N >> g_M;
	DFS( 1 );
	return 0;
}
```

### 결과

![](image-20231228224800937.png)
