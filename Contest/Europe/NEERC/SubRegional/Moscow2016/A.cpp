#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    int v = -2e9, z = -1;
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        if (x > v) {
            v = x;
            z = i;
        }
    }
    printf("%d %d %d\n", (z + n - 1) % n + 1, z + 1, (z + 1) % n + 1);
}
