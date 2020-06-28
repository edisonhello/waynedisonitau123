#include <bits/stdc++.h>
using namespace std;

pair<int64_t, vector<int>> Solve(vector<int> target, vector<int> a) {
    int n = a.size();
    vector<int> res(n, -1);
    vector<vector<int>> g(2);
    for (int i = 0; i < n; ++i) {
        g[a[i] % 2].push_back(i);
    }
    int64_t sum = 0;
    for (int prt = 0; prt < 2; ++prt) {
        vector<pair<int, int>> left, right;
        reverse(g[prt].begin(), g[prt].end());
        for (int j = 0; j < n; ++j) {
            if (target[j] == prt && res[j] == -1) {
                assert(!g[prt].empty());
                int p = g[prt].back();
                g[prt].pop_back();
                sum += abs(j - p);
                if (j < p) {
                    left.emplace_back(j, p);
                } else if (j > p) {
                    right.emplace_back(j, p);
                } else {
                    res[j] = a[j];
                }
            }
        }
        // cerr << "left:" << endl;
        // for (auto &x : left) cerr << x.first << " <- " << x.second << endl;
        // cerr << "right:" << endl;
        // for (auto &x : right) cerr << x.first << " <- " << x.second << endl;
        vector<int> rd;
        for (int i = 0; i < right.size(); ++i) {
            rd.push_back(right[i].second);
        }
        priority_queue<int> pq;
        for (int i = 0, j = 0; i < right.size(); ++i) {
            while (j < rd.size() && rd[j] <= right[i].first) {  // <=
                pq.push(-a[rd[j]]);
                j++;
            }
            assert(!pq.empty());
            int x = -pq.top();
            pq.pop();
            res[right[i].first] = x;
        }
        vector<int> ld;
        for (int i = 0; i < left.size(); ++i) {
            ld.push_back(left[i].second);
        }
        vector<int> go;
        vector<int> vl;
        for (int i = 0, j = 0; i < ld.size(); ++i) {
            while (j < left.size() && left[j].first <= ld[i]) j++;  // <=
            assert(j >= i + 1);
            go.push_back(j - (i + 1));
            vl.push_back(a[ld[i]]);
        }
        const int m = go.size();
        if (m > 0) {
            vector<int> mg(4 * m);
            vector<pair<int, int>> mv(4 * m);
            vector<int> tg(4 * m);

            auto Build = [&]() {
                auto _ = [&](auto self, int l, int r, int o = 0) {
                    if (r - l == 1) {
                        mg[o] = go[l];
                        mv[o] = make_pair(vl[l], l);
                        return;
                    }
                    int m = (l + r) >> 1;
                    self(self, l, m, o * 2 + 1);
                    self(self, m, r, o * 2 + 2);
                    mg[o] = min(mg[o * 2 + 1], mg[o * 2 + 2]);
                    mv[o] = min(mv[o * 2 + 1], mv[o * 2 + 2]);
                };

                _(_, 0, m);
            };

            auto Rightmost = [&]() {
                auto _ = [&](auto self, int l, int r, int o = 0) {
                    if (r - l == 1) {
                        if (mg[o] <= 0) return l - 1;
                        return l;
                    }
                    for (int k = 1; k <= 2; ++k) {
                        mg[o * 2 + k] += tg[o];
                        tg[o * 2 + k] += tg[o];
                    }
                    tg[o] = 0;
                    int m = (l + r) >> 1;
                    if (mg[o * 2 + 1] <= 0) {
                        return self(self, l, m, o * 2 + 1);
                    } else {
                        return self(self, m, r, o * 2 + 2);
                    }
                };

                return _(_, 0, m);
            };

            auto Modify = [&](int ql, int qr, int v) {
                auto _ = [&](auto self, int l, int r, int o = 0) {
                    if (l >= qr || ql >= r) return;
                    if (l >= ql && r <= qr) {
                        mg[o] += v;
                        tg[o] += v;
                        return;
                    }
                    for (int k = 1; k <= 2; ++k) {
                        mg[o * 2 + k] += tg[o];
                        tg[o * 2 + k] += tg[o];
                    }
                    tg[o] = 0;
                    int m = (l + r) >> 1;
                    self(self, l, m, o * 2 + 1);
                    self(self, m, r, o * 2 + 2);
                    mg[o] = min(mg[o * 2 + 1], mg[o * 2 + 2]);
                    mv[o] = min(mv[o * 2 + 1], mv[o * 2 + 2]);
                };

                _(_, 0, m);
            };

            auto Set = [&](int p) {
                auto _ = [&](auto self, int l, int r, int o = 0) {
                    if (r - l == 1) {
                        mg[o] = 2e9;
                        mv[o] = make_pair(2e9, -1);
                        return;
                    }
                    for (int k = 1; k <= 2; ++k) {
                        mg[o * 2 + k] += tg[o];
                        tg[o * 2 + k] += tg[o];
                    }
                    tg[o] = 0;
                    int m = (l + r) >> 1;
                    if (p < m) {
                        self(self, l, m, o * 2 + 1);
                    } else {
                        self(self, m, r, o * 2 + 2);
                    }
                    mg[o] = min(mg[o * 2 + 1], mg[o * 2 + 2]);
                    mv[o] = min(mv[o * 2 + 1], mv[o * 2 + 2]);
                };
                _(_, 0, m);
            };

            auto Query = [&](int ql, int qr) {
                auto _ = [&](auto self, int l, int r, int o = 0) {
                    if (l >= qr || ql >= r) return make_pair(int(2e9), -1);
                    if (l >= ql && r <= qr) return mv[o];
                    for (int k = 1; k <= 2; ++k) {
                        mg[o * 2 + k] += tg[o];
                        tg[o * 2 + k] += tg[o];
                    }
                    tg[o] = 0;
                    int m = (l + r) >> 1;
                    return min(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
                };
                return _(_, 0, m);
            };


            Build();

            vector<bool> used(go.size());
            for (int i = 0; i < left.size(); ++i) {
                int p = min(m, Rightmost() + 2);
                auto x = Query(0, p);
                assert(x.second != -1);
                res[left[i].first] = x.first;
                Set(x.second);
                Modify(0, x.second, -1);
                // int x = 1e9, z = -1;
                // bool ok = true;
                // for (int j = 0; j < go.size(); ++j) {
                //     if (used[j]) continue;
                //     if (ok) {
                //         if (vl[j] < x) {
                //             x = vl[j];
                //             z = j;
                //         }
                //     }
                //     ok &= go[j] > 0;
                // }
                // res[left[i].first] = x;
                // for (int j = 0; j < z; ++j) go[j]--;
                // used[z] = true;
            }
        }
    }
    // cerr << "sum = " << sum << endl;
    // cerr << "res: " << endl;
    // for (int u : res) cerr << u << " ";
    // cerr << endl;
    return make_pair(sum, res);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (n % 2 == 1) {
        vector<int> cnt(2);
        for (int i = 0; i < n; ++i) {
            cnt[a[i] % 2]++;
        }
        assert(cnt[0] == n / 2 || cnt[1] == n / 2);
        vector<int> target(n);
        if (cnt[0] > cnt[1]) {
            for (int i = 0; i < n; i += 2) target[i] = 0;
            for (int i = 1; i < n; i += 2) target[i] = 1;
        } else {
            for (int i = 0; i < n; i += 2) target[i] = 1;
            for (int i = 1; i < n; i += 2) target[i] = 0;
        }
        auto res = Solve(target, a).second;
        for (int i = 0; i < n; ++i) cout << res[i] << " ";
        cout << "\n";
    } else {
        vector<int> cnt(2);
        for (int i = 0; i < n; ++i) {
            cnt[a[i] % 2]++;
        }
        assert(cnt[0] == n / 2 && cnt[1] == n / 2);
        vector<int> target(n);
        for (int i = 0; i < n; i += 2) target[i] = 1;
        auto x = Solve(target, a);
        for (int i = 0; i < n; i += 2) target[i] = 0;
        for (int i = 1; i < n; i += 2) target[i] = 1;
        auto y = Solve(target, a);
        if (x > y) swap(x, y);
        for (int i = 0; i < n; ++i) cout << x.second[i] << " ";
        cout << "\n";
    }
}

