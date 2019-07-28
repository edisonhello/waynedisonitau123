#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int p, t[maxn], a[maxn], inv[maxn];

struct Polynomial {
    vector<int> coeff;

    Polynomial() = default;

    Polynomial(vector<int> &&v) : coeff(move(v)) {}

    int eval(int x) const {
        int res = 0, xp = 1;
        for (int i = 0; i < (int)coeff.size(); ++i) {
            (res += coeff[i] * xp % p) %= p;
            (xp *= x) %= p;
        }
        return res;
    }

    Polynomial derive() const {
        if (coeff.size() == 1) return Polynomial({0});
        vector<int> res((int)coeff.size() - 1, 0);
        for (int i = 1; i < (int)coeff.size(); ++i) {
            res[i - 1] = i * coeff[i] % p;
        }
        return res;
    }
};

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) (res *= a) %= p;
        (a *= a) %= p;
        n >>= 1;
    }
    return res;
}

int main() {
    freopen("system.in", "r", stdin);
    freopen("system.out", "w", stdout);

    int n; scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
    for (int i = 0; i < p; ++i) inv[i] = fpow(i, p - 2);
    for (int i = 0; i < n; ++i) {
        a[i] = 0;
        for (int j = 0; j < i; ++j) {
            a[i] += (p - t[j]) * a[i - j - 1] % p;
            a[i] %= p;
        }
        (a[i] += p - t[i]) %= p;
        a[i] = a[i] * inv[i + 1] % p;
    }

    vector<int> coeff(n + 1, 1);
    for (int i = 0; i < n; ++i) coeff[i] = a[n - i - 1];
    Polynomial poly(move(coeff));

    vector<int> roots(p);
    iota(roots.begin(), roots.end(), 0);

    vector<int> ans;

    while (!roots.empty()) {
        vector<int> troots;
        for (int i = 0; i < (int)roots.size(); ++i) {
            if (poly.eval(roots[i]) == 0) {
                ans.push_back(roots[i]);
                troots.push_back(roots[i]);
            }
        }
        poly = poly.derive();
        roots = troots;
    }

    if ((int)ans.size() != n) {
        puts("NO");
    } else {
        puts("YES");
        sort(ans.begin(), ans.end());
        for (int i = 0; i < n; ++i) printf("%d ", ans[i]);
    }

    return 0;
}
