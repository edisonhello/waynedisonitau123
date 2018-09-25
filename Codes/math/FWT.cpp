void xorfwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    xorfwt(v, l, m), xorfwt(v, m, r);
    for (int i = l, j = m; i < m; ++i, ++j) {
        int x = v[i] + v[j];
        v[j] = v[i] - v[j], v[i] = x;
    }
}

void xorifwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    for (int i = l, j = m; i < m; ++i, ++j) {
        int x = (v[i] + v[j]) / 2;
        v[j] = (v[i] - v[j]) / 2, v[i] = x;
    }
    xorifwt(v, l, m), xorifwt(v, m, r);
}

void andfwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    andfwt(v, l, m), andfwt(v, m, r);
    for (int i = l, j = m; i < m; ++i, ++j) v[i] += v[j];
}

void andifwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    andifwt(v, l, m), andifwt(v, m, r);
    for (int i = l, j = m; i < m; ++i, ++j) v[i] -= v[j];
}

void orfwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    orfwt(v, l, m), orfwt(v, m, r);
    for (int i = l, j = m; i < m; ++i, ++j) v[j] += v[i];
}

void orifwt(int v[], int l, int r) {
    if (r - l == 1) return;
    int m = l + r >> 1;
    orifwt(v, l, m), orifwt(v, m, r);
    for (int i = l, j = m; i < m; ++i, ++j) v[j] -= v[i];
}
