#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e15;
vector<pair<int, int>> g[maxn], r[maxn], rr[maxn];
int ed[maxn + maxn], w[maxn + maxn], ww[maxn + maxn], sts[maxn + maxn], eds[maxn + maxn];
long long dt[2][maxn], dr[2][maxn];
bool v[maxn], on[maxn + maxn];

template <typename t>
using heap = priority_queue<t, vector<t>, greater<t>>;

void dijk(int s, vector<pair<int, int>> g[maxn], long long d[maxn]) {
    // puts("dijk");
    for (int i = 0; i < maxn; ++i) d[i] = inf, v[i] = false;
    d[s] = 0;
    heap<pair<long long, int>> pq;
    pq.emplace(0, s);
    while (pq.size()) {
        int x = pq.top().second; pq.pop();
        if (v[x]) continue;
        v[x] = true;
        for (const auto &e : g[x]) {
            int u = e.first, w = e.second;
            if (d[u] > d[x] + w) {
                d[u] = d[x] + w;
                pq.emplace(d[u], u);
            }
        }
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &y, &a, &b);
        --x, --y;
        sts[i] = x, eds[i] = y;
        ed[i] = (x ^ y);
        w[i] = a;
        ww[i] = b;
        g[x].emplace_back(y, a);
        // g[y].emplace_back(x, a);
        r[x].emplace_back(y, b);
        rr[y].emplace_back(x, b);
        // r[y].emplace_back(x, b);
    }
    // dijk(0, g, dt[0]);
    //  dijk(n - 1, g, dt[1]);
    dijk(0, r, dr[0]);
    dijk(n - 1, rr, dr[1]);
    for (int i = 0; i < m; ++i) {
        if (dr[1][eds[i]] + ww[i] == dr[1][sts[i]]) on[i] = true;
    }
    // for (int i = 0; i < m; ++i) if (on[i]) printf("%d ", i); puts("");
    // puts("hey");
    int pt; scanf("%d", &pt);
    vector<int> vertex = { 0 };
    vector<long long> enter = { 0 };
    vector<long long> leave = { 0 };
    vector<int> edge;
    int last = 0;
    for (int i = 0; i < pt; ++i) {
        int e, s; scanf("%d%d", &e, &s); --e;
        edge.push_back(e);
        vertex.push_back(last ^ ed[e]);
        last ^= ed[e];
        enter.push_back(leave.back() + w[e]);
        leave.push_back(enter.back() + s);
    }
    vector<long long> rlen = { 0 };
    for (int i = (int)vertex.size() - 1; i >= 1; --i) {
        int e = edge.back();  edge.pop_back();
        rlen.push_back(rlen.back() + w[e]);
    }
    reverse(rlen.begin(), rlen.end());
    int pr; scanf("%d", &pr);
    vector<int> vrabbit = { 0 }, redge;
    vector<long long> trabbit = { 0 };
    vector<long long> rrlen = { 0 };
    vector<int> again;
    last = 0;
    for (int i = 0; i < pr; ++i) {
        int e; scanf("%d", &e); --e;
        again.push_back(e);
        redge.push_back(e);
        vrabbit.push_back(last ^ ed[e]);
        last ^= ed[e];
        trabbit.push_back(trabbit.back() + ww[e]);
    }
    while (redge.size()) {
        int e = redge.back(); redge.pop_back();
        rrlen.push_back(rrlen.back() + ww[e]);
    }
    reverse(rrlen.begin(), rrlen.end());
    // printf("vertex: "); for (int i = 0; i < (int)vertex.size(); ++i) printf("%d ", vertex[i]); puts("");
    // printf("enter: "); for (int i = 0; i < (int)enter.size(); ++i) printf("%lld ", enter[i]); puts("");
    // printf("leave: "); for (int i = 0; i < (int)leave.size(); ++i) printf("%lld ", leave[i]); puts("");
    // printf("vrabbit: "); for (int i = 0; i < (int)vrabbit.size(); ++i) printf("%d ", vrabbit[i]); puts("");
    // printf("trabbit: "); for (int i = 0; i < (int)trabbit.size(); ++i) printf("%lld ", trabbit[i]); puts("");
    vector<int> ans;
    for (int i = 0; i < (int)vrabbit.size() - 1; ++i) {
        int x = vrabbit[i];
        if (rrlen[i] == dr[1][x]) continue;
        int at = upper_bound(enter.begin(), enter.end(), trabbit[i]) - enter.begin();
        if (at < enter.size()) {
            if (enter[at] + rlen[at] >= trabbit[i] + dr[1][x]) {
                if (on[again[i]]) continue;
                ans.push_back(x);
            }
        }
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) printf("%d ", ans[i] + 1); puts("");
}
