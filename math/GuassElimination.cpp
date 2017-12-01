double dat[maxn][maxn];

void guass(int n) {
    for (int i = 0; i < n; ++i) {
        bool ok = false;
        for (int j = i; j < n; ++j) {
            if (fabs(dat[i][j]) > eps) {
                swap(dat[i], dat[j]);
                ok = true;
                break;
            }
        }
        if (!ok) continue;
        double f = dat[i][i];
        for (int j = i + 1; j < n; ++j) {
            double r = dat[j][i] / f;
            for (int k = i; k < n; ++k) dat[j][k] -= dat[i][k] * r;
        }
    }
}
