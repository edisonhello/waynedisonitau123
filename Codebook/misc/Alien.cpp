long long Alien() {
  long long c = kInf;
  for (int d = 60; d >= 0; --d) {
    // cost can be negative as well, depending on the problem.
    if (c - (1LL << d) < 0) continue;
    long long ck = c - (1LL << d);
    pair<long long, int> r = check(ck);
    if (r.second == k) return r.first - ck * k;
    if (r.second < k) c = ck;
  }
  pair<long long, int> r = check(c);
  return r.first - c * k;
}
