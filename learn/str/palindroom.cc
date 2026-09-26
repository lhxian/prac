#include<bits/stdc++.h>
using namespace std;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
//constexpr bool doTest = true;
constexpr bool doTest = false;

int palindroom(string& s,vector<int>& l){
    if constexpr(doTest) cout<<"s: "<<s<<endl;
    int n=s.size(), cur =1;
    l[1]=0;
    for(int i=2;i<n;++i){
        int cen = cur;
        while(cur <i){
            l[cur] =min(i -1-cur, l[2*cen-cur]);
            if(l[cur]>= i-1-cur && s[i] == s[2*cur-i]) break;
            ++cur;
        }
        if(cur <i) ++l[cur];
    }
    for(int i=cur+1;i<n;++i) l[i] =min(n-i,l[2*cur-n-1]);
    int res =0;
    for(int i=1;i<n;++i) res= max(res,l[i]);
    if constexpr(doTest){
        for(int i=0;i<n;++i) cout<<l[i]<<" \n"[i==n-1];
    }
    return res;
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
