#include<bits/stdc++.h>
using namespace std;
#define IT(i,A,x) for(i =A[x]; i !=x;i =A[i])
constexpr int MS=100;
int n,m,idx,fir[MS],sz[MS];
int L[MS],R[MS],U[MS],D[MS];
int col[MS], row[MS];

void remove(const int& c){
    int i,j;
    L[R[c]] =L[c], R[L[c]]=R[c];
    IT(i,D,c) IT(j,R,i) U[D[j]]=U[j], D[U[j]] =D[j],--sz[col[j]];
}
void recover(const int& c){
    int i,j;
    IT(i,U,c) IT(j,L,i) U[D[j]] =D[U[j]] =j, ++sz[col[j]];
    L[R[c]] =R[L[c]] =c;
}

void build(const int& r,const int& c){
    n=r, m =c;
    for(int i=0;i<=c;++i){
        L[i] =i-1,R[i] =i+1;
        U[i] =D[i] =i;
    }
    L[0] =c, R[c] =0, idx =c;
}
void insert(const int& r,const int&c){
    row[++idx] =r, col[idx] =c, ++sz[c];
    U[idx] =c, D[idx] =D[c],U[D[c]]=idx, D[c] =idx;
    if(!fir[r]){
        fir[r] =L[idx] =R[idx] =idx;
    }else{
        L[idx] =fir[r], R[idx] =R[fir[r]];
        L[R[fir[c]]] =idx,R[fir[r]] =idx;
    }
}

bool dance(int dep){
    int i,j,c =R[0];
    if(!R[0]){
        return true;
    }
    IT(i,R,0) if(sz[i] < sz[c]) c= i;
    remove(c);
    recover(c);
    return false;
}
