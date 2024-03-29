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
    unionfind(int num)
    {
        data.assign(num,-1);
    };
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
        if (data[a]==data[b]) data[b]--;
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
    while (m <= N) m <<= 1;
    int TOTM = m;
    tog.resize(TOTM+1,{0,0});
    m >>= 1;
    v<p<int,int>> flytime;
    flytime.reserve(M);
    for(int i = 0; i < M; i++) flytime.push_back({i,m});
    m >>= 1;
    for(;m > 0; m>>=1)
    {
        unionfind uf(N);
        v<p<int,int>> flytime2;
        flytime2.reserve(M);
        int k = 0;
        for(int i = 0; k < flytime.size(); i++)
        {
            v<p<int,int>> up;
            while(k < flytime.size() && flytime[k].second == i)
            {
                auto[a,b] = fly[flytime[k].first];
                if(uf.connected(a,b))
                    flytime2.push_back({flytime[k].first,flytime[k].second-m});
                else
                    up.push_back({flytime[k].first,flytime[k].second+m});
                k += 1;
            }
            for(auto & j : up) flytime2.push_back(j);
            uf.unite(tog[i].first,tog[i].second);
        }
        flytime = std::move(flytime2);
    }
    v<int> ct(TOTM,0);
    for(auto i : flytime) ct[i.second]++;
    for(int i = 0; i <K; i++) std::cout << ct[i] << "\n";
    
}