#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
vector<int> p[maxn];
int a[maxn], b[maxn], c[maxn], d[maxn];
int l[maxn], r[maxn], sum[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    vector<int> ds(a, a + n);
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();

    for (int i = 0; i < n; ++i) p[a[i]].push_back(i);

    for (int i = 0; i < n; ++i) b[i] = a[i];
    sort(b, b + n);

    int ans = 0;
    for (int i = 0; i < (int)ds.size(); ++i) {
        l[i] = p[i].front();
        r[i] = p[i].back();
        sum[i] = p[i].size();
    }

    for (int i = 1; i < (int)ds.size(); ++i)
        sum[i] += sum[i - 1];

    for (int i = (int)ds.size() - 1; i >= 0; --i) {
        d[i] = i;
        if (i + 1 < (int)ds.size() && r[i] < l[i + 1])
            d[i] = d[i + 1];
    }

    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n && b[j] == b[i]) ++j;
        int nxt = j - i;
        int pos = p[b[i]][nxt - 1];
        // printf("pos = %d\n", pos);
        // printf("b[i] = %d\n", b[i]);
        int got = j - i;
        if (b[i] + 1 < (int)ds.size()) {
            // printf("jizz\n");
            if (pos < l[b[i] + 1]) {
                int f = r[d[b[i] + 1]];
                got += sum[d[b[i] + 1]] - sum[b[i]];
                // printf("f = %d got = %d\n", f, got);
                if (d[b[i] + 1] + 1 < (int)ds.size()) {
                    int g = lower_bound(p[d[b[i] + 1] + 1].begin(), p[d[b[i] + 1] + 1].end(), f) - p[d[b[i] + 1] + 1].begin();
                    got += p[d[b[i] + 1] + 1].size() - g;
                }
            } else {
                int g = lower_bound(p[b[i] + 1].begin(), p[b[i] + 1].end(), pos) - p[b[i] + 1].begin();
                got += p[b[i] + 1].size() - g;
            }
            ans = max(ans, got);
        }
        ans = max(ans, got);
    }

    printf("%d\n", n - ans);
    return 0;
}
