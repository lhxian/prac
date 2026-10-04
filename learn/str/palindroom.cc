#include<bits/stdc++.h>
using namespace std;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
//constexpr bool doTest = true;
constexpr bool doTest = false;

int palindroom(string& s,vector<int>& d){
    int ans =0, n =s.size();
    for(int i=0,l =0,r =-1;i<n;++i){
        int k =(i >r)? 1: min(d[l+r-i],r -i+1);
        while(i-k >=0 && i+k <n && s[i-k] ==s[i+k]) ++k;
        d[i] =k--;
        if(i+k >r) r =i+k, l=i-k;
    }
    return ans;
}

void solve(){
    string raw;
    cin>>raw;
    string s;
    s.reserve(raw.size()*2+4);
    s.push_back('^');
    s.push_back('#');
    for(char c: raw) s.push_back(c),s.push_back('#');
    s.push_back('$');
    vector<int> l(s.size());
    int ans =palindroom(s,l);
    cout<<ans<<endl;
}
