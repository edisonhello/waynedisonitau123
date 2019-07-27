#include <bits/stdc++.h>
using namespace std;

vector<int> oa, ob;
vector<int> ga[1003], gb[1003];
string sa, sb;
int pa[1003], pb[1003];
int dp[1003][1003];

void dfa(int now, int p) {
    pa[now] = p;
    oa.push_back(now);
    for (int i : ga[now]) if (i != p) dfa(i, now);
}
void dfb(int now, int p) {
    pb[now] = p;
    ob.push_back(now);
    for (int i : gb[now]) if (i != p) dfb(i, now);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        cin >> sa; sa = " " + sa;
        for (int i = 1; i < n; ++i) {
            int z, x; cin >> z >> x;
            ga[z].push_back(x);
            ga[x].push_back(z);
        }
        cin >> sb; sb = " " + sb;
        for (int i = 1; i < m; ++i) {
            int z, x; cin >> z >> x;
            gb[z].push_back(x);
            gb[x].push_back(z);
        }
        oa.clear();
        ob.clear();
        oa.push_back(0);
        ob.push_back(0);
        dfa(1, 0);
        dfb(1, 0);
        for (int i = 1; i < (int)oa.size(); ++i) {
            for (int j = 1; j < (int)ob.size(); ++j) {
                int ii = oa[i], jj = ob[j];
                if (sa[ii] == sb[jj]) {
                    dp[ii][jj] = dp[pa[ii]][pb[jj]] + 1;
                } else dp[ii][jj] = 0;
                dp[ii][jj] = max(dp[ii][jj], max(dp[pa[ii]][jj], dp[ii][pb[jj]]));
            }
        }
        int mx = 0;
        for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
            mx = max(mx, dp[i][j]);
            dp[i][j] = 0;
        }
        for (int i = 0; i <= n; ++i) ga[i].clear();
        for (int i = 0; i <= m; ++i) gb[i].clear();
        cout << mx << '\n';
    }
}
