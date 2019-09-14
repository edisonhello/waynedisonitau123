#include <bits/stdc++.h>
#define double long double
using namespace std;

const double eps = 1e-9;

void gauss(vector<vector<double>> &d, vector<double> &res) {
    int n = (int)d.size(), m = (int)d[0].size();
    for (int i = 0; i < m; ++i) {
        int p = -1;
        for (int j = i; j < n; ++j) {
            if (fabs(d[j][i]) < eps) continue;
            if (p == -1 || fabs(d[j][i]) > fabs(d[p][i])) p = j;
        }
        if (p == -1) continue;
        for (int j = 0; j < m; ++j) swap(d[p][j], d[i][j]);
        swap(res[p], res[i]);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            double z = d[j][i] / d[i][i];
            for (int k = 0; k < m; ++k) d[j][k] -= z * d[i][k];
            res[j] -= z * res[i];
        }
    }
}

const int maxn = 100 + 5;
int d[maxn][maxn], q[maxn], ss[maxn][maxn], w[maxn][maxn];

int main() {
    int n, s, t; scanf("%d%d%d", &n, &s, &t);
    if (n == 1) {
        printf("0.00000000000\n");
        return 0;
    }
    --s, --t;
    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &w[i][j]);
            d[i][j] = w[i][j];
            if (d[i][j] == 0) d[i][j] = 1e9;
        }
        d[i][i] = 0;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }

    if (d[s][t] > 1e8) {
        puts("impossible");
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (w[i][j] > 0 && d[s][i] + w[i][j] + d[j][t] == d[s][t]) ss[i][j] = true;
        }
    }

    vector<vector<double>> coeff(n, vector<double>(n, 0.0));
    vector<double> res(n, 0.0);
    coeff[t][t] = 1;
    res[t] = 0;

    for (int i = 0; i < n; ++i) {
        if (i == t) continue;
        if (q[i]) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (ss[i][j]) ++cnt;
            }
            if (cnt == 0) {
                coeff[i][i] = 1.0;
                continue;
            }
            double prob = 1.0 / cnt;
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (ss[i][j]) coeff[i][j] += prob, res[i] -= prob * w[i][j];
            }
            coeff[i][i] -= 1;
        } else {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (w[i][j] > 0) ++cnt;
            }
            if (cnt == 0) {
                coeff[i][i] = 1.0;
                continue;
            }
            double prob = 1.0 / cnt;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (w[i][j] > 0) coeff[i][j] += prob, res[i] -= prob * w[i][j];
            }
            if (w[i][i] > 0) {
                coeff[i][i] = prob - 1;
                res[i] -= w[i][i] * prob;
            } else {
                coeff[i][i] = -1;
            }
        }
    }

    gauss(coeff, res);
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) sum += x[j] * coeff[i][j];
        if (fabs(coeff[i][i]) > eps) x[i] = (res[i] - sum) / coeff[i][i];
    }
    printf("%.20Lf\n", x[s]);
}
