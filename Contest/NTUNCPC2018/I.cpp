#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], cnt[maxn];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<int> ds;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]), ds.push_back(a[i]);
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
        ++cnt[a[i]];
    }
    vector<int> v(ds.size());
    for (int i = 0; i < (int)v.size(); ++i) v[i] = i;
    sort(v.begin(), v.end(), [&](int i, int j) { return cnt[i] > cnt[j]; });
    int j = 0, sz = 0;
    long long s = 0;
    long long ans = -1;
    for (int i = 0; i < (int)v.size(); ++i) {
        while (j < (int)v.size() && cnt[v[j]] >= cnt[v[i]]) {
            s += cnt[v[j]];
            sz++;
            ++j;
        }
        long long need = (s - cnt[v[i]]) - cnt[v[i]] * 1ll * (sz - 1) + (sz - 1);
        if (need <= m) {
            long long left = m - need;
            if (n - need - cnt[v[i]] >= left) ans = max(ans, 1ll * ds[v[i]]);
            if (n - cnt[v[i]] <= m && m < n) ans = max(ans, 1ll * ds[v[i]]);
        }
    }
    printf("%lld\n", ans);
}
