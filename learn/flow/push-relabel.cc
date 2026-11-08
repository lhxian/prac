#include<bits/stdc++.h>
using namespace std;

constexpr int N =100, M =100, INF =0x3f3f'3f3f;

int n,m,s,t;
struct E{
    int nxt,to;
    int v;
}e[M];

int h[N], cnt;
int ht[N],gap[N],ex[N];
int stk[N];
int level;

int push(int u){
    bool init = u ==s;
    for(int i=h[u];~i;i=e[i].nxt){
        int v =e[i].to;
        int w =e[i].v;
        if(!w

    }
    return 1;
}
