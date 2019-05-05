#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int h[100005], nxt[100005];
int st[19][100005];
int ans[100005];

void build(int n) {
    for (int i = 0; i < n; ++i)
        st[0][i] = h[i + 1];

    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 0; j + (1 << i) <= n; ++j)
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]); 
    }
}

int query(int l, int r) {
    --l, --r;
    int p = 31 - __builtin_clz(r - l + 1);
    return max(st[p][l], st[p][r - (1 << p) + 1]);
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> h[i]; h[n + 1] = 1000000005;
        stack<int> s; s.push(n + 1); ans[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            while (h[s.top()] <= h[i]) s.pop();
            ans[i] = ans[s.top()] + 1;
            nxt[i] = s.top();
            s.push(i);
        }
        map<int, int> mp;
        mp[0] = 0;
        for (int i = 1; i <= n; i = nxt[i]) {
            int sz = mp.size();
            mp[i] = sz;
        }
        build(n + 1);
        while (m--) {
            int x, v; cin >> x >> v;
            auto it = mp.lower_bound(x);
            if (it == mp.end()) {
                if (v > h[prev(mp.end())->first]) {
                    cout << mp.size() << '\n';
                } else {
                    cout << mp.size() - 1 << '\n';
                }
            } else {
                if (v > h[prev(it)->first]) {
                    int L = x + 1, R = n + 1;
                    while (R > L) {
                        int M = (L + R + 1) >> 1;
                        if (query(x + 1, M) > v) R = M - 1;
                        else L = M;
                    }
                    if (query(x + 1, L) > v) cout << prev(it)->second + ans[L] + 1 << '\n';
                    else cout << prev(it)->second + ans[L + 1] + 1 << '\n';
                } else {
                    int L = x + 1, R = n + 1;
                    while (R > L) {
                        int M = (L + R + 1) >> 1;
                        if (query(x + 1, M) > h[prev(it)->first]) R = M - 1;
                        else L = M;
                    }
                    if (query(x + 1, L) > h[prev(it)->first]) cout << prev(it)->second + ans[L] << '\n';
                    else cout << prev(it)->second + ans[L + 1] << '\n';
                }
            }
        }
    }
}
