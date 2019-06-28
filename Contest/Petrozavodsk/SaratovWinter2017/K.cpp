#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

const int mod1 = 1000000007, mod2 = 1000000087;

vector<pair<string, int>> qs[100005];
int ans[100005];
int hh1[100005], pp1[100005];
int hh2[100005], pp2[100005];
vector<int> relive[100005];

pair<int, int> chhs(string &s) {
    int hh1 = 0, hh2 = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        hh1 = (hh1 * 7902131ll + s[i]) % mod1;
        hh2 = (hh2 * 131ll + s[i]) % mod2;
    }
    return make_pair(hh1, hh2);
}
pair<int, int> ghhs(int l, int r) {
    return make_pair(
        ((hh1[r] - 1ll * hh1[l - 1] * pp1[r - l + 1]) % mod1 + mod1) % mod1, 
        ((hh2[r] - 1ll * hh2[l - 1] * pp2[r - l + 1]) % mod2 + mod2) % mod2);
}
long long piill(pair<int, int> p) {
    return 2000000000ll * p.first + p.second;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    s = " " + s;
    pp1[0] = pp2[0] = 1;
    for (int i = 1; i <= n; ++i) pp1[i] = 1ll * pp1[i - 1] * 7902131 % mod1;
    for (int i = 1; i <= n; ++i) pp2[i] = 1ll * pp2[i - 1] * 131 % mod2;
    for (int i = 1; i <= n; ++i) hh1[i] = (hh1[i - 1] * 7902131ll + s[i]) % mod1;
    for (int i = 1; i <= n; ++i) hh2[i] = (hh2[i - 1] * 131ll + s[i]) % mod2;
    for (int i = 0; i < m; ++i) {
        string t; cin >> t;
        qs[t.size()].emplace_back(t, i);
    }
    for (int i = 1; i <= n; ++i) {
        if (qs[i].empty()) continue;
        int le = i; {
            sort(qs[i].begin(), qs[i].end());
            vector<pair<int, int>> ref_list;
            int j = 1;
            for (int i = 1; i < (int)qs[le].size(); ++i) {
                if (qs[le][i].first == qs[le][j - 1].first) {
                    ref_list.emplace_back(qs[le][i].second, qs[le][j - 1].second);
                } else {
                    qs[le][j] = qs[le][i];
                    ++j;
                }
            }
            qs[le].resize(j);
            // cerr << "now doing le = " << le << endl;
            vector<pair<int, int>> hhs(qs[le].size());
            cc_hash_table<long long, vector<int>> active;
            for (int i = 0; i < (int)qs[le].size(); ++i) {
                hhs[i] = chhs(qs[le][i].first);
                active[piill(hhs[i])].push_back(i);
            }
            /* cerr << "active: "; for (auto &p : active) {
                cerr << p.first << " has ";
                for (int i : p.second) cerr << i << " ";
                cerr << endl;
            } */
            for (int i = 1; i + le - 1 <= n; ++i) {
                for (int j : relive[i]) active[piill(hhs[j])].push_back(j);
                pair<int, int> thhs = ghhs(i, i + le - 1);
                // cerr << "thhs = " << piill(thhs) << " at start " << i << endl;
                auto it = active.find(piill(thhs));
                if (it != active.end()) {
                    for (int j : it->second) {
                        ++ans[qs[le][j].second];
                        relive[i + le].push_back(j);
                    }
                    it->second.clear();
                }
            }
            for (int i = 1; i <= n + 3; ++i) relive[i].clear();
            for (auto &p : ref_list) ans[p.first] = ans[p.second];
        }
    }
    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
