#include <bits/stdc++.h>
using namespace std;

void solve() {
    map<string, int> stoi;
    auto Get = [&] (string s) {
        auto &i = stoi[s];
        if (i == 0) {
            i = stoi.size();
        }
        return i;
    };
    int k; cin >> k;
    vector<pair<int, int>> to(k * 3 + 5, make_pair(-1, -1));
    vector<string> word(k * 3 + 5);
    vector<vector<int>> have(k * 3 + 5, vector<int>(26, 0));
    vector<int> vis(k * 3 + 5, 0);

    cin.ignore();
    while (k--) {
        string s; getline(cin, s);
        stringstream ss(s);
        string a, b, c, d, e;
        ss >> a >> b >> c;
        if (ss >> d >> e) {
            int aa = Get(a), cc = Get(c), ee = Get(e);
            to[aa] = make_pair(cc, ee);
        } else {
            int aa = Get(a);
            word[aa] = c;
            for (char ch : c) have[aa][ch - 'a'] = 1;
            vis[aa] = 1;
        }
    }

    auto Prep = [&] (auto self, int now) {
        if (vis[now]) return;
        vis[now] = 1;
        
        self(self, to[now].first);
        self(self, to[now].second);

        for (int i = 0; i < 26; ++i) have[now][i] = have[to[now].first][i] || have[to[now].second][i];
    };

    for (int i = 1; i <= (int)stoi.size(); ++i) Prep(Prep, i);
    string sts; cin >> sts;
    int sti = Get(sts);
    string targ; cin >> targ;
    int cur = 0;

    auto Dfs = [&] (auto self, int now) {
        if (cur >= (int)targ.size()) return;
        if (word[now].size()) {
            for (char c : word[now]) {
                if (cur < (int)targ.size() && c == targ[cur]) {
                    // cerr << "cur " << cur << " match " << targ[cur] << " at now = " << now << " word " << word[now] << endl;
                    ++cur;
                }
            }
        } else {
            int tari = targ[cur] - 'a';
            if (have[to[now].first][tari]) {
                self(self, to[now].first);
            }
            tari = targ[cur] - 'a';
            if (have[to[now].second][tari]) {
                self(self, to[now].second);
            }
        }
    };


    Dfs(Dfs, sti);
    // cerr << "targ cur " << targ << ' ' << cur << endl;
    cout << (cur >= (int)targ.size() ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) solve();
}

