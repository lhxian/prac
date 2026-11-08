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
//constexpr bool doTest = true;
constexpr bool doTest = false;
constexpr int MAX_N=2e4+4, MAX_M=1e6, INF =0x3f3f'3f3f; //'3f3f'3f3f;
struct E{
    int nxt,to;
    int f;
}e[MAX_M];
int n,m,s,t;
int head[MAX_N], fir[MAX_N], dep[MAX_N];
int tot;
int N,M;
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

constexpr int MN =201;
int g[MN][MN],rid[MN][MN];
int r_cnt, c_cnt;
int row[MAX_N], col[MAX_N];
void init(){
    cin>>N>>M;
    memset(head,0xff,(2*N*M+2)*sizeof(int));
    FOR(i,1,N+1) FOR(j,1,M+1){
        cin>>g[i][j];
    }
    FOR(i,1,N+1){
        int pre = 0;
        FOR(j,1,M+1){
            if(g[i][j] == 0){
                if(!pre) row[++r_cnt] = i;
                rid[i][j] = r_cnt;
                pre = j;
            }else if(g[i][j] == 2) pre = 0;
        }
    }
    FOR(j,1,M+1){
        int pre = 0;
        FOR(i,1,N+1){
            if(g[i][j] == 0){
                if(!pre) col[++c_cnt+r_cnt] =j;
                assert(rid[i][j]);
                uadd(rid[i][j],c_cnt + r_cnt,1);
                pre = i;
            }else if(g[i][j] ==2) pre = 0;
        }
    }
    n = r_cnt + c_cnt +2;
    s = n-1, t =n;
    FOR(i,1,r_cnt+1) uadd(s,i,1);
    FOR(i,1,c_cnt+1) uadd(r_cnt + i,t,1);
    if constexpr(doTest){
        cout<<"graph: \n";
        FOR(u,1,n+1){
            cout<<u<<": ";
            for(int i =head[u];~i;i=e[i].nxt) cout<<e[i].to<<' ';
            cout<<endl;
        }
    }
}

void solve(){
    init();
    int ans = dinic();
    cout<<ans<<endl;
    FOR(u,1,r_cnt+1){
        for(int i =head[u];~i;i=e[i].nxt){
            if(!(i&1) && !e[i].f) cout<<row[u]<<' '<<col[e[i].to]<<'\n';
        }
    }
}

