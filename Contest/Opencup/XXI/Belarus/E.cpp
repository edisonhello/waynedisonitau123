#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, int k, vector<tuple<int, int, int>> &cond) {
    // cerr << "solve:";
    // for (auto [l, r, v] : cond) cerr << " [" << l << ", " << r << ", " << v << "]";
    // cerr << endl;

    vector<int> on, ze;
    for (int i = 0; i < k; ++i) (get<2>(cond[i]) ? on : ze).push_back(i);
    vector<int> cnt(n + 3, 0);
    for (int i : on) {
        auto [l, r, v] = cond[i];
        ++cnt[l];
        --cnt[r + 1];
    }
    for (int i = 2; i <= n; ++i) cnt[i] += cnt[i - 1];

    // cerr << "cnt: ";
    // for (int i : cnt) cerr << i << ' ';
    // cerr << endl;

    vector<int> none(n + 3, 0), once(n + 3, 0);
    for (int i = 1; i <= n; ++i) if (cnt[i] == 0) none[i] = 1; else if (cnt[i] == 1) once[i] = 1;

    vector<int> lenone(n + 3, 0), rinone(n + 3, 0);
    vector<int> leonce(n + 3, 0), rionce(n + 3, 0);
    for (int i = 1; i <= n; ++i) {
        if (none[i]) lenone[i] = i;
        else lenone[i] = lenone[i - 1];
        if (once[i]) leonce[i] = i;
        else leonce[i] = leonce[i - 1];
    }
    rinone[n + 1] = n + 1;
    rionce[n + 1] = n + 1;
    for (int i = n; i >= 1; --i) {
        if (none[i]) rinone[i] = i;
        else rinone[i] = rinone[i + 1];
        if (once[i]) rionce[i] = i;
        else rionce[i] = rionce[i + 1];
    }

    // cerr << "lenone: ";
    // for (int i : lenone) cerr << i << ' ';
    // cerr << endl;
    // cerr << "rinone: ";
    // for (int i : rinone) cerr << i << ' ';
    // cerr << endl;
    // cerr << "leonce: ";
    // for (int i : leonce) cerr << i << ' ';
    // cerr << endl;
    // cerr << "rionce: ";
    // for (int i : rionce) cerr << i << ' ';
    // cerr << endl;

    vector<int> ipzr(k + 2, 0); // is_perfect_zero_req
    vector<pair<int, int>> zr(k + 2, make_pair(-1, -1)); // zero_req
    vector<int> ibzr(k + 2, 0); // is_bad_zero_req
    int all_zrl = n + 1, all_zrr = 0;
    int cnt_zr = 0;
    for (int i : ze) {
        auto [l, r, v] = cond[i];
        int tol = rinone[l];
        int tor = lenone[r];
        if (tol <= r) {
            ipzr[i] = true;
            continue;
        }
        tol = rionce[l];
        tor = leonce[r];
        if (tol > r) {
            ibzr[i] = true;
            continue;
        }
        zr[i] = make_pair(tol, tor);
        all_zrl = min(all_zrl, tor);
        all_zrr = max(all_zrr, tol);
        ++cnt_zr;
    }

    int cnt_bad = 0;
    for (int i : ibzr) cnt_bad += i;

    // cerr << "cnt_bad cnt_zr " << cnt_bad << ' ' << cnt_zr << endl;
    // cerr << "all_zrl all_zrr " << all_zrl << ' ' << all_zrr << endl;

    vector<int> sol;
    for (int i = 0; i < k; ++i) {
        auto [l, r, v] = cond[i];
        if (v) {
            if (cnt_bad) { sol.push_back(0); continue; }
            if (!cnt_zr) { sol.push_back(1); continue; }
            if (l <= all_zrl && all_zrr <= r && rionce[l] <= r) { sol.push_back(1); continue; }
            sol.push_back(0);
        } else {
            if (cnt_bad > 1) { sol.push_back(0); continue; }
            if (cnt_bad && ibzr[i]) {
                if (cnt_zr) { sol.push_back(0); continue; }
                sol.push_back(1); continue;
            }
            if (cnt_bad) { sol.push_back(0); continue; }
            if (cnt_zr > 1) { sol.push_back(0); continue; }
            if (cnt_zr == 1 && zr[i].first != -1) { sol.push_back(1); continue; }
            if (cnt_zr) { sol.push_back(0); continue; }
            sol.push_back(1);
        }
    }

    // cerr << "sol: ";
    // for (int i : sol) cerr << i << ' ';
    // cerr << endl;

    return sol;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;

    vector<tuple<int, int, long long>> condi(k);
    for (auto &[l, r, v] : condi) cin >> l >> r >> v;

    vector<int> sol(k, 1);
    for (int i = 0; i < 60; ++i) {
        vector<tuple<int, int, int>> cond;
        for (auto [l, r, v] : condi) cond.emplace_back(l, r, !!(v & (1ll << i)));
        auto ans = solve(n, k, cond);
        for (int i = 0; i < k; ++i) sol[i] &= ans[i];
    }

    for (int i : sol) cout << i;
    cout << endl;

}

