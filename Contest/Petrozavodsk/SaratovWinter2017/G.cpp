#include <bits/stdc++.h>
using namespace std;
#define double long double

const int maxn = 2000 + 5;
const double eps = 1e-12;
vector<pair<int, double>> g[maxn];
string s[maxn];
int o[maxn], a[maxn], b[maxn], d[maxn], upd[maxn];
double dd[maxn];
bool inq[maxn], used[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m; 
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
            if (s[i] == "?") {
                used[i] = false;
                continue;
            }
            used[i] = true;
            stringstream ss; ss << s[i];
            ss >> o[i];
        }

        for (int i = 0; i < m; ++i)
            cin >> a[i] >> b[i] >> d[i];

        auto add_edge = [&](int u, int v, double d) {
            g[u].emplace_back(v, d);
        };

        auto check = [&](double t) {
            // cout << "check " << t << endl;
            for (int i = 0; i <= n; ++i) g[i].clear();

            for (int i = 0; i < m; ++i) {
                add_edge(a[i] - 1, b[i] - 1, d[i] - t);
            }

            for (int i = 0; i < n; ++i) {
                inq[i] = false;
                upd[i] = 0;
                if (!used[i]) dd[i] = -1e8;
                else dd[i] = o[i];
            }

            queue<int> q;
            for (int i = 0; i < n; ++i) {
                inq[i] = true;
                q.push(i);
            }

            while (!q.empty()) {
                int x = q.front(); q.pop();
                inq[x] = false;

                for (int i = 0; i < (int)g[x].size(); ++i) {
                    int u = g[x][i].first;
                    double w = g[x][i].second;
                    if (dd[u] + eps < dd[x] + w) {
                        // printf("x = %d u = %d w = %d\n", x, u, w);
                        dd[u] = dd[x] + w;
                        if (++upd[u] > n + 1)
                            return false;

                        if (!inq[u]) {
                            inq[u] = true;
                            q.push(u);
                        }
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                if (used[i]) {
                    if (fabs(dd[i] - o[i]) > eps)
                        return false;
                }
            }

            return true;
        };

        double l = 0.0, r = 3000 * 100000;
        for (int it = 0; it < 100; ++it) {
            double m = 0.5 * (l + r);
            if (check(m)) r = m;
            else l = m;
        }
        cout << fixed << setprecision(20) << l << endl;
        check(l);

        for (int i = 0; i < m; ++i) {
            // cerr << fixed << ^setprecision(20) << dd[a[i]] + d[i] << ' ' << dd[b[i]] + l << endl;
            assert(dd[a[i] - 1] + d[i] <= dd[b[i] - 1] + l + 1e-4);
        }

        for (int i = 0; i < n; ++i)
            cout << fixed << setprecision(20) << dd[i] << ' ';
        cout << endl;
        // cout << "done" << endl;

    }
    return 0;
}
