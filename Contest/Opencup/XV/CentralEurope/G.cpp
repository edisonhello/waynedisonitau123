#include <bits/stdc++.h>
using namespace std;

int a[500005];
vector<int> pos[500005];
int L[500005], R[500005];
int st[21][500005];

int query(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1);
    return min(st[p][l - 1], st[p][r - (1 << p)]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> num;
    for (int i = 1; i <= n; ++i) num.push_back(a[i]);
    sort(num.begin(), num.end());
    num.resize(unique(num.begin(), num.end()) - num.begin());
    for (int i = 1; i <= n; ++i) a[i] = upper_bound(num.begin(), num.end(), a[i]) - num.begin();
    for (int i = 0; i < n; ++i) st[0][i] = a[i + 1];
    for (int z = 1; (1 << z) <= n; ++z) for (int i = 0; i + (1 << z) <= n; ++i) st[z][i] = min(st[z - 1][i], st[z - 1][i + (1 << (z - 1))]);
    for (int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
    for (int i = 1; i <= n; ++i) {
        L[i] = i - 1;
        while (L[i] >= 1 && a[i] > a[L[i]])
            L[i] = L[L[i]];
    }
    for (int i = n; i >= 1; --i) {
        R[i] = i + 1;
        while (R[i] <= n && a[i] > a[R[i]])
            R[i] = R[R[i]];
    }

    for (int i = 1; i <= n; ++i) L[i]++, R[i]--;
    int mx = 1, at = 1;
    for (int i = 1; i <= n; ++i) {
        int mn = query(L[i], R[i]);
        // cout << "pos = " << i << " , [" << L[i] << " , " << R[i] << "], min = " << mn << endl;
        if (mn == a[i]) continue;
        auto it = lower_bound(pos[mn].begin(), pos[mn].end(), i);
        if (it != pos[mn].begin()) {
            --it;
            int l = (it == pos[mn].begin() ? 1 : *prev(it) + 1);
            int r = (next(it) == pos[mn].end() ? n : *next(it) - 1);
            l = max(L[i], l);
            r = min(R[i], r);
            // cout << "l case, " << l << " to " << r << endl;
            if (r - l + 1 > mx) {
                mx = r - l + 1;
                at = l;
            } else if (r - l + 1 == mx) {
                if (l < at) {
                    at = l;
                }
            }
            ++it;
        }
        if (it != pos[mn].end()) {
            int l = (it == pos[mn].begin() ? 1 : *prev(it) + 1);
            int r = (next(it) == pos[mn].end() ? n : *next(it) - 1);
            l = max(L[i], l);
            r = min(R[i], r);
            // cout << "r case, " << l << " to " << r << endl;
            if (r - l + 1 > mx) {
                mx = r - l + 1;
                at = l;
            } else if (r - l + 1 == mx) {
                if (l < at) {
                    at = l;
                }
            }
        }
    }
    cout << mx << " " << at << endl;
}
