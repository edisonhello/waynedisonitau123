#include <bits/stdc++.h>
using namespace std;

struct Cmp {
    bool operator()(const tuple<int, int, int> &a, const tuple<int, int, int> &b) const {
        int64_t P = 1LL * get<0>(a) * get<1>(b);
        int64_t Q = 1LL * get<1>(a) * get<0>(b);
        return  P == Q ? get<2>(a) < get<2>(b) : P < Q;
    }
};

int main() {
    int M;
    cin >> M;
    vector<int> v(M), N(M);
    int sum = 0;
    vector<int> down(M);
    vector<vector<int>> uu(M), tt(M);
    vector<int> tsum(M);
    vector<tuple<int, int, int, int>> all;
    for (int i = 0; i < M; ++i) {
        cin >> v[i] >> N[i];
        vector<pair<int, int>> ev;
        down[i] = v[i];
        for (int j = 0; j < N[i]; ++j) {
            int u, t;
            cin >> u >> t;
            tsum[i] += t;
            ev.emplace_back(t, u);
            down[i] += u;
        }
        sort(ev.begin(), ev.end(), [&](auto X, auto Y) {
            return 1LL * X.first * Y.second < 1LL * Y.first * X.second;
        });
        for (int j = 0; j < ev.size(); ++j) {
            tt[i].push_back(ev[j].first);
            uu[i].push_back(ev[j].second);
            all.emplace_back(tt[i][j], uu[i][j], i, j);
        }
    }

    sort(all.begin(), all.end(), [&](auto X, auto Y) {
        int p1 = get<0>(X), q1 = get<1>(X);
        int p2 = get<0>(Y), q2 = get<1>(Y);
        return 1LL * p1 * q2 < 1LL * q1 * p2;
    });

    set<tuple<int, int, int>, Cmp> g;
    for (int i = 0; i < M; ++i) g.insert(make_tuple(tsum[i], down[i], i));
    vector<bool> used(M);
    vector<int> ptr(M);

    vector<tuple<int, int, int>> fin;

    for (int i = 0; i < all.size(); ++i) {
        if (used[get<2>(all[i])]) continue;
        assert(!g.empty());
        int PP = get<0>(*g.begin());
        int QQ = get<1>(*g.begin());
        int L = get<2>(*g.begin());
        int P = get<0>(all[i]);
        int Q = get<1>(all[i]);
        // cout << "P = " << P << " Q = " << Q << " From = " << get<2>(all[i]) << endl;
        if (1LL * PP * Q < 1LL * QQ * P) {
            // cout << "push all" << endl;
            for (int j = ptr[L]; j < uu[L].size(); ++j) {
                fin.emplace_back(tt[L][j], uu[L][j], L);
            }
            used[L] = true;
            g.erase(g.begin());
            i--;
        } else {
            int O = get<2>(all[i]);
            fin.emplace_back(get<0>(all[i]), get<1>(all[i]), O);
            g.erase(make_tuple(tsum[O], down[O], O));
            tsum[O] -= get<0>(all[i]);
            down[O] -= get<1>(all[i]);
            if (down[O] > 0) {
                g.insert(make_tuple(tsum[O], down[O], O));
            }
            ptr[O]++;
        }
    }
    int P = accumulate(N.begin(), N.end(), 0);
    assert(fin.size() == P);
    vector<int> cnt(M);
    int64_t res = 0, pref = 0;
    for (int i = 0; i < P; ++i) {
        pref += get<0>(fin[i]);
        res += pref * get<1>(fin[i]);
        if (++cnt[get<2>(fin[i])] == N[get<2>(fin[i])]) {
            res += v[get<2>(fin[i])] * pref;
        }
    }
    cout << res << "\n";
}
