#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
int dp[maxn];
bool v[maxn], w[maxn];

int mex(const vector<int> y) {
    for (int i = 0; i < (int)y.size(); ++i)
        w[y[i]] = true;
    int res = 0;
    while (w[res]) ++res;
    for (int i = 0; i < (int)y.size(); ++i)
        w[y[i]] = false;
    return res;
}
int dfs(int x) {
    if (v[x]) return dp[x];
    vector<int> to;
    for (int i = 0; i <= x - 2; ++i) {
        int j = x - 2 - i;
        to.push_back(dfs(i) ^ dfs(j));
    }
    v[x] = true;
    dp[x] = mex(to);
    return dp[x];
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        int sg = dfs(n);
        if (sg) puts("First");
        else puts("Second");
    }
}
