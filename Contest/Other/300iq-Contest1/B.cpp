#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> w(n);
    for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
    int ans = 2'000'000'000;

    auto Check = [&](int v) {
        vector<int> goods;
        for (int i = 0; i < n; ++i) {
            if (w[i] * 2 <= v) goods.push_back(i);
        }
        if (goods.empty()) return 0;
        if (goods.size() == 1) {
            for (int i = 0; i < n; ++i) {
                if (i == goods[0]) continue;
                if (w[i] + w[goods[0]] <= v) return 2;
            }
            return 1;
        }
        int res = goods.size();
        for (int i = 0; i + 1 < goods.size(); ++i) {
            int64_t kv = v + 1;
            for (int j = goods[i] + 1; j < goods[i + 1]; ++j) kv = min(kv, (int64_t)w[j]);
            if (kv + w[goods[i]] <= v && kv + w[goods[i + 1]] <= v) res++;
        }
        int64_t kv = v + 1;
        for (int i = goods.back() + 1; i < n; ++i) kv = min(kv, (int64_t)w[i]);
        for (int i = 0; i < goods.front(); ++i) kv = min(kv, (int64_t)w[i]);
        if (kv + w[goods.back()] <= v && kv + w[goods.front()] <= v) res++;
        return res;
    };

    for (int d = 31; d >= 0; --d) {
        if (ans - (1 << d) < 0) continue;
        if (Check(ans - (1 << d)) >= k) ans -= (1 << d);
    }
    printf("%d\n", ans);
}

