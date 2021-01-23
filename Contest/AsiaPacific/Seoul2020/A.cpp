#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y; 
};

bool operator< (const P &a, const P &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
ostream& operator<< (ostream &o, const P p) { return o << "(" << p.x << ", " << p.y << ")"; }

struct L {
    P pa, pb;
    vector<pair<int, int>> crx; // [pos, i]
    int dir;
    int rev;

    void init() {
        if (pb < pa) swap(pa, pb), rev = 1;

        if (pa.x == pb.x) dir = 1; // UD seg
        else dir = 0; // LR seg
    }

    P first() { return rev ? pb : pa; }
    P second() { return rev ? pa : pb; }
    int init_dir() { return dir + rev * 2; }
} ls[555];

bool inside(int a, int b, int c) {
    return a <= b && b <= c;
}

void check_crox(int i, int j) {
    L &li = ls[i], &lj = ls[j];
    if (!inside(lj.pa.x, li.pa.x, lj.pb.x)) return;
    if (!inside(li.pa.y, lj.pa.y, li.pb.y)) return;
    // cerr << "crox " << i << ' ' << j << endl;
    li.crx.emplace_back(lj.pa.y, j);
    lj.crx.emplace_back(li.pa.x, i);
}

int main() {
    int n, t; cin >> n >> t;
    for (int i = 0; i < n; ++i) {
        cin >> ls[i].pa.x >> ls[i].pa.y >> ls[i].pb.x >> ls[i].pb.y;
        ls[i].init();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            L &li = ls[i], &lj = ls[j];
            if (li.dir == lj.dir) continue;
            if (li.dir == 1) check_crox(i, j);
            else check_crox(j, i);
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(ls[i].crx.begin(), ls[i].crx.end());
    }

    // cerr << "checked crx " << endl;

    map<P, int> ptid;
    auto GetId = [&] (P p) {
        auto it = ptid.find(p);
        if (it == ptid.end()) {
            int z = ptid.size();
            ptid[p] = z;
            it = ptid.find(p);
        }
        // cerr << "p " << p << " id " << it->second << endl;
        return it->second;
    };

    for (int i = 0; i < n; ++i) {
        GetId(ls[i].pa);
        GetId(ls[i].pb);
        if (ls[i].dir == 1) {
            for (auto [yy, to] : ls[i].crx) {
                GetId(P{ls[i].pa.x, yy});
            }
        } else {
            for (auto [xx, to] : ls[i].crx) {
                GetId(P{xx, ls[i].pa.y});
            }
        }
    }

    // cerr << "getting ptid" << endl;

    int nn = ptid.size();
    vector<vector<pair<int, int>>> g(nn);
    vector<P> invpt(nn);
    for (auto [p, id] : ptid) invpt[id] = p;

    //cerr << "nn = " << nn << endl;

    //cerr << "calc invpt " << endl;

    auto AddEdge = [&] (P a, P b) {
        int i = GetId(a), j = GetId(b);
        int d = abs(a.x - b.x) + abs(a.y - b.y);
        //cerr << "add edge " << a << " " << b << " id " << i << " " << j << " d " << d << endl;
        g[i].emplace_back(j, d);
        g[j].emplace_back(i, d);
        //cerr << "add edge " << a << " " << b << " id " << i << " " << j << " d " << d << endl;
    };

    for (int i = 0; i < n; ++i) {
        if (ls[i].crx.size() == 0u) {
            AddEdge(ls[i].pa, ls[i].pb);
            continue;
        }
        if (ls[i].dir == 1) {
            int X = ls[i].pa.x;
            AddEdge(ls[i].pa, P{X, ls[i].crx[0].first});
            for (int j = 1; j < (int)ls[i].crx.size(); ++j) {
                AddEdge(P{X, ls[i].crx[j - 1].first}, P{X, ls[i].crx[j].first});
            }
            AddEdge(P{X, ls[i].crx[ls[i].crx.size() - 1].first}, ls[i].pb);
        } else {
            int Y = ls[i].pa.y;
            AddEdge(ls[i].pa, P{ls[i].crx[0].first, Y});
            for (int j = 1; j < (int)ls[i].crx.size(); ++j) {
                AddEdge(P{ls[i].crx[j - 1].first, Y}, P{ls[i].crx[j].first, Y});
            }
            AddEdge(P{ls[i].crx[ls[i].crx.size() - 1].first, Y}, ls[i].pb);
        }
    }

    for (int i = 0; i < nn; ++i) {
        if (g[i].size() == 1u) continue;
        assert(g[i].size() == 4u);
    }

    auto GetNext = [&] (int at, int prev) {
        if (g[at].size() == 1u) return g[at][0];
        assert(g[at].size() == 4u);
        P &pp = invpt[prev];
        P &pnow = invpt[at];
        P &p0 = invpt[g[at][0].first];
        P &p1 = invpt[g[at][1].first];
        P &p2 = invpt[g[at][2].first];
        P &p3 = invpt[g[at][3].first];
        if (pp.x > pnow.x) {
            if (p0.y < pnow.y) return g[at][0];
            if (p1.y < pnow.y) return g[at][1];
            if (p2.y < pnow.y) return g[at][2];
            if (p3.y < pnow.y) return g[at][3];
        } else if (pp.y < pnow.y) {
            if (p0.x < pnow.x) return g[at][0];
            if (p1.x < pnow.x) return g[at][1];
            if (p2.x < pnow.x) return g[at][2];
            if (p3.x < pnow.x) return g[at][3];
        } else if (pp.x < pnow.x) {
            if (p0.y > pnow.y) return g[at][0];
            if (p1.y > pnow.y) return g[at][1];
            if (p2.y > pnow.y) return g[at][2];
            if (p3.y > pnow.y) return g[at][3];
        } else {
            if (p0.x > pnow.x) return g[at][0];
            if (p1.x > pnow.x) return g[at][1];
            if (p2.x > pnow.x) return g[at][2];
            if (p3.x > pnow.x) return g[at][3];
        }
        assert(false);
    };

    auto calc_round = [&] () -> long long {
        int start = GetId(ls[0].first());

        int at = start;
        int nxt = g[at][0].first;
        long long d = g[at][0].second;

        while (nxt != start) {
            auto edge = GetNext(nxt, at);
            at = nxt;
            nxt = edge.first;
            d += edge.second;
        }

        return d;
    };

    auto get_position = [&] (int t) -> P {
        int at = GetId(ls[0].first());
        int nxt = g[at][0].first;
        int pd = 0;
        int d = g[at][0].second;

        while (t > d) {
            auto edge = GetNext(nxt, at);
            at = nxt;
            nxt = edge.first;
            pd = d;
            d += edge.second;
        }

        if (t == d) return invpt[nxt];
        int go = t - pd;
        P s = invpt[at];
        P tt = invpt[nxt];
        if (tt.x > s.x) return P{s.x + go, s.y};
        if (tt.x < s.x) return P{s.x - go, s.y};
        if (tt.y > s.y) return P{s.x, s.y + go};
        if (tt.y < s.y) return P{s.x, s.y - go};
        assert(false);
    };

    // cerr << "start calc" << endl;

    long long a_round = calc_round();

    int tt = t % a_round;

    P pos = get_position(tt);

    cout << pos.x << ' ' << pos.y << endl;
}

