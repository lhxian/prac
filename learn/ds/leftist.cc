#include<bits/stdc++.h>
using namespace std;
constexpr int MAX_N =100;
struct Node{
    int val;
    int d,fa;
    int ch[2];
}t[MAX_N];
int merge(int x,int y){
    if(!x || !y) return x |y;
    if(t[x].val > t[y].val) swap(x,y);
    t[x].ch[1] =merge(t[x].ch[1],y);
    if(t[t[x].ch[1]].d > t[t[x].ch[0]].d) swap(t[x].ch[0],t[x].ch[1]);
    t[x].d =t[t[x].ch[1]].d +1;
    return x;
}

void pushup(int x){
    if(!x) return;
    if(t[x].d != t[t[x].ch[1]].d +1){
        t[x].d = t[t[x].ch[1]].d +1;
        pushup(t[x].fa);
    }
}

void earse(int x){
    int y =merge(t[x].ch[0],t[x].ch[1]);
    int fa =t[x].fa;
    t[y].fa = fa;
    t[fa].ch[t[fa].ch[1] == x] = y;
    pushup(t[y].fa);
}
