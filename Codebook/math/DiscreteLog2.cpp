int bsgs(int a, int b, int p) {
    // return L such that a^L = b (mod p)
    if (p == 1) {
        if (!b) return a != 1;
        return -1;
    }
    if (b == 1) {
        if (a) return 0;
        return -1;
    }
    if (a % p == 0) {
        if (!b) return 1;
        return -1;
    }
    int num = 0, d = 1;
    while (true) {
        int r = __gcd(a, p);
        if (r == 1) break;
        if (b % r) return -1;
        ++num;
        b /= r, p /= r;
        d = (1ll * d * a / r) % p;
    }
    for (int i = 0, now = 1; i < num; ++i, now = 1ll * now * a % p) {
        if (now == b) return i;
    }
    int m = ceil(sqrt(p)), base = 1;
    map<int, int> mp;
    for (int i = 0; i < m; ++i) {
        if (mp.find(base) == mp.end()) mp[base] = i;
        else mp[base] = min(mp[base], i);
        base = 1ll * base * a % p;
    }
    for (int i = 0; i < m; ++i) {
        // can be modified to fpow if p is prime
        int r, x, y; tie(r, x, y) = extgcd(d, p, x, y);
        x = (1ll * x * b % p + p) % p;
        if (mp.find(x) != mp.end()) return i * m + mp[x] + num;
        d = 1ll * d * base % p;
    }
    return -1;
}
