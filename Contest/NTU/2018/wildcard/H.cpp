#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const long long inf = 1e15;
vector<pair<int, int>> g[maxn];
long long dp[maxn][maxn];
bool v[maxn][maxn];
int n, m, s1, s2, t;

int parse(string s) {
    if (s == "x") return -1;
    stringstream ss(s);
    int res; ss >> res;
    return res;
}

template <typename t>
using heap = priority_queue<t, vector<t>, greater<t>>;

void dijk() {
    memset(v, false, sizeof(v));
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) dp[i][j] = inf;
    }
    heap<pair<long long, pair<int, int>>> pq;
    dp[t][0] = 0;
    pq.emplace(0, make_pair(t, 0));
    while (pq.size()) {
        int x, e; tie(x, e) = pq.top().second; pq.pop();
//        cout << "x = " << x << " e = " << e << endl;
//        if (x == 3 && e == 0) assert(false);
        if (v[x][e]) continue;
        v[x][e] = true;
        for (const auto &p : g[x]) {
            int u = p.first, w = p.second;
            if (w == -1) {
                if (e + 1 < maxn && dp[u][e + 1] > dp[x][e]) {
                    dp[u][e + 1] = dp[x][e];
                    pq.emplace(dp[u][e + 1], make_pair(u, e + 1));
                }
            } else {
                if (dp[u][e] > dp[x][e] + w) {
                    dp[u][e] = dp[x][e] + w;
//                    if (u == 3 && e == 0) assert(false);
                    pq.emplace(dp[u][e], make_pair(u, e));
                }
            }
        }
    }
    /* for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) dp[j][i] = min(dp[j][i], dp[j][i + 1]);
    } */
}

pair<long long, long long> inter(pair<int, long long> a, pair<int, long long> b) {
    long long x = (b.second - a.second) / (a.first - b.first);
    return make_pair(x, x + 1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while (cin >> n >> m >> s1 >> s2 >> t) {
        if (n + m + s1 + s2 + t == 0) break;
        for (int i = 0; i < n; ++i) g[i].clear();
        --s1, --s2, --t;
        for (int i = 0; i < m; ++i) {
            int x, y; string s;
            cin >> x >> y >> s;
            --x, --y;
            int c = parse(s);
  //          cout << "x = " << x << " y = " << y << " c = " << c << endl;
            g[x].emplace_back(y, c);
            g[y].emplace_back(x, c);
        }
        dijk();
        /* for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
        } */
        deque<pair<int, long long>> dq1, dq2;
        for (int i = n - 1; i >= 0; --i) {
            if (dp[s1][i] == inf) continue;
            while (dq1.size() >= 2 && inter(dq1[dq1.size() - 1], dq1[dq1.size() - 2]).first >= inter(dq1[dq1.size() - 1], make_pair(i, dp[s1][i])).first) dq1.pop_back();
            dq1.emplace_back(i, dp[s1][i]);
        }
        for (int i = n - 1; i >= 0; --i) {
            if (dp[s2][i] == inf) continue;
            while (dq2.size() >= 2 && inter(dq2[dq2.size() - 1], dq2[dq2.size() - 2]).first >= inter(dq2[dq2.size() - 1], make_pair(i, dp[s2][i])).first) dq2.pop_back();
            dq2.emplace_back(i, dp[s2][i]);
        }
        vector<long long> query = { 0 };
        for (int i = 0; i < dq1.size(); ++i) {
            for (int j = 0; j < dq2.size(); ++j) {
                if (dq1[i].first == dq2[j].first) continue;
                long long x, y;
                tie(x, y) = inter(dq1[i], dq2[j]);
                query.push_back(x);
                query.push_back(y);
            }
        }
        for (int i = 1; i < dq1.size(); ++i) {
            long long x, y;
            tie(x, y) = inter(dq1[i - 1], dq1[i]);
            query.push_back(x);
            query.push_back(y);
        }
        for (int i = 1; i < dq2.size(); ++i) {
            long long x, y;
            tie(x, y) = inter(dq2[i - 1], dq2[i]);
            query.push_back(x);
            query.push_back(y);
        }
        sort(query.begin(), query.end());
        query.resize(unique(query.begin(), query.end()) - query.begin());
        long long ans = inf;
        for (int i = 0; i < (int)query.size(); ++i) {
            long long x = query[i];
            if (x < 0) continue;
            // printf("x = %lld\n", x);
            while (dq1.size() >= 2 && dq1[0].first * x + dq1[0].second >= dq1[1].first * x + dq1[1].second) dq1.pop_front();
            while (dq2.size() >= 2 && dq2[0].first * x + dq2[0].second >= dq2[1].first * x + dq2[1].second) dq2.pop_front();
            // printf("a = %d b = %lld\n", dq1[0].first, dq1[0].second);
            // printf("a = %d b = %lld\n", dq2[0].first, dq2[0].second);
            // printf("now = %lld\n", abs(dq1[0].first * x + dq1[0].second - dq2[0].first * x - dq2[0].second));
            ans = min(ans, abs(dq1[0].first * x + dq1[0].second - dq2[0].first * x - dq2[0].second));
        }
        cout << ans << '\n';
    }
    return 0;
}
