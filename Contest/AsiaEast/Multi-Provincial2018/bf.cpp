#include <bits/stdc++.h>
using namespace std;

struct point {
    long long x, y;
    double abs() { return hypot(x, y); }
};
point operator-(const point a, const point b) { return point{a.x - b.x, a.y - b.y}; }
long long operator*(const point a, const point b) { return a.x * b.x + a.y * b.y; }
long long operator^(const point a, const point b) { return a.x * b.y - a.y * b.x; }

bool line(point a, point b, point c) {
    return ((b - a) ^ (c - b)) == 0;
}

vector<int> G[100005];
int len[100005], nxt[100005];

void dfs(int now) {
    for (int i : G[now]) {
        if (!len[i]) dfs(i);
        if (len[i] + 1 > len[now] || (len[i] + 1 == len[now] && nxt[now] > i)) {
            len[now] = len[i] + 1;
            nxt[now] = i;
        }
    }
}

int main() {
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        point a, b; cin >> a.x >> a.y >> b.x >> b.y;
        int n; cin >> n;
        for (int i = 0; i <= n; ++i) G[i].clear(), len[i] = 0, nxt[i] = INT_MAX;
        vector<point> ps(n);
        for (point &p : ps) cin >> p.x >> p.y;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) if (i != j) {
                long long ara = abs((ps[i] - a) ^ (b - a));
                if (ara == 0) continue;
                long long a1 = abs((ps[j] - a) ^ (ps[j] - b));
                long long a2 = abs((ps[j] - ps[i]) ^ (ps[j] - b));
                long long a3 = abs((ps[j] - a) ^ (ps[j] - ps[i]));
                if (a1 == 0 || a2 == 0 || a3 == 0) continue;
                if (a1 + a2 + a3 == ara) G[i].push_back(j);
            }
        }
        for (int i = 0; i < n; ++i) if (!len[i]) dfs(i);
        int st = 0;
        for (int i = 0; i < n; ++i) if (len[i] > len[st]) st = i;
        vector<int> ans;
        while (st != INT_MAX) {
            ans.push_back(st);
            st = nxt[st];
        }
        cout << ans.size() << endl;
        for (int i : ans) cout << i + 1 << endl;
    }
}
