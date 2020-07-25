#include <bits/stdc++.h>
using namespace std;

void Print(vector<pair<int, int>> res) {
    sort(res.begin(), res.end());
    cout << "1\n";
    for (auto u : res) cout << u.first << " " << u.second << "\n";
}

void Solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k + 1);
    for (int i = 0; i <= k; ++i) cin >> a[i];
    vector<int> b(k + 1);
    for (int i = 1; i <= k; ++i) {
        if (a[i - 1] < a[i]) {
            cout << "0\n";
            return;
        }
        b[i] = a[i - 1] - a[i];
    }
    int s = a[0];
    vector<pair<int, int>> res;
    for (int i = 1; i < k; ++i) b[i] -= b[i + 1];
    int kind = n;
    for (int i = 1; i < k; ++i) {
        if (b[i] > 0) {
            res.emplace_back(i, b[i]);
            s -= i * b[i];
            kind--;
        }
        if (b[i] < 0) {
            cout << "0\n";
            return;
        }
    }
    if (s < 0 || kind < 0) {
        cout << "0\n";
        return;
    }
    s -= b[k] * k;
    if (s < 0) {
        cout << "0\n";
        return;
    }
    if (b[k] < kind) {
        cout << "0\n";
        return;
    }
    if (kind == 0) {
        if (s > 0 || b[k] > 0) {
            cout << "0\n";
            return;
        }
        Print(res);
        return;
    }
    if (kind == 1) {
        if (s % b[k] != 0) {
            cout << "0\n";
            return;
        }
        res.emplace_back(k + s / b[k], b[k]);
        Print(res);
        return;
    }
    int N = kind * (kind - 1) / 2;
    if (s < N) {
        cout << "0\n";
        return;
    }
    if (s == N) {
        res.emplace_back(k, b[k] - (kind - 1));
        for (int i = 1; i < kind; ++i) {
            res.emplace_back(k + i, 1);
        }
        Print(res);
        return;
    }
    if (kind >= 3) {
        if (s - N >= 2) {
            cout << "2\n";
            return;
        }
        if (s - N == 1) {
            if (kind == b[k]) {
                res.emplace_back(k, b[k] - (kind - 1));
                for (int i = 1; i < kind - 1; ++i) {
                    res.emplace_back(k + i, 1);
                }
                res.emplace_back(k + kind, 1);
                Print(res);
                return;
            } else {
                cout << "2\n";
                return;
            }
        }
        return;
    }
    assert(kind == 2);
    vector<tuple<int, int, int, int>> sol;
    for (int c = 0; c <= s; ++c) {
        for (int x = 1; x < b[k] && c * x <= s; ++x) {
            int y = b[k] - x;
            if ((s - c * x) % y != 0) continue;
            // cout << "x = " << x << " y = " << y << endl;
            int d = (s - c * x) / y;
            if (c < d) {
                sol.emplace_back(c, x, d, y);
            }
        }
    }
    if (sol.empty()) {
        cout << "0\n";
        return;
    }
    if (sol.size() > 1) {
        cout << "2\n";
        return;
    }
    int c, x, d, y;
    tie(c, x, d, y) = sol[0];
    res.emplace_back(c + k, x);
    res.emplace_back(d + k, y);
    Print(res);
}

int main() {
    int t;
    cin >> t;
    while (t--) Solve();
}

