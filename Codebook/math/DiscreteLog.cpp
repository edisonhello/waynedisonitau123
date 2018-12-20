long long bsgs(long long a, long long b, long long p) {
    // return L such that a^L = b (mod p)
    // p must be prime number
	if (p % a == 0) return -1;
	long long m = ceil(sqrt(p));
	long long l = b;
    map<long long, int> mp;
	mp[l] = 1;
	for (int i = 1; i <= m; i++) {
		(l *= a) %= p;
		mp[l] = i + 1;
	}
	l = fpow(a, m, p);
    long long r = l;
	for (int i = 1; i <= m; i++) {
		if (mp.find(r) != mp.end()) {
		    long long ans = i * m - mp[r] + 1;
			return ans;
		}
		(r *= l) %= p;
	}
	return -1;
}
