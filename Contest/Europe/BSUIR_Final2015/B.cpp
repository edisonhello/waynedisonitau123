#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

int mp[104][104];

double go(int n, int k) {
    srand(time(0) * clock() + clock());
    // int n, k; cin >> n >> k;
    double cur_ans = 0;
    int case_cnt = 0;
    for (int t = 0; t < 400000; ++t) {
    // while (true) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) mp[i][j] = rand() % k;
        }
        int tot = 0, cnt = 0;
        for (int i1 = 1; i1 <= n; ++i1) {
            for (int i2 = i1; i2 <= n; ++i2) {
                for (int j1 = 1; j1 <= n; ++j1) {
                    vector<int> c(k, 0);
                    int incnt = 0;
                    for (int j2 = j1; j2 <= n; ++j2) {
                        for (int i = i1; i <= i2; ++i) {
                            ++c[mp[i][j2]];
                            if (c[mp[i][j2]] == 1) ++incnt;
                        }
                        ++cnt;
                        tot += incnt;
                    }
                }
            }
        }
        // printf("n = %d, k = %d, %d / %d = %lf\n", n, k, tot, cnt, (double)tot / cnt);
        ++case_cnt; cur_ans += (double)tot / cnt;
        // printf("n = %d, k = %d, %d cases, avg = %lf\n", n, k, case_cnt, (double)cur_ans / case_cnt);
    }
    return (double)cur_ans / case_cnt;
}

int main() {
    for (int n = 1; n <= 10; ++n) {
        for (int k = 1; k <= n * n; ++k) {
            cout << go(n, k) << " "; 
        } cout << endl;
    }
}
