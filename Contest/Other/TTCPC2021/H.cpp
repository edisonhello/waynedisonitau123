#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, k, t;
    cin >> N >> k >> t;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<int> ds(A.begin(), A.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    const int M = ds.size();
    vector<int> fw(M + 1);

    auto Update = [&](int p, int v) {
        for (int i = p + 1; i <= M; i += i & -i) fw[i] += v;
    };

    auto Query = [&](int p) {
        int res = 0;
        for (int i = p + 1; i > 0; i -= i & -i) res += fw[i];
        return res;
    };

    int64_t ans = 0;
    for (int i = 0, j = 0; i < N; ++i) {
        int p = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin();
        Update(p, 1);
        if (i - j > k) {
            int p = lower_bound(ds.begin(), ds.end(), A[j]) - ds.begin();
            Update(p, -1);
            j++;
        }
        int r = upper_bound(ds.begin(), ds.end(), A[i] + t) - ds.begin() - 1;
        ans += Query(r);
        int l = lower_bound(ds.begin(), ds.end(), A[i] - t) - ds.begin();
        ans -= Query(l - 1);
    }
    cout << ans + ans - N << "\n";
}
