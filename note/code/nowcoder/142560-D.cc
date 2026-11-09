#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii =pair<int,int>;
#define FOR(i,s,e) for(int i=s;i<e;++i)
//constexpr bool doTest = true;
constexpr bool doTest = false;
constexpr int INF = 0x3f3f'3f3f;

void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
    int t;
    cin>>t;
	while(t--) solve();
}
constexpr int MAX_N=604, MAX_M =1e4;
struct E{
    int nxt,to;
}e[MAX_M];
int tot;
int head[MAX_N];
int d[MAX_N][MAX_N], f[MAX_N][MAX_N];
int n,s,t;

void add(int u,int v){
    e[tot] = {head[u],v};
    head[u] = tot++;
}

void bfs(int src,int* dis){
    queue<int> q;
    q.push(src);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        for(int i=head[u];~i;i=e[i].nxt){
            int v =e[i].to;
            if(v != src && !dis[v]) dis[v]=dis[u]+1, q.push(v);
        }
    }
}

void solve(){
    int m,k;
    cin>>n>>m>>s>>t>>k;
    tot =0;
    memset(head,0xff,(n+1)*sizeof(int));
    FOR(i,0,n+1) memset(f[i],0,(n+1)*sizeof(int));
    FOR(i,1,n+1){
        memset(d[i],0,(n+1)*sizeof(int));
        bfs(i,d[i]);
    }
    FOR(i,0,m){
        int u,v;
        cin>>u>>v;
        add(u,v), add(v,u);
    }
    FOR(i,1,n+1) bfs(i,d[i]);
    queue<pii> q;
    q.push({s,t});
    f[s][t]= 1;
    while(!q.empty()){
        auto tp = q.front();
        q.pop();
        int a = tp.first, b =tp.second;
        for(int i=head[a];~i;i=e[i].nxt){
            int v =e[i].to;
            if(v!= b && d[v][b] <=k){
                if(!f[v][b]) {
                    if(v == t && b == s) {
                        cout<<f[a][b]<<'\n';
                        return;
                    }
                    f[v][b] =f[a][b] +1, q.push({v,b});
                }
            }
        }
        for(int i=head[b];~i;i=e[i].nxt){
            int v =e[i].to;
            if(v!= a && d[a][v] <=k){
                if(!f[a][v]) {
                    f[a][v] =f[a][b] +1, q.push({a,v});
                    if(a == t && v == s) {
                        cout<<f[a][b]<<'\n';
                        return;
                    }
                }
            }
        }
    }
    cout<<"-1\n";

}

