#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii =pair<int,int>;
void solve();
signed main(){
	cin.tie(0)->sync_with_stdio(false);
	solve();
}
#define FOR(i,b,x) for(int i=(b);i<(x);++i)
//constexpr bool doTest = true;
constexpr bool doTest = false;
constexpr int SON_CNT=26+1;
constexpr char C='z'+1;
struct Node{
    int next[SON_CNT];
    int fail;
    int cnt;
};
vector<Node> tr;
void add_c(int i,int& cur){
    if constexpr(doTest) cout<<(char)(i+'a');
    if(!tr[cur].next[i]) tr[cur].next[i] =tr.size(), tr.emplace_back();
    cur =tr[cur].next[i];
}
void insert(string& a,string& b){
    if constexpr(doTest) cout<<"add: ";
    int cur =0,i =0,n =a.size(), post =n-1;
    for(;post>=0 && a[post] ==b[post];--post) ;

    for(;i<n && a[i] ==b[i];++i) add_c(a[i] -'a',cur);
    add_c(C-'a',cur);
    for(int j=i;j<=post;++j) add_c(a[j]-'a',cur);
    for(int j=i;j<=post;++j) add_c(b[j]-'a',cur);
    add_c(C-'a',cur);
    for(i=max(i,post+1);i<n;++i) add_c(a[i]-'a',cur);

    tr[cur].cnt++;
    if constexpr(doTest) cout<<'\n';
}
void ac_build(){
    queue<int> q;
    FOR(i,0,SON_CNT) if(tr[0].next[i]) q.push(tr[0].next[i]);
    while(!q.empty()){
        int u =q.front();
        q.pop();
        int f =tr[u].fail;
        FOR(i,0,SON_CNT){
            int& s =tr[u].next[i];
            if(s){
                tr[s].fail =tr[f].next[i];
                if constexpr(doTest) cout<<"fail: "<<s<<' '<<tr[s].fail<<' '<<tr[tr[s].fail].cnt<<'\n';
                tr[s].cnt += tr[tr[s].fail].cnt;
                q.push(s);
            }else s =tr[f].next[i];
        }
    }
}
string get_s(string& s,string& t){
    string p;
    p.reserve(s.size() +t.size() +4);
    int i =0, n =s.size();
    int post =n-1;
    for(;post>=0 && s[post] ==t[post];--post);
    for(;i<n && s[i] ==t[i];++i) p.push_back(s[i]);
    p.push_back(C);
    for(int j =i;j<=post;++j) p.push_back(s[j]);
    for(int j =i;j<=post;++j) p.push_back(t[j]);
    p.push_back(C);
    for(i =max(i,post+1);i<n;++i) p.push_back(s[i]);

    if constexpr(doTest) cout<<"P: "<<p<<'\n';

    return p;
}
int calc(string& s){
    int ans =0, cur =0;
    for(char c:s){
        cur =tr[cur].next[c -'a'];
        ans += tr[cur].cnt;
    }

    return ans;
}

void solve(){
    int n,q;
    cin>>n>>q;
    string a,b;
    string s,t;
    tr.resize(1);
    for(int i=0;i<n;++i){
        cin>>a>>b;
        insert(a,b);
    }
    ac_build();
    while(q--){
        cin>>s>>t;
        auto p =get_s(s,t);
        cout<<calc(p)<<'\n';
    }
    if constexpr(doTest){
        cout<<"cnt: \n";
        for(int i=0;i<tr.size();++i) cout<<i<<' '<<tr[i].cnt<<'\n';
    }
}
