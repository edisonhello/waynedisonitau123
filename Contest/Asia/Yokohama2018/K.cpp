#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
int a[maxn], b[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &b[i]);

    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int i, int j) {
        return a[i] < a[j];
    });

    multiset<int> ms;
    for (int i = 0; i < n; ++i) ms.insert(b[i]);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[v[i]];
        auto it = ms.upper_bound(x);
        if (it != ms.end()) {
            ms.erase(it);
            ++k;
        }
    }

    vector<int> w(b, b + n);
    sort(w.begin(), w.end());

    auto check = [&](int p, int z, int k) {
        // printf("check p = %d w.size() = %d z = %d k = %d\n", p, (int)w.size(), z, k);
        int win = (w[p] > a[z]);
        vector<int> ww(w.begin(), w.end());
        ww.erase(ww.begin() + p);
        vector<int> vv(v.begin(), v.end());
        vv.erase(find(vv.begin(), vv.end(), z));

        // printf("ww: "); for (int i : ww) printf("%d ", i); puts("");
        // printf("vv: "); for (int i : vv) printf("%d ", i); puts("");

        bool ok = true;

        // printf("k - win = %d\n", k - win);
        for (int i = 0, j = 0; i < k - win; ++i) {
            while (j < (int)ww.size() && ww[j] <= a[vv[i]]) ++j;
            // printf("i = %d j = %d\n", i, j);
            ok &= j < (int)ww.size();
            ++j;
        }
        // printf("check done p = %d z = %d k = %d\n", p, z, k);
        return ok;
    };

    for (int i = 0; i < n; ++i) {
        int p = 0;
        bool ok = w.back() > a[i];
        int ub = w.size();
        if (ok) p = upper_bound(w.begin(), w.end(), a[i]) - w.begin();
        else ub = upper_bound(w.begin(), w.end(), a[i]) - w.begin();
        for (int d = 12; d >= 0; --d) {
            if (p + (1 << d) >= ub) continue;
            if (check(p + (1 << d), i, k)) p += (1 << d);
        }
        // printf("p = %d w.size() = %d\n", p, (int)w.size());
        printf("%d ", w[p]);
        if (w[p] > a[i]) --k;
        w.erase(w.begin() + p);
        auto it = find(v.begin(), v.end(), i);
        assert(it != v.end());
        v.erase(find(v.begin(), v.end(), i));
    }
}
