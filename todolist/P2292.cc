#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
//constexpr bool doTest = true;
constexpr bool doTest = false;

constexpr int SON_CNT=26, MAX_N=512;
constexpr int MAX_T=2e6+2;
struct Node{
    int next[SON_CNT];
    int fail;
    int hasStr,len;
}tr[MAX_N];
int tot;
bool vis[MAX_T];
void insert(string& s){
    int cur =0;
    for(char c: s){
        int i=c -'a';
        if(!tr[cur].next[i]) {
            tr[cur].next[i] =++tot;
            tr[tot].len =tr[cur].len +1;
        }
        cur =tr[cur].next[i];
    }
    tr[cur].hasStr=1;
    tr[cur].len =s.size();
}

void ac_build(){
    queue<int> q;
    for(int i=0;i<SON_CNT;++i) if(tr[0].next[i]) q.push(tr[0].next[i]);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        int f= tr[u].fail;
        for(int i=0;i<SON_CNT;++i){
            int s=tr[u].next[i];
            if(s){
                tr[s].fail =tr[f].next[i];
                q.push(s);
            }else tr[u].next[i] =tr[f].next[i];
        }
    }
}

int calc(string& s){
    int cur =0;
    memset(vis,0,s.size()+1);
    vis[0] =true;
    for(int i=0;i<s.size();++i){
        int idx =s[i] -'a';
        cur =tr[cur].next[idx];
        if(!cur) break;
        int tmp =cur;
        if constexpr(doTest) cout<<"cur: "<<cur<<", fail: "<<tr[cur].fail<<'\n';
        while(tmp){
            if constexpr(doTest) cout<<"tmp: "<<tmp<<'\n';
            if(tr[tmp].hasStr && vis[i+1-tr[tmp].len]){
                if constexpr(doTest) cout<<"get: "<<i+1<<'\n';
                vis[i+1] =1;
                break;
            }
            tmp =tr[tmp].fail;
        }
    }
    int res =0;
    for(int i=1;i<=s.size();++i) if(vis[i]) res = i;
    return res;
}

void solve(){
    int n,m;
    cin>>n>>m;
    string s;
    for(int i=0;i<n;++i){
        cin>>s;
        insert(s);
    }
    ac_build();
    while(m--){
        cin>>s;
        cout<<calc(s)<<'\n';
    }
}
