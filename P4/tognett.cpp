#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>


using it = long long;
template<typename T>
using v = std::vector<T>;
template<typename U,typename V>
using p = std::pair<U,V>;
using std::max;


struct unionfind
{
    v<int> data;
    unionfind(int num) : data(num,-1) {};
    int find(int num)
    {
        if (data[num] < 0) return num;
        data[num] = find(data[num]);
        return data[num];
    }
    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a==b) return false;
        if (data[a] < data[b]) std::swap(a,b);
        if (data[a]==data[b]) data[b]++;
        data[a] = b;
        return true;
    }
    bool connected(int a,int b)
    {
        return find(a)==find(b);
    }
};

int main()
{
    int N,M,K;
    std::cin >> N >> M >> K;
    v<p<int,int>> fly(M);
    for(auto && i : fly) std::cin >> i.first >> i.second;
    v<p<int,int>> tog(K);
    for(auto && i : tog) std::cin >> i.first >> i.second;
    int m = 1;
    while (m < N) m <<= 1;
    m >>= 1;
    
}