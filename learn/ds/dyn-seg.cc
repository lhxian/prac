#include<bits/stdc++.h>
using namespace std;

vector<array<int,2>> ch;
vector<int> tr;
int rt,id,L,R;
void update(int& cr,int l,int r,int x,int v){
    if(!cr) cr = ++id;
    if(l ==r){
        tr[cr] =v;
        return;
    }
    int mid =(l+r)/2;
    if(mid >= x) update(ch[cr][0],l,mid,x,v);
    else update(ch[cr][1],mid+1,r,x,v);
}
int query(int cr,int l,int r,int s,int t){
    if(l >=s && r <=t) return tr[cr];
    int mid =(l+r)/2;
    int ret =0;
    if(mid >=s ) ret += query(ch[cr][0],l,mid,s,t);
    if(mid <t) ret += query(ch[cr][1],mid+1,r,s,t);
    return ret;
}
