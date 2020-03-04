#include <bits/stdc++.h>
using namespace std;

const int kN = 5000 + 5;
vector<int> g[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n - 1; ++i) {
            int x, y; scanf("%d%d", &x, &y);
        }
        if (n & 1) puts("Alice");
        else puts("Bob");
    }
}
