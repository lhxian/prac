#include <algorithm>
#include <queue>
#include<vector>
using namespace std;

constexpr int N=100;
int n,s,t;

struct Edge{
    int from, to;
    int cap, flow;
    Edge(int from,int to,int cap,int flow): from(from), to(to),cap(cap),flow(flow) {}
};

vector<Edge> edges;
vector<int> G[N];
vector<int> level;
vector<int> cur;

void add(int from,int to,int cap){
    edges.push_back(Edge(from,to,cap,0));
    edges.push_back(Edge(to,from,0,0));
    int m =edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}

bool bfs(){
    std::fill(level.begin(),level.end(),0);
    queue<int> q;
    q.push(s);
    level[s] =1;
    while(!q.empty()){
        int u =q.front();
        q.pop();
        for(int i: G[u]){
            int v=edges[i].to;
            if(level[v] || edges[i].cap == edges[i].flow) continue;
            level[v] =level[u]+1;
            q.push(v);
        }
    }
    return level[t] !=0;
}

int dfs(int u,int f){
    if(u ==t) return f;
    // find the target flow
    int res =0;
    for(int i: G[u]){
        int v=edges[i].to;
        if(level[v] != level[u] +1 || edges[i].cap == edges[i].flow) continue;
        // child and has rest
        int add_f =dfs(v,min(f,edges[i].cap -edges[i].flow));
        edges[i].flow += add_f;
        edges[i^1].flow -= add_f;
        f -= add_f;
        res += add_f;
        if(f ==0) break;
    }
    return res;
}

constexpr int inf =1e9;
int dinic(){
    int flow =0;
    while(bfs()){
        std::fill(cur.begin(),cur.end(),0);
        flow += dfs(s,inf);
    }
    return flow;
}