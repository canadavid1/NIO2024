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

    int dfsdepth = 0;
    Node* low;
    Node* dfspar;
    v<Node*> child;
    v<Node*> upedge;
    v<Node*> downedge;
    bool incycle = false;
    int cyclesdown = 0;
    int cyclesup = 0;
};

struct Node2
{};

static Node sentinel;

void dfs(Node* curr,Node* par=&sentinel,int d = 0)
{
    curr->dfspar = par;
    curr->dfsdepth = d;
    v<Node*> other;
    for(auto i : curr->neigh)
    {
        if (i==par) continue;
        if (i->dfspar)
        {
            curr->upedge.push_back(i);
            i->downedge.push_back(curr);
            continue;
        }
        other.push_back(i);
    }
    for(auto i : other)
    {
        if (i->dfspar) continue;
        curr->child.push_back(i);
        dfs(i,curr,d+1);
    }
}

void lowdfs(Node* curr)
{
    for(auto c : curr->child) lowdfs(c);
    curr->low = curr;
    for(auto c : curr->child) if (c->low->dfsdepth < curr->low->dfsdepth) curr->low = c->low;
    for(auto i : curr->upedge) if (i->dfsdepth < curr->low->dfsdepth) curr->low = i;
}

template<typename F>
void post_dfs(Node* curr, F func)
{
    for(auto c: curr->child) post_dfs(c,func);
    func(curr);
}
template<typename F>
void pre_dfs(Node* curr,  F func)
{
    func(curr);
    for(auto c: curr->child) pre_dfs(c,func);
}

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

    // make dfs tree
    dfs(&nodes[0]);
    nodes[0].dfspar = nullptr; // remove sentinel value

    lowdfs(&nodes[0]);

    for(auto& node : nodes)
    {
        node.incycle = node.downedge.size() || node.low != &node;
    }
    post_dfs(&nodes[0],[](Node* curr){
        if (curr->incycle) {curr->cyclesdown = 1;return;}
        curr->cyclesdown = 0;
        for(auto c : curr->child)
        {
            if (c->cyclesdown) curr->cyclesdown++;
        }
    });

    pre_dfs(&nodes[0],[](Node* curr){
        if (curr->dfspar==nullptr) return;
        curr->cyclesup = curr->dfspar->cyclesdown+curr->dfspar->cyclesup - (curr->cyclesdown > 0) > 0;
    });
    
    if(nodes[0].cyclesdown <= 1 && !nodes[0].incycle) std::cout << "0\n";
    for(int i = 1; i < N; i++)
    {
        if (nodes[i].incycle || nodes[i].cyclesdown+nodes[i].cyclesup > 1) continue;
        std::cout << i << "\n";
    }
}