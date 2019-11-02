#include <bits/stdc++.h>
using namespace std;

const int kN = 3000 + 5;
int g[kN][kN], z[kN];
char s[kN][kN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", s[i]);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            if (s[i + 1][j] == s[i][j + 1]) {
                g[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i > 0 && g[i][j] && g[i - 1][j]) {
                puts("YES");
                return 0;
            }
            if (j > 0 && g[i][j] && g[i][j - 1]) {
                puts("YES");
                return 0;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int bt = -1;
        z[i] = -1;
        for (int j = 0; j < n; ++j) {
            if (g[j][i]) bt = j;
            if (g[j][i] && z[i] == -1) z[i] = j;
        }
        if (bt == -1) continue;
        for (int k = 0; k < i; ++k) {
            if (z[k] != -1 && z[k] < bt) {
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}
