#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll
using pii =pair<int,int>;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
#define FOR(i,b,x) for(int i=(b);i<(x);++i)
constexpr bool doTest = true;
//constexpr bool doTest = false;
constexpr int MAX_N=1e3+4, MAX_M=1e5, INF =0x3f3f'3f3f; //'3f3f'3f3f;
struct E{
    int nxt,to;
    int f;
}e[MAX_M];
int n,m,s,t;
int head[MAX_N], fir[MAX_N], dep[MAX_N];
int tot;
void add(int u,int v,int c){
    e[tot] ={head[u], v,c};
    head[u] = tot++;
}
void uadd(int u,int v,int c){ add(u,v,c), add(v,u,0); }

bool bfs(){
    memset(dep,0,(n+1)*sizeof(int));
    dep[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        for(int i=head[u];~i;i=e[i].nxt){
            int v =e[i].to;
            if(!dep[v] && e[i].f) dep[v] = dep[u] +1, q.push(v);
        }
    }
    return dep[t];
}
int dfs(int u,int f){
    if(u ==t || !f) return f;
    int ret = 0;
    for(int& i =fir[u];~i;i=e[i].nxt){
        int v =e[i].to, d;
        if(dep[v] ==dep[u] +1 && e[i].f && (d=dfs(v,min(f,e[i].f)))){
            e[i].f -= d, e[i^1].f += d;
            ret += d;
            f -=d;
            if(!f) return ret;
        }
    }
    return ret;
}
int dinic(){
    int f =0;
    while(bfs()){
        memcpy(fir,head,(n+1)*sizeof(int));
        f += dfs(s,INF);
    }
    return f;
}

void init(){
    int k,p,q;
    cin>>k>>p>>q;
    n =2*k+p+q+2;
    memset(head,0xff,(n+1)*sizeof(int));
    s = n-1, t =n;
    FOR(i,1,p+1) uadd(s,i+2*k,1);
    FOR(i,1,q+1) uadd(i+2*k+p,t,1);
    int c;
    FOR(i,1,k+1) FOR(j,1,p+1){
        cin>>c;
        if(c) uadd(j+2*k,i,1);
    }
    FOR(i,1,k+1) FOR(j,1,q+1){
        cin>>c;
        if(c) uadd(i+k,j+2*k+p,1);
    }
    FOR(i,1,k+1) uadd(i,i+k,1);
}
void solve(){
    init();
    int ans = dinic();
    cout<<ans<<endl;
}

