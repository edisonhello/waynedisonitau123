#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 5;
bool v[maxn], u[maxn];
int dv[maxn], mul[maxn];

int main() {
    vector<int> pr;
    for (int i = 2; i < maxn; ++i) {
        if (!v[i]) {
            pr.push_back(i);
            dv[i] = i;
        }
        for (int j = 0; i * pr[j] < maxn; ++j) {
            v[i * pr[j]] = true;
            dv[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }

    int n; scanf("%d", &n);
    for (int i = 0; i < maxn; ++i) mul[i] = 1;
    u[1] = u[2] = true;
    mul[2] = 2;
    vector<int> ans = {1, 2};

    while ((int)ans.size() < n) {
        int last = ans.back();
        int cnd = 1e9;
        while (last > 1) {
            int x = dv[last];
            // printf("x = %d mul = %d\n", x, mul[x]);
            while (u[x * mul[x]]) ++mul[x];
            cnd = min(cnd, x * mul[x]);
            while (last % x == 0) last /= x;
        }
        u[cnd] = true;
        ans.push_back(cnd);
    }

    printf("%d\n", ans[n - 1]);
    return 0;
}
