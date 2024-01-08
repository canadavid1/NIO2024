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
    struct uf_helper
    {
        const unionfind& orig;
        int time;
        uf_helper(const unionfind& orig,int time) : time(time), orig(orig) {};

        int operator[](int num) const
        {
            const auto& t = orig.data[num];
            auto[_,v] = *std::lower_bound(t.rbegin(),t.rend(),time,[](auto a, auto b) {return a.first > b;});
            return v;
        }

        int find(int a)
        {
            auto b = (*this)[a];
            if (b < 0) return a;
            return find(b);   
        }
        bool isconnected(int a,int b)
        {
            return find(a)==find(b);
        }
    };
    v<v<p<int,int>>> data;
    int time = 0;
    unionfind(int num) : data(num,v<p<int,int>>{{-1,-1}}) {}; // time, value

    uf_helper operator[](int time) const
    {
        return uf_helper(*this,time);
    }
    uf_helper back() const
    {
        return uf_helper(*this,time);
    }

    bool unite_back(int a, int b)
    {
        a = back().find(a);
        b = back().find(b);
        if (a==b)
        {
            time++;
            return false;
        }
        int as = back()[a];
        int bs = back()[b];
        if (as == bs)
        {
            data[a].push_back({time,as-1});
        }
        if (as > bs) 
        {
            std::swap(a,b);
        }
        data[b].push_back({time,a});
        time++;
        return true;
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
    unionfind uf(N);
    for(auto[a,b] : tog) uf.unite_back(a,b);

    v<int> ct(K);
    for(auto[a,b] : fly)
    {
        int l = -1;
        int r = K;
        while (r-l > 1)
        {
            int m = (l+r)/2;
            if (uf[m].isconnected(a,b)) r = m;
            else l = m;
        }
        if (r < K) ct[r]++;
    }
    for(auto i : ct) std::cout << i << "\n";
}