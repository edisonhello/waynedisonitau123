struct segment {
    int i, l, r;
    segment() {}
    segment(int a, int b, int c): i(a), l(b), r(c) {}
};

inline long long f(int l, int r) {
    return dp[l] + w(l + 1, r); 
}

void solve() {
    dp[0] = 0ll;
    deque<segment> deq; deq.push_back(segment(0, 1, n));
    for (int i = 1; i <= n; ++i) {
        dp[i] = f(deq.front().i, i);
        while (deq.size() && deq.front().r < i + 1) deq.pop_front();
        deq.front().l = i + 1;
        segment seg = segment(i, i + 1, n);
        while (deq.size() && df(i, deq.back().l) < df(deq.back().i, deq.back().l)) deq.pop_back();
        if (deq.size()) {
            int d = 1048576, c = deq.back().l;
            while (d >>= 1) if (c + d <= deq.back().r) {
                if (df(i, c + d) > df(deq.back().i, c + d)) c += d;
            }
            deq.back().r = c; seg.l = c + 1;
        }
        if (seg.l <= n) deq.push_back(seg);
    }
}
