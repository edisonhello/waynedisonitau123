#include <bits/stdc++.h>
using namespace std;

int w, h, ct[10][3], cp[105][3];
set<pair<int, int>> mt;
bool cango[10][105];

int dx[] = {1, 1, 0, -1, -1, 0};
int dy[] = {0, -1, -1, 0, 1, 1};

bool can_reach(int x, int y, int i) {
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(x, y), 2);
    while (q.size()) {
        auto now = q.front(); q.pop();
        for (int d = 0; d < 6; ++d) {
            int nx = now.first.first + dx[d];
            int ny = now.first.second + dy[d];
            if (ct[i][0] == nx && ct[i][1] == ny) return true;
            if (now.second == 1) continue;
            q.emplace(make_pair(nx, ny), now.second - 1);
        }
    }
    return false;
}

bool check_cango(int i, int j) {
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(cp[j][0], cp[j][1]), cp[j][2] - 1);
    while (q.size()) {
        auto now = q.front(); q.pop();
        for (int d = 0; d < 6; ++d) {
            int nx = now.first.first + dx[d];
            int ny = now.first.second + dy[d];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            if (mt.count(make_pair(nx, ny))) continue;
            if (can_reach(nx, ny, i)) return true;
            if (now.second <= 1) continue;
            q.emplace(make_pair(nx, ny), now.second - 1);
        }
    }
    return false;
}

bool bfs_with_mt(int x, int y, int xx, int yy, int stp) {
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(x, y), stp);
    if (x == xx && y == yy) return true;
    while (q.size()) {
        auto now = q.front(); q.pop();
        if (now.second <= 0) continue;
        for (int d = 0; d < 6; ++d) {
            int nx = now.first.first + dx[d];
            int ny = now.first.second + dy[d];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            if (mt.count(make_pair(nx, ny))) continue;
            if (nx == xx && ny == yy) return true;
            if (now.second <= 1) continue;
            q.emplace(make_pair(nx, ny), now.second - 1);
        }
    }
    return false;
}

bool bfs_without_mt(int x, int y, int xx, int yy, int stp) {
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(x, y), stp);
    if (x == xx && y == yy) return true;
    while (q.size()) {
        auto now = q.front(); q.pop();
        if (now.second <= 0) continue;
        for (int d = 0; d < 6; ++d) {
            int nx = now.first.first + dx[d];
            int ny = now.first.second + dy[d];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            // if (mt.count(make_pair(nx, ny))) continue;
            if (nx == xx && ny == yy) return true;
            if (now.second <= 1) continue;
            q.emplace(make_pair(nx, ny), now.second - 1);
        }
    }
    return false;
}

map<pair<int, int>, pair<int, int>> poss;
void insert_poss(int x, int y, int stp = 2) {
    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(x, y), stp);
    while (q.size()) {
        auto now = q.front(); q.pop();
        poss.insert(make_pair(now.first, make_pair(poss.size() * 2, poss.size() * 2 + 1)));
        if (now.second == 0) continue;
        for (int d = 0; d < 6; ++d) {
            int nx = now.first.first + dx[d];
            int ny = now.first.second + dy[d];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            // if (mt.count(make_pair(nx, ny))) continue;
            // if (nx == xx && ny == yy) return true;
            // if (now.second <= 1) continue;
            q.emplace(make_pair(nx, ny), now.second - 1);
        }
    }
}


void printpos(int id) {
    for (auto p : poss) {
        if (p.second.first == id) {
            cout << p.first.first << " " << p.first.second;
            return;
        }
    }
}

struct dinic {
    static const int maxn = 250;
    struct edge {
        int to, cap, rev;
        edge(int a, int b, int c): to(a), cap(b), rev(c) {}
    };

    vector<edge> g[maxn];
    int qu[maxn], lev[maxn];

    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        int ql = 0, qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (int i = 0; i < (int)g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }

