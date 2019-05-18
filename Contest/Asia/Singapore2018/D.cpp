#include <bits/stdc++.h>
using namespace std;

const int magic = 15;
const int maxn = 1e6 + 5;
int a[maxn], n, k;

bool check2(int x) {
    for (int i = 0; i < n; ++i) {
        int c = 0, s = 0;
        for (int j = i, k = 0; k < n; ++k, j = (j + 1) % n) {
            c |= a[j];
            if ((c & x) == x) {
                c = 0;
                ++s;
            }
        }
        if (s >= k) return true;
    }
    return false;
}

bool check1(int x) {
    int p = 0;
    for (int t = 0; t < magic; ++t) {
        int c = 0, s = 0, last = -1, i = p;
        for (int j = 0; j < n; ++j) {
            c |= a[i];
            if ((c & x) == x) {
                ++s;
                last = i + 1;
                c = 0;
                if (last >= n) last = 0;
            }
            if ((++i) >= n) i = 0;
        }
        if (s >= k) return true;
        p = last;
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    // n = 1000000, k = 999999;
    // n = 1000, k = 500;
    // for (int i = 0; i < n; ++i) a[i] = rand() % 1000000000 + 1;
    int ans1 = 0, ans2 = 0;
    for (int b = 30; b >= 0; --b) {
        int x1 = ans1 + (1 << b);
        // int x2 = ans2 + (1 << b);
        if (check1(x1)) ans1 = x1;
        // if (check2(x2)) ans2 = x2;
    }
    // printf("%d %d\n", ans1, ans2);
    // assert(ans1 == ans2);
    printf("%d\n", ans1);
    return 0;
}


