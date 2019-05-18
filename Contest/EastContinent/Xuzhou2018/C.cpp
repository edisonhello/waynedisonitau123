#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool same(double a, double b) { return abs(a - b) < eps; }
int CEIL(double x) { return same(x, round(x)) ? round(x) + 1 : ceil(x); }
int FLOOR(double x) { return same(x, round(x)) ? round(x) - 1 : floor(x); }

auto cmp = [&] (const pair<double, double> &a, const pair<double, double> &b) -> bool {
    if (same(a.first, b.first)) {
        if (same(a.second, b.second)) return 0;
        return a.second < b.second;
    } else return a.first < b.first;
};

const int maxn = 55;

int n, states, h[maxn];
map<pair<double, double>, int, decltype(cmp)> state(cmp);
map<pair<int, int>, vector<int>> block;
pair<double, double> istate[maxn * maxn];
vector<vector<int>> G;
double d[maxn * maxn];
bitset<maxn * maxn> vis;

double get_y(double x) {
    if (same(x, round(x))) return h[int(round(x))];
    int L = floor(x);
    double slo = h[L + 1] - h[L];
    return h[L] + slo * (x - L);
}

void add_state(double a, double b) {
    // cerr << "add state " << a << " " << b;
    int &id = state[make_pair(a, b)];
    if (!id) id = state.size();
    // cerr << ", id = " << id << endl;
}

int get_state(double a, double b) {
    // cerr << "get state " << a << " " << b;
    int &id = state[make_pair(a, b)];
    // cerr << ", id = " << id << endl;
    assert(id);
    return id;
}

double calc_distance(int si, int sj) {
    // cerr << "calc_distance state " << si << " and " << sj;
    double ret = hypot(istate[si].first - istate[sj].first, get_y(istate[si].first) - get_y(istate[sj].first)) + hypot(istate[si].second - istate[sj].second, get_y(istate[si].second) - get_y(istate[sj].second));
    // cerr << " is " << ret << endl;
    return ret;
}

double dijkstra(int s) {
    // cerr << "states: " << states << ", s = " << s << endl;
    fill(d + 1, d + 1 + states, 1e9);
    vis.reset();
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    d[s] = 0;
    pq.emplace(0, s);
    while (pq.size()) {
        while (pq.size() && vis[pq.top().second]) pq.pop();
        if (pq.empty()) break;
        int now = pq.top().second;
        // cerr << "now: " << now << " , my distance " << d[now] << endl;
        vis[now] = 1;
        for (int is : G[now]) {
            if (d[is] > d[now] + calc_distance(now, is)) {
                d[is] = d[now] + calc_distance(now, is);
                pq.emplace(d[is], is);
            }
        }
    }
    // cerr << "and d[2] = " << d[2] << endl;
    return d[get_state(n, 0)];
}

void check_connect(int si, int sj) {
    double ix = istate[si].first, iy = istate[si].second;
    double jx = istate[sj].first, jy = istate[sj].second;
    // cerr << "original ix iy jx jy: " << ix << " " << iy << " " << jx << " " << jy << endl;
    // tie(ix, jx) = minmax(ix, jx);
    // tie(iy, jy) = minmax(iy, jy);
    if (jx < ix) swap(jx, ix);
    if (jy < iy) swap(jy, iy);
    if (CEIL(ix) > FLOOR(jx) && CEIL(iy) > FLOOR(jy)) {
        // cerr << "check connect " << "of " << si << " and " << sj << " : " << ix << " " << jx << " " << iy << " " << jy << " -> " << CEIL(ix) << " " << FLOOR(jx) << " " << CEIL(iy) << " " << FLOOR(jy) << endl;
        G[si].push_back(sj), G[sj].push_back(si);
    }
}

int main() {
    int t; scanf("%d", &t); while (t--) {
        state.clear();
        G.clear();
        block.clear();
        scanf("%d", &n);
        for (int i = 0; i <= n; ++i) scanf("%d", &h[i]);
        add_state(0, n);
        add_state(n, 0);
        for (int i = 0; i <= n; ++i) {
            // add_state(i, i);
            for (int j = 0; j < n; ++j) { // seg[j, j + 1]
                int lo = min(h[j], h[j + 1]);
                int hi = max(h[j], h[j + 1]);
                // cerr << "i j: " << i << " " << j << " " << lo << " " << hi << endl;
                if (lo <= h[i] && h[i] <= hi); else continue;
                // cerr << "inside!" << endl;
                if (lo == hi) {
                    add_state(i, j);
                    add_state(j, i);
                    add_state(i, j + 1);
                    add_state(j + 1, i);
                } else {
                    double dist = h[i] - h[j];
                    double tot = h[j + 1] - h[j];
                    double xdist = dist / tot;
                    add_state(i, j + xdist);
                    add_state(j + xdist, i);
                }
            }
        }
        states = state.size();
        G.resize(states + 1);
        for (auto &p : state) {
            istate[p.second] = p.first;
            block[make_pair(int(p.first.first), int(p.first.second))].push_back(p.second);
        }
        for (int i = 1; i <= states; ++i) {
            int xx = istate[i].first, yy = istate[i].second;
            for (int x = xx - 1; x <= xx + 1; ++x) for (int y = yy - 1; y <= yy + 1; ++y) {
                auto it = block.find(make_pair(x, y));
                if (it != block.end()) for (int jstate : it->second) check_connect(i, jstate);
            }
        }
        double ans = dijkstra(get_state(0, n));
        printf("%.20lf\n", ans);
    }
}
