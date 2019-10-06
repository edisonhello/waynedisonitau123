#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int a[2][maxn], b[2][maxn];
vector<pair<int, int>> pos[maxn];

int main() {
    int n; scanf("%d", &n);
    vector<int> ds;
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[j][i]);
            ds.push_back(a[j][i]);
        }
    }

    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < n; ++i) {
            b[j][i] = lower_bound(ds.begin(), ds.end(), a[j][i]) - ds.begin();
        }
    }

    auto check = [&](int p) {
        for (int i = 0; i < 2; ++i) {
            int last = -1;
            for (int j = 0; j < n; ++j) {
                if (b[i][j] < p) continue;
                if (last == -1) {
                    last = b[i][j];
                } else {
                    if (last != b[i][j]) return false;
                    last = -1;
                }
            }
            if (last != -1) return false;
        }
        return true;
    };

    int ans = ds.size();
    for (int d = 20; d >= 0; --d) {
        if (ans - (1 << d) < 0) continue;
        if (check(ans - (1 << d))) ans -= (1 << d);
    }

    if (ans == 0) printf("0\n");
    else printf("%d\n", ds[ans - 1]);
    return 0;
}
