#include <bits/stdc++.h>
using namespace std;

int Parse(const string &s) {
    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        v = v * 10 + (s[i] - '0');
    }
    return v - 1;
}

bool Solve(int n, int m) {
    vector<tuple<int, int, vector<int>>> rule(m);
    vector<vector<int>> g(n);
    vector<vector<int>> rev(n);
    for (int i = 0; i < m; ++i) {
        int x, k;
        cin >> x >> k;
        x--;
        int p = 0;
        vector<int> t;
        for (int j = 0; j < k; ++j) {
            string s;
            cin >> s;
            if (s == "a" || s == "b") p ^= 1;
            else t.push_back(Parse(s));
        }
        rule[i] = make_tuple(x, p, t);
        g[x].push_back(i);
    }
    vector<int> cnt(m);
    for (int i = 0; i < m; ++i) {
        auto &v = get<2>(rule[i]);
        sort(v.begin(), v.end());
        for (int j = 0, k = 0; j < v.size(); j = k) {
            while (k < v.size() && v[j] == v[k]) k++;
            cnt[i]++;
            rev[v[j]].push_back(i);
        }
    }

    vector<bool> used(n);
    vector<int> que;
    auto TryPush = [&](int r) {
        if (cnt[r] == 0) {
            if (used[get<0>(rule[r])]) return;
            used[get<0>(rule[r])] = true;
            que.push_back(get<0>(rule[r])); 
        }
    };

    for (int i = 0; i < m; ++i) TryPush(i);
    for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (int r : rev[x]) {
            cnt[r]--;
            TryPush(r);
        }
    }
    if (!used[0]) return false;
    vector<bool> invalid(m);
    for (int i = 0; i < m; ++i) {
        for (int u : get<2>(rule[i])) {
            if (!used[u]) invalid[i] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) continue;
        vector<int> ng;
        for (int u : g[i]) {
            if (!invalid[u]) {
                ng.push_back(u);
            }
        }
        g[i] = ng;
    }
    for (int i = 0; i < n; ++i) rev[i].clear();
    vector<vector<int>> rv(n);
    for (int i = 0; i < m; ++i) {
        if (invalid[i]) continue;
        vector<int> u;
        auto &v = get<2>(rule[i]);
        for (int j = 0, k = 0; j < v.size(); j = k) {
            while (k < v.size() && v[j] == v[k]) k++;
            if ((k - j) & 1) {
                u.push_back(v[j]);
                rev[v[j]].push_back(i);
            }
            rv[v[j]].push_back(i);
        }
        cnt[i] = u.size();
        get<2>(rule[i]) = u;
    }

    {
        vector<vector<bool>> used(n, vector<bool>(3));
        vector<pair<int, int>> que;

        auto Push = [&](auto self, int x, int b) {
            if (used[x][b]) return;
            used[x][b] = true;
            que.emplace_back(x, b);
            if (b < 2 && used[x][0] && used[x][1]) {
                self(self, x, 2); 
            }
        };

        auto PushRule = [&](int r) {
            Push(Push, get<0>(rule[r]), get<1>(rule[r]));
        };

        for (int i = 0; i < m; ++i) {
            if (invalid[i]) continue;
            if (cnt[i] == 0) PushRule(i);
        }
        for (int it = 0; it < que.size(); ++it) {
            auto [x, b] = que[it];
            if (b < 2 && used[x][2]) continue;
            for (int r : rev[x]) {
                if (b == 2) {
                    get<1>(rule[r]) = 2;
                    PushRule(r);
                    continue;
                }
                get<1>(rule[r]) ^= b;
                if (--cnt[r] == 0) PushRule(r);
            }
            if (b == 2) {
                for (int r : rv[x]) {
                    get<1>(rule[r]) = 2;
                    PushRule(r);
                }
            }
        }
        if (used[0][1] || used[0][2]) return true;
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        cout << (Solve(n, m) ? "YES" : "NO") << "\n";
    }
}

