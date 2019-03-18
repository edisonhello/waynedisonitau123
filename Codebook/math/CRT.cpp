long long crt(vector<int> mod, vector<int> a) {
    long long mult = mod[0];
    int n = (int)mod.size();
    long long res = a[0];
    for (int i = 1; i < n; ++i) {
        long long d, x, y; 
        tie(d, x, y) = extgcd(mult, mod[i] * 1ll);
        if ((a[i] - res) % d) return -1;
        long long new_mult = mult / __gcd(mult, 1ll * mod[i]) * mod[i]; 
        res += x * ((a[i] - res) / d) % new_mult * mult % new_mult;
        mult = new_mult;
        ((res %= mult) += mult) %= mult;
    }
    return res;
}
