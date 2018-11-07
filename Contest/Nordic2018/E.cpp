#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> ds;

int state(const vector<int> &cnt) {
    return lower_bound(ds.begin(), ds.end(), cnt) - ds.begin();
}

vector<int> rev(int s) {
    return ds[s];
}

void dfs(vector<int> cur, int x) {
    if (x == cur.size()) return ds.push_back(cur), void();
    dfs(cur, x + 1);
    while (accumulate(cur.begin(), cur.end(), 0) < 5) {
        cur[x]++;
        dfs(cur, x + 1);
    }
}

const int maxn = 3e5 + 5;
const long double eps = 1e-12;
long double dp[2][maxn];
int tab[1000][1000];
vector<pair<int, int>> tp[1000][1000];

int comp(vector<int> a, vector<int> b) {
    return state(a) * 462 + state(b);
}


int main() {
    dfs(vector<int>(6, 0), 0);
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    int n, m, d; cin >> n >> m >> d;
    vector<int> cx(6), cy(6);
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        cx[a - 1]++;
    }
    for (int i = 0; i < m; ++i) {
        int a; cin >> a;
        cy[a - 1]++;
    }
    for (int i = 0; i < 462; ++i) {
        for (int j = 0; j < 462; ++j) {
            // cout << i << ' ' << j << endl;
            vector<int> cx = rev(i), cy = rev(j);
            tab[i][j] = accumulate(cx.begin(), cx.end(), 0) + accumulate(cy.begin(), cy.end(), 0);
            for (int k = 0; k < 6; ++k) {
                if (cx[k] == 0) continue;
                --cx[k];
                if (k) ++cx[k - 1];
                int t = comp(cx, cy);
                ++cx[k];
                tp[i][j].emplace_back(t, cx[k]);
                if (k) --cx[k - 1];
            }
            for (int k = 0; k < 6; ++k) {
                if (cy[k] == 0) continue;
                --cy[k];
                if(k) ++cy[k - 1];
                int t = comp(cx, cy);
                ++cy[k];
                tp[i][j].emplace_back(t, cy[k]);
                if (k) --cy[k - 1];
            }
            if (accumulate(cx.begin(), cx.end(), 0) == 0 && accumulate(cy.begin(), cy.end(), 0) == 0) {
                // cout << "hey" << endl;
                tp[i][j].emplace_back(i * 462 + j, 1);
                tab[i][j] = 1;
            }
        }
    }
    dp[0][comp(cx, cy)] = 1.0;
    for (int i = 1; i <= d; ++i) {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for (int j = 0; j < 462 * 462; ++j) {
            if (dp[i & 1 ^ 1][j] < eps) continue;
            vector<int> cx = rev(j / 462), cy = rev(j % 462);
            // int all = count(cx, cy);
            int all = tab[j / 462][j % 462];
            // vector<int> to = tp[j / 462][j % 462];
            for (auto k : tp[j / 462][j % 462]) dp[i & 1][k.first] += dp[i & 1 ^ 1][j] * k.second / all;
            // printf("dp[%d][%d] = %.5Lf\n", i, j, dp[i][j]);
        }
    }
    long double ans = 0.0;
    for (int i = 0; i < 462; ++i) {
        for (int j = 0; j < 462; ++j) {
            vector<int> c = rev(j);
            if (accumulate(c.begin(), c.end(), 0) == 0) ans += dp[d & 1][i * 462 + j];
        }
    }
    cout << fixed << setprecision(20) << ans << endl;
}
