#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
constexpr int MAXN=250;
constexpr int INF= 0x3f3f3f3f;


struct Edge{
    int from, to, cap, flow;
    Edge(int u,int v,int c,int f): from(u), to(v), cap(c), flow(f) {}
};

struct EK{
    int n,m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int a[MAXN], p[MAXN];

    void init(int n){
        // TODO
    }
    void AddEdge(int from,int to, int cap){
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int MaxFlow(int s,int t){
        int flow = 0;
        for(;;){
            memset(a,0,sizeof(a));
            queue<int> Q;
            Q.push(s);
            while(!Q.empty()){
                int x = Q.front();
                Q.pop();
                for(int i =0;i<G[x].size();++i){
                    auto& e = edges[G[x][i]];
                    if(!a[e.to] && e.cap > e.flow){
                        p[e.to] = G[x][i];
                        a[e.to] = max(a[x],e.cap - e.flow);
                        Q.push(e.to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u =t; u !=s;u =edges[p[u]].from){
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }

};