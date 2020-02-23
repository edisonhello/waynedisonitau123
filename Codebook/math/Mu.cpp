int mu[kC], dv[kC];
vector<int> prime;
void Sieve() {
    mu[1] = dv[1] = 1;
    for (int i = 2; i < kC; ++i) {
        if (!dv[i]) {
            dv[i] = i, mu[i] = -1;
            prime.push_back(i);
        }
        for (int j = 0; i * prime[j] < kC; ++j) {
            dv[i * prime[j]] = prime[j];
            mu[i * prime[j]] = -mu[i];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
