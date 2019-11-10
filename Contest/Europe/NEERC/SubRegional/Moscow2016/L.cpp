#include <bits/stdc++.h>
using namespace std;

const int kN = 1e6 + 5;

int main() {
    int n; scanf("%d", &n);
    vector<pair<int, int>> v;
    for (int i = 0; i < n + n; ++i) {
        char s[2]; 
        int t;
        scanf("%s%d", s, &t);
        if (s[0] == '+') v.emplace_back(t, 1);
        else v.emplace_back(t, -1);
    }

    auto Sign = [](int x) {
        if (x == 0) return 0;
        if (x > 0) return 1;
        return -1;
    };

    auto Solve = [&](int l, int r) {
        int sgn = 1, z = l;
        vector<int> a, c;
        vector<double> t;
        for (int i = l; i <= r; ++i) {
            if (Sign(v[i].second) != sgn) {
                if (sgn == 1) {
                    a.push_back(i - z);
                } else {
                    c.push_back(i - z);
                    double sum = 0;
                    for (int j = z; j < i; ++j) sum += v[j].first;
                    t.push_back(sum / (i - z));
                }
                z = i;
            }
            sgn = Sign(v[i].second);
        }
        assert(sgn == -1);
        c.push_back(r + 1 - z);
        double sum = 0;
        for (int j = z; j <= r; ++j) sum += v[j].first;
        t.push_back(sum / (r + 1 - z));
        assert(a.size() == c.size());

        vector<double> ans(a.size());
        int pf = accumulate(a.begin(), a.end(), 0);
        int cf = accumulate(c.begin(), c.end(), 0);
        for (int i = a.size() - 1; i >= 0; --i) {
            if (i == a.size() - 1) {
                ans[i] = t[i];
            } else {
                double x = pf - cf + c[i]; 
                double p = c[i] / x;
                ans[i] = t[i] * p;
                ans[i] += (1 - p) * ans[i + 1];
            }
            pf -= a[i];
            cf -= c[i];
        }
        for (int i = l, j = 0, k = 0; i <= r; ++i) {
            if (v[i].second == 1) {
                printf("%.20lf\n", ans[j] - v[i].first);
                if (++k == a[j]) ++j, k = 0;
            }
        }
    };

    for (int i = 0, s = 0, j = 0; i < n + n; ++i) {
        s += v[i].second;
        if (s == 0) {
            Solve(j, i);
            j = i + 1;
        }
    }
    return 0;
}
