#include <bits/stdc++.h>
using namespace std;

int dp[1 << 15];
bool vis[1 << 15];

int mex(vector<int> &v) {
    for (int i = 0; i < (int)v.size(); ++i) 
        vis[v[i]] = true;
    int res = 0;
    while (vis[res]) ++res;
    for (int i = 0; i < (int)v.size(); ++i) 
        vis[v[i]] = false;
    return res;
}

int is_leaf(int s, int i) {
    if (s & (1 << (i * 2 + 1))) return 0;
    if (s & (1 << (i * 2 + 2))) return 0;
    return 1;
}

int exist(int s, int i) {
    if (s & (1 << i)) return 1;
    return 0;
}

int dfs(int s) {
    if (s == 0) return 0;
    if (dp[s] >= 0) return dp[s];
    vector<int> v;
    for (int i = 0; i < 15; ++i) {
        if ((s >> i & 1) == 0) continue;
        if (is_leaf(s, i)) v.push_back(dfs(s ^ (1 << i)));
        else if ((!exist(s, i * 2 + 1) || is_leaf(s, i * 2 + 1)) && (!exist(s, i * 2 + 2) || is_leaf(s, i * 2 + 2))) 
            v.push_back(dfs(s ^ (1 << i) ^ (exist(s, i * 2 + 1) ? 1 << (i * 2 + 1) : 0) ^ (exist(s, i * 2 + 2) ? 1 << (i * 2 + 2) : 0)));
        /* int ns = s ^ (1 << i);
        queue<int> q; q.push(i);
        while (q.size()) {
            int now = q.front(); q.pop();
            if (now > 6) continue;
            int lc = now * 2 + 1;
            int rc = now * 2 + 2;
            ns ^= (1 << lc) ^ (1 << rc);
            q.push(lc); q.push(rc);
        }
        v.push_back(dfs(ns)); */
    }
    return dp[s] = mex(v);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int t; scanf("%d", &t);
    while (t--) {
        int f; scanf("%d", &f);
        int ans = 0;
        while (f--) {
            int n; scanf("%d", &n);
            int s = 0;
            for (int i = 0; i < n; ++i) {
                int x; scanf("%d", &x);
                s ^= (1 << x);
            }
            ans ^= dfs(s);
        }
        puts(ans ? "Ella wins" : "Emma wins");
    }
    return 0;
}
