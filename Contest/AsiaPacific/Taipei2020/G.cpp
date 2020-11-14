#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

vector<int> rotate(const vector<int> &v) {
    int n = v.size();
    auto vv = v;
    for (auto i : v) vv.push_back(i);
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && vv[i + k] == vv[j + k]) ++ k;
        if (vv[i + k] <= vv[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) ++j;
    }
    int pos = (i < n ? i : j);
    vector<int> r;
    for (int i = pos, j = 0; j < n; ++i, ++j) {
        r.push_back(vv[i]);
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<int> dephash(100005);
    for (int i = 0; i < 100005; ++i) dephash[i] = rand() % 1000000000;
    int t; cin >> t; while (t--) {
        int k; cin >> k;
        // map<int, int> hashc;
        set<vector<int>> st;
        while (k--) {
            int n; cin >> n;
            vector<vector<int>> g(n);
            for (int i = 0; i < n; ++i) {
                int u, v; cin >> u >> v;
                --u, --v;
                g[u].push_back(v);
                g[v].push_back(u);
            }
            stack<int> stk;
            vector<int> loop;
            vector<int> vis(n, 0);
            auto dfs = [&] (auto self, int now, int pa) -> bool {
                // cerr << "dfs " << now << endl;
                stk.push(now);
                vis[now] = 1;
                for (int i : g[now]) if (i != pa) {
                    if (vis[i]) {
                        while (stk.top() != i) {
                            // cerr << "new " << stk.top() << " i = " << i << endl;
                            loop.push_back(stk.top());
                            stk.pop();
                        }
                        loop.push_back(i);
                        return true;
                    }
                    else {
                        int res = self(self, i, now);
                        if (res) return true;
                    }
                }
                vis[now] = 0;
                stk.pop();
                return false;
            };
            assert(dfs(dfs, 0, -1));

            // cerr << "herre" << endl;

            vector<int> isloop(n, 0);
            for (int i : loop) isloop[i] = 1;

            // cerr << "loop: ";
            // for (int i : loop) cerr << i << ' ';
            // cerr << endl;


            vector<int> hashs;
            auto dfs2 = [&] (auto self, int now, int pa, int dep) -> pair<int, int> {
                int sz = 1;
                vector<int> szs, hhs;
                for (int i : g[now]) if (i != pa && !isloop[i]) {
                    auto [ssz, hhh] = self(self, i, now, dep + 1);
                    sz += ssz;
                    szs.push_back(ssz);
                    hhs.push_back(hhh);
                }
                int hh = dephash[dep];
                // sort(szs.begin(), szs.end()); 
                sort(hhs.begin(), hhs.end());
                // for (int i : szs) hh = (131ll * hh + i) % mod;
                for (int i : hhs) hh = (hh * 1ll * ((i + dephash[dep]) % mod)) % mod;

                return make_pair(sz, hh);
            };
            for (int i : loop) {
                auto [sz, hh] = dfs2(dfs2, i, -1, 0);
                // cerr << "i res = " << i << ' ' << hh << endl;
                hashs.push_back(hh);
            }

            auto r1 = rotate(hashs);
            reverse(hashs.begin(), hashs.end());
            r1 = min(r1, rotate(hashs));

            // cerr << "r1: ";
            // for (int i : r1) cerr << i << ' ';
            // cerr << endl;
            st.insert(r1);

            // sort(hashs.begin(), hashs.end());

            // int hh = 0;
            // // for (auto [sz, h] : r1) { hh = (131ll * hh + sz) % mod; }
            // for (auto [sz, h] : r1) { hh = (131ll * hh + h) % mod; }

            // hashc[hh]++;
            // // cerr << "hh =  " << hh << endl;
        }

        cout << st.size() << '\n';
    }
}
