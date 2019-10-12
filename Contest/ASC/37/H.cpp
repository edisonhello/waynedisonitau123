#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Ship {
    int d, c, s, id;
    Ship() = default;
    Ship(int d, int c, int s, int id) : d(d), c(c), s(s), id(id) {}

    bool operator<(const Ship &sh) const {
        if (d != sh.d) return d < sh.d;
        return id < sh.id;
    }
};

struct Crane {
    vector<int> ty;
    int v;

    Crane() = default;
    Crane(int v, vector<int> &&ty) : v(v), ty(move(ty)) {}
};

const int maxn = 1e6 + 5;
set<pair<int, int>> pq[50];
int ans[maxn];

int32_t main() {
#ifdef ONLINE_JUDGE
    freopen("seaport.in", "r", stdin);
    freopen("seaport.out", "w", stdout);
#endif
    int n, m, c; scanf("%lld%lld%lld", &n, &m, &c);

    vector<Ship> ship;
    for (int i = 0; i < n; ++i) {
        int d, c, s; scanf("%lld%lld%lld", &d, &c, &s);
        ship.emplace_back(d, c, s, i); 
    }

    sort(ship.begin(), ship.end());

    vector<Crane> crane;
    for (int i = 0; i < m; ++i) {
        int v, t; scanf("%lld%lld", &v, &t);
        vector<int> ty(t);
        for (int j = 0; j < t; ++j)
            scanf("%lld", &ty[j]);
        crane.emplace_back(v, move(ty)); 
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < (int)crane[i].ty.size(); ++j) {
            pq[crane[i].ty[j]].insert(make_pair(0, i));
        }
    }

    for (int i = 0; i < n; ++i) {
        Ship sh = ship[i];
        auto cr = *pq[sh.c].begin();
        for (int j : crane[cr.second].ty) pq[j].erase(cr);
        int t = max(sh.d, cr.first);
        int nd = (sh.s + crane[cr.second].v - 1) / crane[cr.second].v;
        ans[sh.id] = cr.second + 1;
        for (int j : crane[cr.second].ty) pq[j].insert(make_pair(t + nd, cr.second));
    }
    for (int i = 0; i < n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
