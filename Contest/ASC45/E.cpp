#include<bits/stdc++.h>
using namespace std;

int a,b,c,m,n;

long long ans;

int cost(int i,int j){
    int co=(1ll*a*i+1ll*b*j+1ll*c*(i^j))%m;
    return co;
}

vector<int> possible(int at,int now){ int b = (at + 1) & -(at + 1);
    int k = now ^ b;
    vector<int> res;
    for (int i = 0; i < b; ++i) {
        res.push_back(k ^ i);
    }
    return res;
}

long long dp[4096][4096];
int fr[4096][4096];

long long dfs(int at,int now) {
    if (at == n - 1) return 0;
    if (~dp[at][now]) return dp[at][now];
    dp[at][now] = 1e18;
    vector<int> p = possible(at, now);
    for (int i = 0; i < (int)p.size(); ++i) {
        long long d = dfs(at + 1, p[i]) + cost(now, p[i]);
        if (d < dp[at][now]) {
            dp[at][now] = d;
            fr[at][now] = p[i];
        }
    }
    return dp[at][now];
}

int main(){
#ifdef ONLINE_JUDGE
    freopen("elegant.in", "r", stdin);
    freopen("elegant.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    while(cin>>n,n){
        cin>>a>>b>>c>>m;
        ans=1e16;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) dp[i][j] = -1;
        }
        int s = -1;
        for(int i=0;i<n;++i){
            long long d = dfs(0, i);
            if (d < ans) {
                ans = d;
                s = i;
            }
        }
        cout<<ans<<'\n';
        for (int j = 0; j < n; ++j) {
            cout << s << ' ';
            s = fr[j][s];
        }
        cout << endl;
    }
}
