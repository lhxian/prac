#include<bits/stdc++.h>
using namespace std;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
void zf(string& s){
    int n =s.size();
    vector<int> z(n);
    for(int i=1,l=0,r=0;i<n;++i){
        if(i <=r && z[i-l] < r-i+1) z[i] =z[i -l];
        else{
            z[i] = max(0,r-i+1);
            while(i + z[i] <n && s[i+z[i]] ==s[z[i]]) ++z[i];
        }
        if(i+z[i] >= r) l =i, r =i +z[i] -1;
    }
    for(int i=0;i<n;++i) cout<<z[i]<<" \n"[i==n-1];
}

void solve(){
    int n;
    string s;
    cin>>n;
    while(n--){
        cin>>s;
        zf(s);
    }
}
