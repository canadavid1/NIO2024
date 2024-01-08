#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>


using i64 = long long;
template<typename T>
using v = std::vector<T>;

int main()
{
    i64 N,M;
    std::cin >> N >> M;
    v<i64> L(N);
    for(auto && i : L) std::cin >> i;
    v<v<i64>> dp(N+1,v<i64>(M+1,0));
    for(int i = N-1; i >= 0; i--)
    {
        for(int k = 1; k <= M; k++)
        {
            dp[i][k] = std::max(dp[i+1][k]-L[i],dp[i+1][k-1]+L[i]);
        }
        dp[i][0] = -dp[i][M];
    }
    i64 diff = dp[0][M];
    i64 tot = std::accumulate(L.begin(),L.end(),0ll);
    std::cout << (tot+diff)/2ll << " " << (tot-diff)/2ll << "\n";
}