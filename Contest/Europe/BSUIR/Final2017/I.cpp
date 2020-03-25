#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> cnt(n);
    vector<int> nxt(n);

    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n && cnt[a[j]] == 0) {
            cnt[a[j]]++;
            j++;
        }
        nxt[i] = j - 1;
        cnt[a[i]]--;
    }

    // for (int i = 0; i < n; ++i) cerr << nxt[i] << " ";
    // cerr << "\n";

    auto Check = [&](int l, int r) {
        return nxt[l] >= r;
    };

    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + (a[i] == 0);

    auto DivideConquer = [&](auto self, int l, int r) -> int64_t {
        if (r - l == 1) return a[l] == 0;
        int m = (l + r) >> 1;
        int64_t res = self(self, l, m) + self(self, m, r);
        for (int i = m, x = 0, k = m - 1, y = 0; i < r; ++i) {
            x = max(x, a[i]);
            while (k >= l && max(y, a[k]) <= x) {
                y = max(y, a[k]);
                --k;
            }
            int j = i - x;
            if (j >= l && j < m && j > k) {
                if (!Check(j, i)) continue;
                if (pref[i + 1] - pref[j] == 1) {
                    ++res;
                    // cerr << "found " << j << " " << i << endl;
                }
            }
        }
        for (int i = m - 1, x = 0, k = m, y = 0; i >= l; --i) {
            x = max(x, a[i]);
            while (k < r && max(y, a[k]) <= x) {
                y = max(y, a[k]);
                k++;
            }
            int j = i + x;
            if (j >= m && j < r && j < k) {
                if (!Check(i, j)) continue;
                if (pref[j + 1] - pref[i] == 1) {
                    ++res;
                    // cerr << "found " << i << " " << j << endl;
                }
            }
        }
        // cerr << "Solve l = " << l << " r = " << r << " res = " << res << endl;
        return res;
    };

    cout << DivideConquer(DivideConquer, 0, n) << "\n";
}

