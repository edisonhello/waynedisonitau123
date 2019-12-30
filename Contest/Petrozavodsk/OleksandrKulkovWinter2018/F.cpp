#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;

struct Edge {
    int t, u, v, w;
    Edge() = default;
    Edge(int t, int u, int v, int w) : t(t), u(u), v(v), w(w) {}
    bool operator<(const Edge &e) const {
        if (w == e.w) return t > e.t;
        return w > e.w;
    }
};

int uf[kN], sz[kN], mk[kN];

int Find(int x) {
    if (x == uf[x]) return x;
    int g = Find(uf[x]);
    mk[x] |= mk[uf[x]];
    return uf[x] = g;
}

void Merge(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (!mk[x]) swap(x, y);
    uf[x] = y;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<Edge> ed;
    for (int i = 0; i < m; ++i) {
        int t, u, v, w; scanf("%d%d%d%d", &t, &u, &v, &w);
        u--, v--;
        ed.emplace_back(t, u, v, w);
    }
    sort(ed.begin(), ed.end());
    for (int i = 0; i < n; ++i) {
        uf[i] = i;
        mk[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        // printf("%d %d %d %d\n", ed[i].t, ed[i].u, ed[i].v, ed[i].w);
        if (ed[i].t == 0) {
            if (Find(ed[i].u) != Find(ed[i].v)) {
                mk[Find(ed[i].u)] = 1;
                mk[Find(ed[i].v)] = 1;
                // for (int j = 0; j < n; ++j) printf("%d ", uf[j]); puts("");
                // printf("Mark %d %d\n", Find(ed[i].u), Find(ed[i].v));
            }
        }
        Merge(ed[i].u, ed[i].v);
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int g = Find(i);
        if (!mk[i]) ans.push_back(i);
    }
    printf("%d\n", (int)ans.size());
    for (int u : ans) printf("%d ", u + 1);
    puts("");
}
