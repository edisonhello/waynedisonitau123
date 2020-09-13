#include <bits/stdc++.h>
using namespace std;

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int birth[404];

int main() {
    auto parse = [&] (int m, int d) {
        int pre = 0;
        for (int i = 1; i < m; ++i) pre += days[i];
        return pre + d;
    };

    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int m, d;
        scanf("%*s%d-%d", &m, &d);
        birth[parse(m, d)] = 1;
    }

    int mx = -1;
    int mm = -1, md = -1;

    auto update = [&] (int m, int d) {
        int _ = parse(10, 27);
        int l = parse(mm, md) - _;
        int k = parse(m, d) - _;
        if (l <= 0) l += 365;
        if (k <= 0) k += 365;

        if (k < l) {
            mm = m;
            md = d;
        }
    };

    int safe = 0;
    for (int m = 1; m <= 12; ++m) {
        for (int d = 1; d <= days[m]; ++d) {
            int i = parse(m, d);
            if (birth[i] == 1) {
                safe = 0;
            } else {
                ++safe;
                if (safe > mx) {
                    mx = safe;
                    mm = m, md = d;
                } else if (safe == mx) {
                    update(m, d);
                }
            }
            // printf("m d = %d %d, i = %d, safe = %d, mx = %d, mm = %d, md = %d\n", m, d, i, safe, mx, mm, md);
        }
    }
    for (int m = 1; m <= 12; ++m) {
        for (int d = 1; d <= days[m]; ++d) {
            int i = parse(m, d);
            if (birth[i] == 1) {
                safe = 0;
            } else {
                ++safe;
                if (safe > mx) {
                    mx = safe;
                    mm = m, md = d;
                } else if (safe == mx) {
                    update(m, d);
                }
            }
            // printf("m d = %d %d, i = %d, safe = %d, mx = %d, mm = %d, md = %d\n", m, d, i, safe, mx, mm, md);
        }
    }

    printf("%02d-%02d\n", mm, md);
}

