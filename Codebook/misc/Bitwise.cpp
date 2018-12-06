long long next_perm(long long v) {
	long long t = v | (v - 1);
	return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}

void subset(long long s) {
    long long sub = s;
    while (sub) {
        // do things
        sub = (sub - 1) & s;
    }
}
