#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int x[maxn], y[maxn];
int xv[maxn], yv[maxn], sv[maxn];
bool inq[maxn], w[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = 0; i < n; ++i) {
        xv[i] = i;
        yv[i] = i;
        sv[i] = i;
    }

    sort(xv, xv + n, [&](int i, int j) { return x[i] < x[j]; });
    sort(yv, yv + n, [&](int i, int j) { return y[i] < y[j]; });
    sort(sv, sv + n, [&](int i, int j) { return x[i] + y[i] < x[j] + y[j]; });

    vector<int> ans;

    auto check = [&](int d) {
        int mx = 1, my = 1, cnt = 0;
        int xi = 0, yi = 0, si = 0;

        for (int i = 0; i < n; ++i) {
            inq[i] = false;
            w[i] = false;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> xq;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> yq;

        vector<int> ord;

        while (ord.size() < n) {
            vector<int> v;
            while (xi < n) {
                int u = xv[xi];
                if (inq[u] || w[u]) {
                    ++xi;
                } else if (x[u] <= mx) {
                    xq.emplace(y[u], u);
                    inq[u] = true;
                    ++xi;
                } else {
                    break;
                }
            } 
            while (yi < n) {
                int u = yv[yi];
                if (inq[u] || w[u]) {
                    ++yi;
                } else if (y[u] <= my) {
                    yq.emplace(x[u], u);
                    inq[u] = true;
                    ++yi;
                } else {
                    break;
                }
            } 
            while (si < n) {
                int u = sv[si];
                if (inq[u]) {
                    ++si;
                } else if (max(mx, x[u]) + max(my, y[u]) - mx - my <= d) {
                    v.push_back(u);
                    w[u] = true;
                    ++si;
                } else {
                    break;
                }
            }

            while (!xq.empty()) {
                int u = xq.top().second;
                if (w[u]) {
                    xq.pop();
                } else if (max(mx, x[u]) + max(my, y[u]) - mx - my <= d) {
                    w[u] = true;
                    v.push_back(u);
                    xq.pop();
                } else {
                    break;
                }
            }
            while (!yq.empty()) {
                int u = yq.top().second;
                if (w[u]) {
                    yq.pop();
                } else if (max(mx, x[u]) + max(my, y[u]) - mx - my <= d) {
                    w[u] = true;
                    v.push_back(u);
                    yq.pop();
                } else {
                    break;
                }
            }
            if (v.empty()) return false;
            for (int u : v) {
                ord.push_back(u);
                mx = max(mx, x[u]);
                my = max(my, y[u]);
            }
        }
        ans = ord;
        return true;
    };

    int tans = 2000000000;
    for (int d = 30; d >= 0; --d) {
        if (tans - (1 << d) >= 0 && check(tans - (1 << d))) tans -= (1 << d);
    }
    for (int i = 0; i < n; ++i) printf("%d ", ans[i] + 1);
    puts("");
}
