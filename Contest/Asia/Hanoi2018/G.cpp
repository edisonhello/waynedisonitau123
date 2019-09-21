#include <bits/stdc++.h>
using namespace std;

long long f[100];
const long long inf = 1000000000000000000LL;
vector<pair<int, int>> g[100];

long long dp[100];
int d[100];
bool v[100];

bool check(int n, const vector<tuple<int, int, int>> &edge, long long A) {
    for (int i = 0; i < n; ++i) g[i].clear();
    for (auto &e : edge) {
        g[get<0>(e)].emplace_back(get<1>(e), get<2>(e));
        g[get<1>(e)].emplace_back(get<0>(e), get<2>(e));
    }
    for (int i = 0; i < n; ++i) d[i] = 1e9;
    memset(v, false, sizeof(v));
    memset(dp, 0, sizeof(dp));
    d[0] = 0;
    dp[0] = 1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        int x = pq.top().second;
        pq.pop();
        if (v[x]) continue;
        v[x] = true;
        for (auto &e : g[x]) {
            int u = e.first, w = e.second;
            if (d[u] > d[x] + w) {
                d[u] = d[x] + w;
                dp[u] = dp[x];
                pq.emplace(d[u], u);
            } else if (d[u] == d[x] + w) {
                dp[u] += dp[x];
            }
        }
    }
    cout << "dp[1] = " << dp[1] << " A = " << A << endl;
    return dp[1] == A;
}

void case1(long long A) {
    vector<tuple<int, int, int>> edge;
    vector<int> v(62);
    for (int i = 0; i < 62; ++i) v[i] = i;
    swap(v[1], v[61]);
    long long B = A;
    for (int i = 0; i < 62; ++i) {
        for (int j = i + 1; j < 62; ++j) {
            // if (i == 0 && j == 61) cout << "jizz" << endl;
            if (i == 0) {
                if (j < 61 && (A >> (60 - j) & 1LL)) {
                    A -= (1LL << (60 - j));
                    edge.emplace_back(v[i], v[j], j - i);
                } 
            } else {
                edge.emplace_back(v[i], v[j], j - i);
            }
        }
    }
    cout << "YES" << endl;
    cout << 62 << ' ' << (int)edge.size() << endl;
    for (auto &e : edge) {
        cout << get<0>(e) + 1 << ' ' << get<1>(e) + 1 << ' ' << get<2>(e) << endl;
    }
    // assert(check(62, edge, B));
}

void case2(long long A) {
    vector<tuple<int, int, int>> edge;
    vector<int> v(88);
    for (int i = 0; i < 88; ++i) v[i] = i;
    swap(v[1], v[87]);
    for (int i = 1; i < 88; ++i) {
        if (i + 1 < 88) {
            edge.emplace_back(v[i], v[i + 1], 1);
        } 
        if (i + 2 < 88) {
            edge.emplace_back(v[i], v[i + 2], 2);
        }
    }
    long long B = A;
    for (int i = 87; i >= 1; --i) {
        if (A >= f[i]) {
            edge.emplace_back(v[0], v[88 - i], 88 - i);
            A -= f[i];
        }
    }
    
    cout << "YES" << endl;
    cout << 88 << ' ' << (int)edge.size() << endl;
    for (auto &e : edge) {
        cout << get<0>(e) + 1 << ' ' << get<1>(e) + 1 << ' ' << get<2>(e) << endl;
    }
    // assert(check(88, edge, B));
}

int main() {
    f[0] = 0, f[1] = 1;
    for (int i = 2; i < 100; ++i) f[i] = f[i - 1] + f[i - 2];
    long long A;
    while (cin >> A) {
        if (A == -1) break;
        case1(A);
        case2(A);
    }
}


