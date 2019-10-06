int QuadraticResidue(int a, int p) {
    int z = (p - 1) >> 1;
    if (fpow(a, z, p) != 1) return -1;
    int b = -1;
    for (b = 2; ; ++b) {
        if (fpow(b, z, p) != 1) break;
    }
    int iv = fpow(a, p - 2, p), t = 0;
    while ((p - 1) % (1 << t) == 0) ++t;
    t--;
    int s = (p - 1) / (1 << t);
    int x = fpow(a, (s + 1) >> 1, p);
    int w = fpow(a, s, p);
    int k = 1;
    while (k < t) {
        if (fpow(w, (1 << (t - k - 1)), p) != 1) {
            x = 1LL * x * fpow(b, (1 << k) * s, p) % p;
            w = 1LL * iv * fpow(x, 2, p) % p;
        }
        ++k;
    }
    return x;
}