    int dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (int i = 0; i < (int)g[x].size(); ++i) {
            edge &e = g[x][i];
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                int f = dfs(e.to, t, min(flow - res, e.cap));
                e.cap -= f;
                g[e.to][e.rev].cap += f;
                res += f;
            }
        }
        if (res == 0)
            lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int res = 0;
        for (; bfs(s, t); res += dfs(s, t, 1e9));
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> w >> h;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> ct[i][0] >> ct[i][1] >> ct[i][2];
    int c; cin >> c;
    for (int i = 0; i < c; ++i) cin >> cp[i][0] >> cp[i][1] >> cp[i][2];
    for (int i = 0; i < n; ++i) for (int j = 0; j < c; ++j) cango[i][j] = check_cango(i, j);
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        mt.insert(make_pair(x, y));
    }
    for (int i = 0; i < n; ++i) insert_poss(ct[i][0], ct[i][1]);
    int mx = 0, id = 0;
    for (int i = 0; i < (1 << n); ++i) {
        dinic d;
        for (int j = 0; j < c; ++j) d.add_edge(poss.size() * 2 + 0, poss.size() * 2 + j + 1, 1); // source to capa
        for (int j = 0; j < c; ++j) {
            for (auto p : poss) {
                if (bfs_with_mt(cp[j][0], cp[j][1], p.first.first, p.first.second, cp[j][2] - 1)) {
                    d.add_edge(poss.size() * 2 + j + 1, p.second.first, 1);
                }
            }
        }
        for (auto p : poss) d.add_edge(p.second.first, p.second.second, 1);
        int sumhp = 0, cnt = 0;
        for (int j = 0; j < n; ++j) if (i & (1 << j)) {
            for (auto p : poss) {
                if (bfs_without_mt(ct[j][0], ct[j][1], p.first.first, p.first.second, 2)) {
                    d.add_edge(p.second.second, poss.size() * 2 + 1 + c + j, 1);
                }
            }
            d.add_edge(poss.size() * 2 + j + 1 + c, poss.size() * 2 + 1 + c + n, ct[j][2]); // city to bye
            sumhp += ct[j][2];
            ++cnt;
        }
        if (d(poss.size() * 2, 1 + c + n + poss.size() * 2) == sumhp) {
            if (cnt > mx) mx = cnt, id = i;
        }
    }
    cout << mx << endl;
    for (int i = id; i == id; ++i) {
        dinic d;
        for (int j = 0; j < c; ++j) d.add_edge(poss.size() * 2 + 0, poss.size() * 2 + j + 1, 1); // source to capa
        for (int j = 0; j < c; ++j) {
            for (auto p : poss) {
                if (bfs_with_mt(cp[j][0], cp[j][1], p.first.first, p.first.second, cp[j][2] - 1)) {
                    d.add_edge(poss.size() * 2 + j + 1, p.second.first, 1);
                }
            }
        }
        for (auto p : poss) d.add_edge(p.second.first, p.second.second, 1);
        int sumhp = 0, cnt = 0;
        for (int j = 0; j < n; ++j) if (i & (1 << j)) {
            for (auto p : poss) {
                if (bfs_without_mt(ct[j][0], ct[j][1], p.first.first, p.first.second, 2)) {
                    d.add_edge(p.second.second, poss.size() * 2 + 1 + c + j, 1);
                }
            }
            d.add_edge(poss.size() * 2 + j + 1 + c, poss.size() * 2 + 1 + c + n, ct[j][2]); // city to bye
            sumhp += ct[j][2];
            ++cnt;
        }
        d(poss.size() * 2, 1 + c + n + poss.size() * 2);
        for (int k = 0; k < c; ++k) {
            bool out  = false;
            for (auto e : d.g[k + 1 + poss.size() * 2]) {
                if (e.to < poss.size() * 2 && e.cap == 0) {
                    for (auto ee : d.g[e.to + 1]) {
                        if (ee.to >= 1 + c + poss.size() * 2 && ee.cap == 0) {
                            printpos(e.to);
                            cout << " " << ee.to - 1 - c - poss.size() * 2 + 1 << '\n';
                            ee.cap += 1;
                            e.cap += 1;
                            out = true;
                            break;
                        }
                    }
                    if (out) break;
                }
            }
            if (!out) {
                cout << cp[k][0] << ' ' << cp[k][1] << ' ' << 0 << '\n';
            }
        }
    }
}
