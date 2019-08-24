#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> inc;
const int inf = 1e9 + 5;
const int maxn = 100 + 5;

struct MinCost {
    struct Edge {
        int to, cap, w, rev;
        Edge(int a, int b, int c, int d) : to(a), cap(b), w(c), rev(d) {}
    };

    vector<Edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];

    void AddEdge(int a, int b, int c, int d) {
        g[a].emplace_back(b, c, +d, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, -d, (int)g[a].size() - 1);
    }

    bool Spfa(int s, int t, int &f, int &c) {
        for (int i = 0; i < maxn; ++i) {
            d[i] = inf;
            p[i] = ed[i] = -1;
            inq[i] = false;
        }

        d[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int x = q.front(); q.pop();
            inq[x] = false;
            for (int i = 0; i < (int)g[x].size(); ++i) {
                Edge &e = g[x][i];
                if (e.cap > 0 && d[e.to] > d[x] + e.w) {
                    d[e.to] = d[x] + e.w;
                    p[e.to] = x;
                    ed[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        if (d[t] == inf) return false;
        int dlt = inf;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            Edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.to][e.rev].cap += dlt;
        }
        inc.emplace_back(dlt, d[t]);
        f += dlt;
        c += d[t] * dlt;
        return true;
    }

    pair<int, int> operator()(int s, int t) {
        int f = 0, c = 0;
        while (Spfa(s, t, f, c));
        return make_pair(f, c);
    }
} flow;

struct Fraction {
    Fraction() = default;
    long long x, y; // (x / y)
    Fraction(long long x, long long y) : x(x), y(y) { reduce(); };
    Fraction(long long x) : x(x), y(1) {};
    void reduce() {
        assert(x >= 0 && y > 0);
        long long g = __gcd(x, y);
        x /= g, y /= g;
    }
    Fraction operator*(long long d) { return Fraction(x * d, y); }
    Fraction operator*(const Fraction &rhs) const { 
        return Fraction(x * rhs.x, y * rhs.y); 
    }
    Fraction operator/(const Fraction &rhs) const { return Fraction(x * rhs.y, y * rhs.x); }
    Fraction operator+(const Fraction &rhs) const { 
        long long d = y * rhs.y / __gcd(y, rhs.y);
        return Fraction(x * (d / y) + rhs.x * (d / rhs.y), d);
    }
    Fraction operator-(const Fraction &rhs) const  { 
        long long d = y * rhs.y / __gcd(y, rhs.y);
        return Fraction(x * (d / y) - rhs.x * (d / rhs.y), d);
    }

    bool operator<(const Fraction &rhs) const {
        return (long double)x / (long double)y < (long double)rhs.x / (long double)rhs.y;
    }
};

__int128 gcd(__int128 x, __int128 y) {
    return y == 0 ? x : gcd(y, x % y);
}

void output(__int128 x) {
    if (x == 0) {
        cout << "0";
        return;
    }
    vector<int> d;
    while (x > 0) {
        d.push_back(x % 10);
        x /= 10;
    }
    while (d.size()) {
        cout << d.back();
        d.pop_back();
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int s, t; scanf("%d%d", &s, &t);
    --s, --t;

    for (int i = 0; i < m; ++i) {
        int a, b, u, c; scanf("%d%d%d%d", &a, &b, &u, &c);
        --a, --b;
        flow.AddEdge(a, b, u, c);
    }
    
    int M, _; tie(M, _) = flow(s, t);
    if (M == 0) {
        printf("0/1\n");
        return 0;
    }
    // printf("M = %d\n", M);
    int prv = 0, cost = 0;
    long double ans = 1e18;
    __int128 p = -1, q = -1, ll = -1, iii = -1, cc = -1;
    for (int i = 0; i < (int)inc.size(); ++i) {
        // printf("(%d, %d)\n", inc[i].first, inc[i].second);
        long long left = prv, right = prv + inc[i].first;
        long long ii = inc[i].second;
        long long rhs = M + ii * ii * left - ii * cost;
        long long lhs = ii * ii + 1;
        if (rhs >= lhs * left && rhs <= lhs * right) {
            long double x = (long double)rhs / (long double)lhs;
            long double B = (cost + (x - left) * ii) * (cost + (x - left) * ii) + (M - x) * (M - x);
            if (B < ans) {
                ans = B;
                p = rhs;
                q = lhs;
                ll = left;
                iii = ii;
                cc = cost;
            }
        }
        {

            long double x = left;
            long double B = (cost + (x - left) * ii) * (cost + (x - left) * ii) + (M - x) * (M - x);
            if (B < ans) {
                ans = B;
                p = left;
                q = 1;
                ll = left;
                iii = ii;
                cc = cost;
            }
        }
        {
            long double x = right;
            long double B = (cost + (x - left) * ii) * (cost + (x - left) * ii) + (M - x) * (M - x);
            if (B < ans) {
                ans = B;
                p = right;
                q = 1;
                ll = left;
                iii = ii;
                cc = cost;
            }
        }
        cost += inc[i].second * inc[i].first;
        prv += inc[i].first;
    }
    __int128 g = gcd(p, q);
    p /= g, q /= g;
    __int128 x = -2 * M * p * q + M * M * q * q + p * p + p * p * iii * iii + ll * ll * iii * iii * q * q + cc * cc * q * q + 2 * p * iii * cc * q - 2 * iii * ll * cc * q * q - 2 *iii * p * iii * ll * q;
    __int128 y = q * q;
    g = gcd(x, y);
    x /= g, y /= g;
    output(x);
    cout << "/";
    output(y);
    cout << endl;
}
