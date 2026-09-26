
#include<bits/stdc++.h>
using namespace std;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}

void solve(){
    
}

constexpr int N=100;
int tot;
struct Node{
    int son[26];
    int fail,cnt;
    int d;
    int ans;
}tr[N];

void build(){
    queue<int> q;
    for(int i=0;i<26;++i) if(tr[0].son[i]) q.push(tr[0].son[i]);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        int f =tr[u].fail;
        for(int i=0;i<26;++i){
            int s=tr[u].son[i];
            if(s){
                tr[s].fail =tr[f].son[i];
                tr[tr[f].son[i]].d++;
                q.push(s);
            }else tr[u].son[i] =tr[f].son[i];

        }
    }
}

void query(const char* t){
    int u=0, res=0;
    while(*t){
        u =tr[u].son[*t++ -'a'];
        ++tr[u].ans;
    }
}
void topo(){
    queue<int> q;
    for(int i=0;i<=tot;++i) if(tr[i].d ==0) q.push(i);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        int p =tr[u].fail;
        tr[p].ans += tr[u].ans;
        if(--tr[p].d ==0) q.push(p);
    }
}
