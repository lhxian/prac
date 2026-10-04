#include<bits/stdc++.h>
using namespace std;
int lowbit(int x){ return x&-x; }
vector<int> bt;
int n;
int getsum(int x){
    int ans =0;
    while(x){
        ans += bt[x];
        x -=lowbit(x);
    }
    return ans;
}

void add(int x,int k){
    while(x <= n){
        bt[x] += k;
        x += lowbit(x);
    }
}
void build(){
    for(int i=1;i<=n;++i){
        int p =i + lowbit(i);
        if(p <=n) bt[p] += bt[i];
    }
}
