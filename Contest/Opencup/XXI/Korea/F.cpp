#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, f;
    long long c;
    int ii;
};

vector<edge> g[500005];

void addedge(int u, int v, int f, long long c) {
    // cerr << "addedge " << u << ' ' << v << ' ' << f << ' ' << c << ' ' << endl;
    g[u].push_back(edge{u, v, f, c, (int)g[v].size()});
    g[v].push_back(edge{v, u, 0, -c, (int)g[u].size() - 1});
}

int cfi[500005];
long long d[500005];
int f[500005];
bool inq[500005];
long long flow(int s, int t) {
    // cerr << "fl " << s << ' ' << t << endl;
    long long rt = 0;
    long long co = 0;
    while (true) {
        memset(d, 0x3f, sizeof(d));
        memset(f, 0, sizeof(f));
        f[s] = INT_MAX;
        d[s] = 0;
        // queue<int> q;
        priority_queue<pair<long long, int>> pq;
        // q.emplace(s);
        pq.emplace(0, s);

        // while (q.size()) {
        while (pq.size()) {
            int now = pq.top().second;
            pq.pop();
            // inq[now] = 0;
            // cerr << "now = " << now << endl;

            // for (auto &e : g[now]) {
            for (int ei = 0; ei < (int)g[now].size(); ++ei) {
                auto &e = g[now][ei];
                if (e.f > 0 && d[e.v] > d[now] + e.c) {
                    d[e.v] = d[now] + e.c;
                    f[e.v] = min(f[now], e.f);
                    cfi[e.v] = e.ii;
                    // if (!inq[e.v]) {
                    //     q.push(e.v);
                    //     inq[e.v] = 1;
                    // }
                    pq.emplace(-d[e.v], e.v);
                }
            }
        }

        if (d[t] == 0x3f3f3f3f3f3f3f3f) break;

        rt += f[t];
        co += d[t];
        // cerr << "rt co " << rt << ' ' << co << endl;
        for (int u = t, vv; u != s; u = vv) {
            auto &e = g[u][cfi[u]];
            auto &ei = g[e.v][e.ii];
            vv = e.v;
            e.f += f[t];
            ei.f -= f[t];
        }
    }
    return co;
}



int main() {
    int n; cin >> n;
    vector<int> num;
    vector<tuple<int, int, long long>> seg;
    for (int i = 1; i <= n; ++i) {
        int s, e; long long w; cin >> s >> e >> w;
        ++e;
        num.push_back(s);
        num.push_back(e);
        seg.emplace_back(s, e, w);
    }

    sort(num.begin(), num.end());
    num.resize(unique(num.begin(), num.end()) - num.begin());
    int nn = num.size();

    const long long Z = 1000000000000;

    for (auto &t : seg) {
        get<0>(t) = upper_bound(num.begin(), num.end(), get<0>(t)) - num.begin();
        get<1>(t) = upper_bound(num.begin(), num.end(), get<1>(t)) - num.begin();
        addedge(get<0>(t), get<1>(t), 1, -get<2>(t) + (get<1>(t) - get<0>(t)) * Z);
    }

    addedge(0, 1, 2, Z);
    for (int i = 1; i <= nn; ++i) {
        addedge(i, i + 1, 2, Z);
    }

    long long co = flow(0, nn + 1) - (nn + 1) * Z * 2;

    cout << -co << endl;
}

