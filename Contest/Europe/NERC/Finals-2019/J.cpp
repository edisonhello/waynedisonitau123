#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 4'000'000 + 5;
int c[kN], cnt[kN], cc[kN], rk[kN], sk[kN];
bool used[kN];
vector<int> dv[kN];

int main() {
    int t; scanf("%d", &t);
    for (int i = 1; i < kN; ++i) {
        for (int j = i; j < kN; j += i) dv[j].push_back(i);
    }
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &c[i]);
            ++cnt[c[i]];
        }
        sort(c, c + n);
        n = unique(c, c + n) - c;
        for (int i = 0; i < n; ++i) ++cc[cnt[c[i]]];
        vector<int> p;
        for (int i = 0; i < n; ++i) {
            if (used[cnt[c[i]]]) continue;
            used[cnt[c[i]]] = true;
            vector<pair<int, int>> uv;
            // printf("cnt[c[i]] = %d\n", cnt[c[i]]);
            for (int j = 0; j <= cnt[c[i]]; ++j) {
                for (int s : dv[cnt[c[i]] + j]) {
                    int us = (cnt[c[i]] + j) / s;
                    if (us < j) continue;
                    uv.emplace_back(s, us);
                }
            }
            sort(uv.begin(), uv.end());
            for (int j = 0, k = 0; j < uv.size(); j = k) {
                int ck = 1e9;
                for (k = j; k < uv.size() && uv[j].first == uv[k].first; ++k) ck = min(ck, uv[k].second);
                rk[uv[j].first] += cc[cnt[c[i]]];
                sk[uv[j].first] += cc[cnt[c[i]]] * ck;
                p.push_back(uv[j].first);
                // printf("s = %d ck = %d\n", uv[j].first, ck);
            }
        }
        int ans = 1e9;
        for (int u : p) {
            if (rk[u] == n) ans = min(ans, sk[u]);
        }
        for (int u : p) {
            rk[u] = 0;
            sk[u] = 0;
        }
        for (int i = 0; i < n; ++i) used[cnt[c[i]]] = false;
        for (int i = 0; i < n; ++i) cc[cnt[c[i]]] = 0;
        for (int i = 0; i < n; ++i) cnt[c[i]] = 0;
        printf("%d\n", ans);
    }
    return 0;
}
