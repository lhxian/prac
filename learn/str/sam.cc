#include<bits/stdc++.h>
using namespace std;

constexpr int N =100;
struct state{
    int len, link;
    map<char,int> next;
};

state st[N];
int sz, last;
void sam_init(){
    st[0].link =-1;
    sz =1;
}

void sam_extentd(char c){
    int cur =sz++;
    st[cur].len = st[last].len +1;
    int p =last;
    while(p != -1 && !st[p].next.count(c)){
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p ==-1){
        st[cur].link =0;
    }else{
        int q= st[p].next[c];
        if(st[q].len == st[p].len +1){
            st[cur].link = q;
        }else{
            int clone = sz++;
            st[clone].len = st[p].len +1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while(p != -1 && st[p].next[c] == q){
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[cur].link =st[q].link = clone;
        }
    }
    last = cur;
}
