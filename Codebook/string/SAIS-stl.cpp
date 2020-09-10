// sa[i]: sa[i]-th suffix is the i-th lexigraphically smallest suffix.
// lcp[i]: longest common prefix of suffix sa[i] and suffix sa[i - 1].
namespace sfx {
vector<int> Build(const string &s) {
    int n = s.size();
    vector<int> str(n * 2), sa(n * 2), c(max(n, 256) * 2), x(max(n, 256)), p(n), q(n * 2), t(n * 2);
    for (int i = 0; i < n; ++i) str[i] = s[i];
    auto Pre = [&](int *sa, int *c, int n, int z) {
        memset(sa, 0, sizeof(int) * n);
        memcpy(x.data(), c, sizeof(int) * z);
    };
    auto Induce = [&](int *sa, int *c, int *s, int *t, int n, int z) {
        memcpy(x.data() + 1, c, sizeof(int) * (z - 1));
        for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
        memcpy(x.data(), c, sizeof(int) * z);
        for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
    };
    auto SAIS = [&](auto self, int *s, int *sa, int *p, int *q, int *t, int *c, int n, int z) -> void {
        bool uniq = t[n - 1] = true;
        int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
        memset(c, 0, sizeof(int) * z);
        for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
        for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
        if (uniq) {
            for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
            return;
        }
        for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
        Pre(sa, c, n, z);
        for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
        Induce(sa, c, s, t, n, z);
        for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
            bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
            ns[q[last = sa[i]]] = nmxz += neq;
        }
        self(self, ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
        Pre(sa, c, n, z);
        for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
        Induce(sa, c, s, t, n, z);
    };
    SAIS(SAIS, str.data(), sa.data(), p.data(), q.data(), t.data(), c.data(), n + 1, 256);
    return vector<int>(sa.begin() + 1, sa.begin() + n + 1);
}
vector<int> BuildLCP(const vector<int> &sa, const string &s) {
    int n = s.size();
    vector<int> lcp(n), rev(n);
    for (int i = 0; i < n; ++i) rev[sa[i]] = i;
    for (int i = 0, ptr = 0; i < n; ++i) {
        if (!rev[i]) {
            ptr = 0;
            continue;
        }
        while (i + ptr < n && s[i + ptr] == s[sa[rev[i] - 1] + ptr]) ptr++;
        lcp[rev[i]] = ptr ? ptr-- : 0;
    }
    return lcp;
}}  // namespace sfx
