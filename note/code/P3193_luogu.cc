#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
constexpr bool doTest = true;
//constexpr bool doTest = false;

using mat =vector<vector<int>>;
void matmul(mat& dst,const mat& a,const mat&b,int mod){
    int n =a.size(), mid =a[0].size(), m=b[0].size();
    for(int i=0;i<n;++i) for(int j=0;j<m;++j){
        dst[i][j] =0;
        for(int k=0;k<mid;++k) dst[i][j] =(dst[i][j] +a[i][k] *b[k][j]) %mod;
    }
}

void solve(){
    int N,n,K;
    string s;
    cin>>N>>n>>K>>s;
    vector<mat> ms(2,mat(n,vector<int>(n))), res(2,mat(n,vector<int>(n)));
    auto& g =ms[0];
    int ms_idx =0, res_idx =0;
    for(int i=0;i<n;++i) res[0][i][i] =1;
    vector<int> pl(n+1);
    for(int i=2;i<=n;++i){
        int k =pl[i-1];
        while(k && s[i-1] != s[k]) k =pl[k];
        if(s[i-1] == s[k]) ++k;
        pl[i] = k;
    }
    for(int j=0;j<n;++j){
        for (int c = 0; c <= 9; ++c) {
            int k = j;
            while (k && s[k] != char('0' + c))
                k = pl[k];

            if (s[k] == char('0' + c))
                ++k;

            if (k < n)
                ++g[k][j];
        }
    }
    if constexpr(doTest){
        cout<<"s : ";
        for(int i=1;i<=n;++i) cout<<s[i-1]<<" \n"[i==n];
        cout<<"pl: ";
        for(int i=1;i<=n;++i) cout<<pl[i]<<" \n"[i==n];
        cout<<"g:\n";
        for(int i=0;i<n;++i) for(int j=0;j<n;++j) cout<<g[i][j]<<" \n"[j==n-1];
    }
    --N;
    while(N){
        if(N&1){ // res = res @ ms
            matmul(res[res_idx^1],res[res_idx],ms[ms_idx],K);
            res_idx ^=1;
        }
        N >>=1;
        matmul(ms[ms_idx^1],ms[ms_idx],ms[ms_idx],K);
        ms_idx ^=1;
    }
    vector<int> v1(n);
    v1[0] =9;
    if(n >1) v1[1] =1;
    int ans =0;
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) ans =(ans +res[res_idx][i][j] *v1[j]) %K;
    cout<<ans<<endl;
}
