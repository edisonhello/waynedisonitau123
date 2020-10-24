#include <bits/stdc++.h>
using namespace std;

int ch[4000006][26];
long long val[4000006];
bool ed[4000006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<string> vs(n);
        for (int i = 0; i < n; ++i) cin >> vs[i];

        int _id = 0;
        auto Get = [&] () {
            memset(ch[_id], -1, sizeof(ch[_id]));
            val[_id] = 0;
            ed[_id] = 0;
            return _id++;
        };
        int root = Get();

        auto Add = [&] (auto self, int now, string &s, int idx, int v) {
            if (idx == (int)s.size()) {
                val[now] += v;
                ed[now] = 1;
                return;
            }
            int &to = ch[now][s[idx] - 'a'];
            if (to == -1) to = Get();
            self(self, to, s, idx + 1, v);
        };

        while (m--) {
            string s; cin >> s;
            int v; cin >> v;
            Add(Add, root, s, 0, v);
        }

        long long tot = 0;
        bool fail = 0;
        for (int i = 0; i < n; ++i) {
            int now = root;
            for (int j = 0; j < n; ++j) {
                if (vs[i][j] == '#') {
                    if (now == root) continue;
                    if (!ed[now]) {
                        fail = 1;
                        break;
                    }
                    tot += val[now];
                    now = root;
                } else {
                    now = ch[now][vs[i][j] - 'a'];
                    if (now == -1) {
                        fail = 1;
                        break;
                    }
                }
            }
            if (fail) break;
            if (now == root) continue;
            if (!ed[now]) {
                fail = 1;
                break;
            }
            tot += val[now];
        }
        if (!fail) for (int j = 0; j < n; ++j) {
            int now = root;
            for (int i = 0; i < n; ++i) {
                if (vs[i][j] == '#') {
                    if (now == root) continue;
                    if (!ed[now]) {
                        fail = 1;
                        break;
                    }
                    tot += val[now];
                    now = root;
                } else {
                    now = ch[now][vs[i][j] - 'a'];
                    if (now == -1) {
                        fail = 1;
                        break;
                    }
                }
            }
            if (fail) break;
            if (now == root) continue;
            if (!ed[now]) {
                fail = 1;
                break;
            }
            tot += val[now];
        }

        if (fail) cout << -1 << '\n';
        else cout << tot << '\n';
    }
}

