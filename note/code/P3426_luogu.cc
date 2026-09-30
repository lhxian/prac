#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii =pair<int,int>;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
#define FOR(i,x) for(int i=0;i<(x);++i)
constexpr bool doTest = true;
//constexpr bool doTest = false;

void solve(){
    string s;
    cin>>s;
    int n =s.size();
    vector<int> pl(n+1), dp(n+1), bu(n+1);
    dp[1] =1;
    bu[1] =1;
    for(int i=2;i<=n;++i){
        int k=pl[i-1];
        while(k && s[i-1] != s[k]) k =pl[k];
        if(s[i-1] == s[k]) ++k;
        pl[i] =k;
        if(bu[dp[pl[i]]] >= i -pl[i]) dp[i] =dp[pl[i]];
        else dp[i] =i;
        bu[dp[i]] =i;
    }
    cout<<dp[n]<<endl;
}
