#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <unordered_map>


using it = long long;
template<typename T>
using v = std::vector<T>;
template<typename U,typename V>
using p = std::pair<U,V>;
using std::max;
using std::min;

struct Node
{    
    v<Node*> neigh;
};

int main()
{
    int N,M;
    std::cin >> N >> M;
    v<Node> nodes(N);
    for(int i = 0; i < M; i++)
    {
        int a,b;
        std::cin >> a >> b;
        nodes[a].neigh.push_back(&nodes[b]);
        nodes[b].neigh.push_back(&nodes[a]);
    }
    v<Node*> o;
    for(auto& n : nodes) if(n.neigh.size()<2) o.push_back(&n);
    
}