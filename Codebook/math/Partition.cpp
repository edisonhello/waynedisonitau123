void Build(int n) {
    // P[i] = the number of ways to represent i as the sum of a non-decreasing sequence.
    vector<pair<int, int>> g = {{0, 0}};
    for (int i = 1; g.back().second <= n; ++i) {
        g.emplace_back(i % 2 ? 1 : kMod - 1, i * (3 * i - 1) / 2);
        g.emplace_back(i % 2 ? 1 : kMod - 1, i * (3 * i + 1) / 2);
    }
    P[0] = P[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (auto it : g) {
            if (i < it.second) continue;
            (P[i] += 1LL * P[i - it.second] * it.first % kMod) %= kMod;
        }
    }
}
