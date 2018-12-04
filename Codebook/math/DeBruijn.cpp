int res[maxn], aux[maxn], a[maxn], sz;

void db(int t, int p, int n, int k) {
    if (sz >= tg) return;
    if (t > n) {
        if (n % p == 0) {
            for (int i = 1; i <= p && sz < tg; ++i) res[sz++] = aux[i];
        }
    } else {
        aux[t] = aux[t - p];
        db(t + 1, p, n, k);
        for (int i = aux[t - p] + 1; i < k; ++i) {
            aux[t] = i;
            db(t + 1, t, n, k);
        }
    }
}

int de_bruijn(int k, int n) {
    // return cyclic string of length k^n such that every string of length n using k character appears as a substring.
    if (k == 1) {
        res[0] = 0;
        return 1;
    }
    for (int i = 0; i < k * n; i++) aux[i] = 0;
    sz = 0;
    db(1, 1, n, k);
    return sz;
}
