#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int fw[maxn], pref[maxn];
char s[maxn];

void add(int p) {
    for (int i = p + 1; i < maxn; i += i & -i)
        fw[i] += 1;
}

int query(int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i)
        res += fw[i];
    return res;
}

int main() {
    int p, q; scanf("%d%d", &p, &q);
    scanf("%s", s + 1);
    int n = strlen(s + 1);

    for (int i = 1; i <= n; ++i)
        pref[i] = pref[i - 1] + (s[i] == '1');

    vector<long long> ds;
    for (int i = 0; i <= n; ++i)
        ds.push_back(q * 1ll * pref[i] - p * 1ll * i);

    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    long long ans = 0;
    int z = lower_bound(ds.begin(), ds.end(), 0) - ds.begin();
    add(z);
    for (int i = 1; i <= n; ++i) {
        int x = lower_bound(ds.begin(), ds.end(), q * 1ll * pref[i] - p * 1ll * i) - ds.begin();
        ans += query(x - 1);
        add(x);
    }
    printf("%lld\n", ans);
    return 0;
}
