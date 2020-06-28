#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> ds(a.begin(), a.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
    }
    vector<int64_t> dp(n);
    vector<deque<pair<int, int64_t>>> tree(n * 4);

    const int m = ds.size();

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    auto Add = [&](auto &dq, pair<int, int64_t> v) {
        while (dq.size() >= 2) {
            auto a = dq[dq.size() - 2];
            auto b = dq[dq.size() - 1];
            assert(b.first > a.first);
            assert(v.first > b.first);
            if (__int128(a.second - b.second) * (v.first - b.first) >= __int128(b.second - v.second) * (b.first - a.first)) dq.pop_back();
            else break;
        }
        dq.push_back(v);
    };

    auto Ask = [&](auto &dq, int x) {
        while (dq.size() >= 2) {
            int64_t v0 = 1LL * dq[0].first * x + dq[0].second;    
            int64_t v1 = 1LL * dq[1].first * x + dq[1].second;    
            if (v1 >= v0) dq.pop_front();
            else break;
        }
        if (dq.empty()) return -kInf;
        return (int64_t)dq[0].first * x + dq[0].second;
    };

    auto Modify = [&](int p, pair<int, int64_t> v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            Add(tree[o], v);
            if (r - l == 1) return;
            int m = (l + r) >> 1;
            if (p < m) self(self, l, m, o * 2 + 1);
            else self(self, m, r, o * 2 + 2);
        };

        _(_, 0, m);
    };


    auto Query = [&](int ql, int qr, int x) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return -kInf;
            if (l >= ql && r <= qr) return Ask(tree[o], x);
            int m = (l + r) >> 1;
            return max(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
        };
        return _(_, 0, m);
    };
    int64_t res = -1LL * n * (n + 1) / 2;

    for (int i = 0; i < n; ++i) {
        dp[i] = -1LL * i * (i + 1) / 2 + a[i];
        int64_t v = Query(0, b[i] + 1, i) - 1LL * i * i + i;
        dp[i] = max(dp[i], v / 2 + a[i]);
        int64_t w = 2 * dp[i] - 1LL * i * i - i;
        Modify(b[i], make_pair(2 * i, w));
        // for (int j = 0; j < i; ++j) {
        //     if (a[i] >= a[j]) {
        //         dp[i] = max(dp[i], dp[j] - int64_t(1) * (i - j) * (i - j - 1) / 2 + a[i]);
        //     }
        // }
        int64_t g = 1LL * (n - i - 1) * (n - i) / 2;
        res = max(res, dp[i] - g);
    }
    cout << res << "\n";
}

