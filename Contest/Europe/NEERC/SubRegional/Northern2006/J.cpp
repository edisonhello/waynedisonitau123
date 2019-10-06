#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int cnt[maxn];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 0; i < k; ++i) scanf("%d", &cnt[i]);
    int ans = 0;
    vector<int> v;
    function<bool(int)> check = [&](int p) {
        vector<int> pile(k);
        for (int i = 0; i < k; ++i) pile[i] = cnt[i] / p;
        vector<int> x;
        for (int i = 0; i < k; ++i) {
            while (x.size() < n && pile[i]) x.push_back(i), pile[i]--;
        }
        if (x.size() == n) {
            v = x;
            return true;
        }
        return false;
    };
    for (int d = 30; d >= 0; --d) {
        int p = ans + (1 << d);
        if (p > n) continue;
        if (check(p)) ans += (1 << d);
    }
    printf("%d\n", ans);
    for (int i = 0; i < n; ++i) printf("%d ", v[i] + 1);
    puts("");
}
