#include<bits/stdc++.h>
using namespace std;


struct SAM {
    static const int maxn = 5e5 + 5;
    int nxt[maxn][3], to[maxn], len[maxn];
    int root, last, sz;
    int gnode(int x) {
        for (int i = 0; i < 3; ++i) nxt[sz][i] = -1;
        to[sz] = -1;
        len[sz] = x;
        return sz++;
    }
    void init() {
        sz = 0;
        root = gnode(0);
        last = root;
    }
    void push(int c) {
        int cur = last;
        last = gnode(len[last] + 1);
        for (; ~cur && nxt[cur][c] == -1; cur = to[cur]) nxt[cur][c] = last;
        if (cur == -1) return to[last] = root, void();
        int link = nxt[cur][c];
        if (len[link] == len[cur] + 1) return to[last] = link, void();
        int tlink = gnode(len[cur] + 1);
        for (; ~cur && nxt[cur][c] == link; cur = to[cur]) nxt[cur][c] = tlink;
        for (int i = 0; i < 3; ++i) nxt[tlink][i] = nxt[link][i];
        to[tlink] = to[link];
        to[link] = tlink;
        to[last] = tlink;
    }
    void add(const string &s) {
        for (int i = 0; i < s.size(); ++i) push(s[i] - 'a');
    }
    long long solve(const string &s, const string &t, vector<int> &mx) {
        long long ans = 0;
        int cnt = 0, res = 0;
        int cur = root;
        for (int i = 0; i < t.size(); ++i) {
            if (~nxt[cur][t[i] - 'a']) {
                ++cnt;
                cur = nxt[cur][t[i] - 'a'];
            } else {
                for (; ~cur && nxt[cur][t[i] - 'a'] == -1; cur = to[cur]);
                if (~cur) cnt = len[cur] + 1, cur = nxt[cur][t[i] - 'a'];
                else cnt = 0, cur = root;
            }
            res = max(res, cnt);
            ans += cnt;
            // cout << i << " cnt = " << cnt << " res = " << res << " len = " << len[cur] << endl;
            mx[i] = max(mx[i], cnt);
            push(s[i] - 'a');
        }
        return ans;
    }
} sam;

/* int BF(string s){
    for (int i = 0; i < int(s.size()); ++i) {
        for (int j = i; j < int(s.size()); ++j) {

        }
    }
} */

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while(cin>>n) {
        string s; cin>>s;
        vector<int> mx(s.size(), 0);
        // sam.init();
        // sam.add(s);
        string p="abc";
        do{
            string t; 
            for(char c:s)t+=p[c-'a'];
            sam.init();
            sam.solve(t, s, mx);
            // cout<<t<<" "<<sam.solve(t)<<endl;
        }while(next_permutation(p.begin(),p.end()));
        // cout<<"bf ans: "<<BF(s)<<endl;
        // for(int i:mx) cout<<i<<" "; cout<<endl;
        long long ans=1ll *n*(n+1)/2;
        for(int i:mx)ans-=i;
        cout<<ans<<endl;
    }
}
