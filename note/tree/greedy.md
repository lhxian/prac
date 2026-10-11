# 树上的一个贪心问题
[题目链接](https://www.luogu.com.cn/problem/P1084)

具体的方法是二分答案，需要注意在根节点贪心的步骤，容易得到错误的贪心方法，mark一下。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
using pii =pair<int,int>;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
#define FOR(i,b,x) for(int i=(b);i<(x);++i)
//constexpr bool doTest = true;
//constexpr bool doTest = false;
constexpr int MAX_N=1e5+1, MAX_M =MAX_N;
constexpr int INF=0x3f3f'3f3f;
struct E{
    int to,w;
    E(int to,int w): to(to),w(w){}
    bool operator <(const E& other) const{ return w < other.w; }
};
vector<vector<E>> g;
int n,m;
int pos[MAX_N], org[MAX_N];
constexpr int F_CNT=20;
int f[MAX_N][F_CNT];
ll r_t[MAX_N];
ll d[MAX_N];
void dfs0(int u,int p){
    f[u][0] =p;
    for(int i=1;i<F_CNT;++i) f[u][i] = f[f[u][i-1]][i-1];
    for(auto& e: g[u]){
        int v =e.to;
        if(v ==p) continue;
        d[v] = d[u] +e.w;
        dfs0(v,u);
    }
}
bool rd[MAX_N];
int bel[MAX_N],F[MAX_N];

void dfs1(int u,int p){
    bool flag = false, sub= true;
    for(auto& e: g[u]){
        int v =e.to;
        if(v ==p) continue;
        flag = true;
        dfs1(v,u);
        sub = sub && rd[v];
    }
    if(!rd[u]) rd[u]= flag && sub;
}
void dfs2(int u,int p,int rt){
    F[u] =rt;
    for(auto& e: g[u]) if(e.to != p) dfs2(e.to,u,rt);
}

bool check(ll t){
    memset(rd,0,n+1);
    for(int i=1;i<=m;++i){
        int c =org[i];
        ll a =t;
        for(int j=F_CNT-1;j>=0;--j){
            if(f[c][j] ==0) continue;
            ll dis = d[c]-d[f[c][j]];
            if(dis <= a) a -=dis, c =f[c][j];
        }
        pos[i] =c, r_t[i] =a;
        rd[c] =true;
    }
    dfs1(1,0);
    vector<pair<ll,int>> ms;
    for(int i =1;i<=m;++i){
        if(pos[i] ==1) ms.emplace_back(r_t[i],bel[i]);
    }
    sort(ms.begin(),ms.end());
    int k =0, n_cnt =g[1].size();
    const auto& es = g[1];
    for(auto& it: ms){
        while(k < n_cnt && rd[es[k].to]) ++k;
        if(k < n_cnt){
            if(it.first >= es[k].w && (rd[it.second] || it.first >= d[it.second])) ++k;
            else rd[it.second] =true;
        }

        if(k >= n_cnt) break;
    }
    while(k < n_cnt && rd[es[k].to]) ++k;
    return k >= n_cnt;
}

void solve(){
    cin>>n;
    g.resize(n+1);
    for(int i=1;i<n;++i){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    sort(g[1].begin(),g[1].end());
    dfs0(1,0);
    for(auto& e: g[1]) dfs2(e.to,1,e.to);
    cin>>m;
    for(int i=1;i<=m;++i) cin>>org[i],bel[i] =F[org[i]];
    if(m < g[1].size()) {
        cout<<"-1\n";
        return;
    }
    ll l=0, r =1e14;
    while(l <r){
        ll mid =(l +r)/2;
        if(check(mid)) r =mid;
        else l = mid+1;
    }
    cout<<r<<endl;

}

```
