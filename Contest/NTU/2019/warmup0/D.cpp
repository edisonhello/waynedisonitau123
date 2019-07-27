#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

const int maxn = 1e5 + 5;
const int pr1 = 131;
const int mod1 = 1e9 + 87;
const int pr2 = 123;
const int mod2 = 1e9 + 123;
int pos[maxn], h1[maxn], h2[maxn], pw1[maxn], pw2[maxn], ans[maxn], l[maxn], r[maxn];
vector<pair<int, long long>> qr[maxn];
string qs[maxn];

long long query(int l, int r) {
    int a = 0, b = 0;
    if (l == 0) {
        a = h1[r];
        b = h2[r];
    } else {
        a = (h1[r] + mod1 - 1ll * pw1[r - l + 1] * h1[l - 1] % mod1) % mod1;
        b = (h2[r] + mod2 - 1ll * pw2[r - l + 1] * h2[l - 1] % mod2) % mod2;
    }
    return a * 1ll * mod2 + b;
}

int main() {
    pw1[0] = 1;
    for (int i = 1; i < maxn; ++i)
        pw1[i] = pw1[i - 1] * 1ll * pr1 % mod1;
    pw2[0] = 1;
    for (int i = 1; i < maxn; ++i)
        pw2[i] = pw2[i - 1] * 1ll * pr2 % mod2;

    ios_base::sync_with_stdio(false), cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int k = 0;
        string c = "";
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            int l = s.size();
            for (int j = 0; j < l; ++j) {
                pos[(int)c.size()] = i;
                c += s[j];
            } 
            c += 'Z';
        }

        h1[0] = h2[0] = c[0];
        for (int i = 1; i < (int)c.size(); ++i) {
            h1[i] = (h1[i - 1] * 1ll * pr1 + c[i]) % mod1;
            h2[i] = (h2[i - 1] * 1ll * pr2 + c[i]) % mod2;
        }

        for (int i = 0; i < m; ++i) {
            cin >> qs[i] >> l[i] >> r[i];
            --l[i], --r[i];
            int hv1 = 0, hv2 = 0;
            for (int j = 0; j < (int)qs[i].size(); ++j) {
                hv1 = (hv1 * 1ll * pr1 + qs[i][j]) % mod1;
                hv2 = (hv2 * 1ll * pr2 + qs[i][j]) % mod2;
            }
            qr[qs[i].size()].emplace_back(i, hv1 * 1ll * mod2 + hv2);
            ans[i] = 0;
        }

        for (int i = 1; i < maxn; ++i) {
            if (qr[i].empty()) continue;

            cc_hash_table<long long, int> tab;
            cc_hash_table<long long, vector<int>> occ;
            for (int j = 0; j < (int)qr[i].size(); ++j) tab[qr[i][j].second] = qr[i][j].first;

            for (int j = i - 1; j < (int)c.size(); ++j) {
                long long hv = query(j - i + 1, j);
                if (tab.find(hv) != tab.end()) {
                    int k = tab[hv];
                    occ[hv].push_back(pos[j]);
                    // if (pos[j] >= l[k] && pos[j] <= r[k]) ++ans[k];
                }
            }
            for (auto &it : occ) {
                sort(it.second.begin(), it.second.end());
            }
            for (int j = 0; j < (int)qr[i].size(); ++j) {
                int ll = l[qr[i][j].first];
                int rr = r[qr[i][j].first];
                long long hv = qr[i][j].second;
                ans[qr[i][j].first] = upper_bound(occ[hv].begin(), occ[hv].end(), rr) - lower_bound(occ[hv].begin(), occ[hv].end(), ll);
            }
        }

        for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);

        for (int i = 0; i < m; ++i) qr[qs[i].size()].clear();
    }
}
