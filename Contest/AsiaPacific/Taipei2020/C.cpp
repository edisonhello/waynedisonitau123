#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int pre[10004][10004];

int main() {
    int t; cin >> t; while (t--) {
        int n, k; cin >> n >> k;
        pre[0][0] = k - 1;
        for (int i = 1; i <= n; ++i) {
            memset(pre[i], 0, (i + 1) << 2);
            for (int j = 0; j < i; ++j) {
                pre[i][j] += (pre[i - 1][j] + 1) >> 1;
                pre[i][j + 1] += pre[i - 1][j] >> 1;
            }

            // for (int j = 0; j <= i; ++j) {
            //     cerr << "pre[" << i << "][" << j << "] = " << pre[i][j] << endl;
            // }
        }

        int me = 0;
        for (int i = 1; i < n; ++i) {
            if (pre[i - 1][me] & 1) ++me;
        }

        cout << me << '\n';
    }
}
