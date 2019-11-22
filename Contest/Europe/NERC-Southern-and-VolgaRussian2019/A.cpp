#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
int a[kN], x[kN], y[kN], p[kN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        x[i] = i;
        y[i] = i;
        p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int g; scanf("%d", &g); --g;
        if (p[g] == 0) continue;
        int z = a[p[g]- 1];
        x[z] = min(x[z], p[g]);
        y[z] = max(y[z], p[g]);
        swap(a[p[g]], a[p[g] - 1]);
        p[z] = p[g];
        p[g]--;
        x[g] = min(x[g], p[g]);
        y[g] = max(y[g], p[g]);
    }
    for (int i = 0; i < n; ++i) printf("%d %d\n", x[i] + 1, y[i] + 1);
}
