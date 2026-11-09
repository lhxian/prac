#include<bits/stdc++.h>
using namespace std;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
    int t;
    cin>>t;
	while(t--) solve();
}

void solve(){
    string s;
    int n;
    cin>>n>>s;
    stack<int> ro,sq;
    int ans = 0;
    int unk = 0;
    vector<char> vis(n);
    for(int i=0;i<n;++i){
        switch(s[i]){
            case '(': ro.push(i), vis[i] = 1; break;
            case '[': sq.push(i), vis[i] = 1; break;
            case ')':{
                if(!ro.empty()) {
                    int tp = ro.top();
                    vis[tp] = 0;
                    ro.pop();
                }
                else vis[i] = 1;
            }break;
            case ']':{
                if(!sq.empty()) {
                    int tp = sq.top();
                    vis[tp] =0;
                    sq.pop();
                }
                else vis[i] = 1;
            }break;
        }
    }
    int al =-1, ar= -1, bl = -1, br = -1;
    int lcnt = 0, rcnt = 0;
    for(int i =0;i<n;++i){
        if(!vis[i]) continue;
        if(s[i] =='(' || s[i] == '['){
            if(al == -1) al = i;
            ar= i;
            ++lcnt;
        }else {
            if(bl == -1) bl = i;
            br = i;
            ++rcnt;
        }
    }
    ans += lcnt/2 + rcnt/2;
    if(lcnt%2) {
        ++ans;
        if(al > br) ++ans;
    }
    cout<<ans<<'\n';
}
