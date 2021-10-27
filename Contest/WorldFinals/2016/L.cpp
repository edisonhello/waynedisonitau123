#include <bits/stdc++.h>
using namespace std;
#define ll long long


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; 
    cin >> n;
    vector<pair<int, int>> bg, sm;

    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        if (y >= x) {
            bg.emplace_back(x, y);
        } else {
            sm.emplace_back(x, y);
        }
    }

    sort(bg.begin(), bg.end());
    sort(sm.begin(), sm.end(), [&] (const auto x, const auto y) { return x.second > y.second; });

    auto is_ok = [&] (ll sp) -> bool {
        for (auto [x, y] : bg) {
            if (x > sp) return false;
            sp += y - x;
        }
        for (auto [x, y] : sm) {
            if (x > sp) return false;
            sp += y - x;
        }
        return true;
    };


    ll L = 1, R = 1'000'000'000'000'000;
    while (L < R) {
        ll M = (L + R) >> 1;
        if (is_ok(M)) R = M;
        else L = M + 1;
    }

    cout << L << endl;
}

