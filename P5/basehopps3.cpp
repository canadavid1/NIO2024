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

int uint64_log2(uint64_t n)
{
  #define S(k) if (n >= (UINT64_C(1) << k)) { i += k; n >>= k; }

  int i = -(n == 0); S(32); S(16); S(8); S(4); S(2); S(1); return i;

  #undef S
}



struct sparsetable
{
    v<v<it>> data;
    sparsetable(const v<it>& in)
    {
        data.push_back(in);
        for(int i = 0; data.back().size() > (1<<i); i++)
        {
            data.push_back({});
            for(int k = 0; k + (1<<i) < data[i].size(); k++)
            {
                data[i+1].push_back(max(data[i][k],data[i][k+(1<<i)]));
            }
        }
    }
    it query(it l, it r) const
    {
        if (l==r) return INT64_MIN;
        // max of [l,r)
        auto log = uint64_log2(r-l);
        return max(data[log][l],data[log][r-(1<<log)+1]);
    }    
};



int main()
{
    it N,M;
    std::cin >> N >> M;
    v<it> y(N);
    for(auto && i : y) std::cin >> i;
    
    v<it> yinc(N);
    for(int i = 0; i < N; i++) yinc[i] = y[i] + i;
    v<it> ydec(N);
    for(int i = 0; i < N; i++) ydec[i] = y[i] - i;

    const sparsetable yincseg(yinc);
    const sparsetable ydecseg(ydec);

    
    for(int fo = 0; fo < M; fo++)
    {
        int x;
        int h;
        std::cin >> x >> h;

        // right
        int th = h+x;
        int l = x;
        int r = N;
        while(r-l > 1)
        {
            int m = (l+r)/2;
            if (yincseg.query(x,m) <= th) l = m;
            else r = m;
        }
        int rightlen = l-x;

        // left
        th = h-x;
        l = -1;
        r = x;
        while(r-l > 1)
        {
            int m = (l+r)/2;
            if (ydecseg.query(m,x) <= th) r = m;
            else l = m;
        }
        int leftlen = x-r;
        std::cout << max(leftlen,rightlen) << "\n";

    }

    
}