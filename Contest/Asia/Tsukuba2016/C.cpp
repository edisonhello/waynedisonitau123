#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> ld[maxn];
int n, m, ptr[maxn], lb[maxn], rb[maxn], x[maxn], y[maxn];
int s[maxn];

int push_down(int p) {
    if (p == n) return n;
    if (ptr[p] + 1 == (int)ld[p].size()) {
        rb[p] = p;
        return p;
    }
    while (ld[p + 1][ptr[p + 1]] <= ld[p][ptr[p]]) {
        ++ptr[p + 1];
        rb[p + 1] = push_down(p + 1);
    }
    rb[p] = rb[p + 1];
    return rb[p];
}

int push_up(int p) {
    if (p == 1) return 1;
    if (ptr[p] + 1 == (int)ld[p].size()) {
        lb[p] = p;
        return p;
    }
    while (ld[p - 1][ptr[p - 1]] <= ld[p][ptr[p]]) {
        ++ptr[p - 1];
        lb[p - 1] = push_up(p - 1);
    }
    lb[p] = lb[p - 1];
    return lb[p];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = 0; i < maxn; ++i) ld[i].clear();
    for (int i = 0; i < m; ++i) ld[y[i]].push_back(x[i]);
    for (int i = 1; i <= n; ++i) {
        ld[i].push_back(100000);
        sort(ld[i].begin(), ld[i].end());
    }
    for (int i = n; i >= 1; --i) {
        ptr[i] = 0;
        rb[i] = push_down(i);
        --s[rb[i] + 1];
    }
    for (int i = 1; i <= n; ++i) ptr[i] = 0;
    for (int i = 0; i < maxn; ++i) ld[i].clear();
    for (int i = 0; i < m; ++i) ld[y[i] + 1].push_back(x[i]);
    for (int i = 1; i <= n; ++i) {
        ld[i].push_back(100000);
        sort(ld[i].begin(), ld[i].end());
    }
    for (int i = 1; i <= n; ++i) {
        ptr[i] = 0;
        lb[i] = push_up(i);
        ++s[lb[i]];
    }
    // for (int i = 1; i <= n; ++i) {
    // 	printf("%d %d\n", lb[i], rb[i]);
    // }
    for (int i = 1; i < maxn; ++i) s[i] += s[i - 1];
    for (int i = 1; i <= n; ++i) printf("%d ", s[i]);
    puts("");
}
