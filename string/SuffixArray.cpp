int sa[maxn], tmp[2][maxn], c[maxn], hi[maxn], r[maxn];
// sa[i]: sa[i]-th suffix is the i-th lexigraphically smallest suffix.
// hi[i]: longest common prefix of suffix sa[i] and suffix sa[i - 1].
void build(const string &s) {
    int *rnk = tmp[0], *rkn = tmp[1];
    for (int i = 0; i < 256; ++i) c[i] = 0;
    for (int i = 0; i < s.size(); ++i) c[rnk[i] = s[i]]++;
    for (int i = 1; i < 256; ++i) c[i] += c[i - 1];
    for (int i = s.size() - 1; i >= 0; --i) sa[--c[s[i]]] = i;
    int sigma = 256;
    for (int n = 1; n < s.size(); n *= 2) {
        for (int i = 0; i < sigma; ++i) c[i] = 0;
        for (int i = 0; i < s.size(); ++i) c[rnk[i]]++;
        for (int i = 1; i < sigma; ++i) c[i] += c[i - 1];
        int *sa2 = rkn;
        int r = 0;
        for (int i = s.size() - n; i < s.size(); ++i) sa2[r++] = i;
        for (int i = 0; i < s.size(); ++i) {
            if (sa[i] >= n) sa2[r++] = sa[i] - n;
        }
        for (int i = s.size() - 1; i >= 0; --i) sa[--c[rnk[sa2[i]]]] = sa2[i];
        rkn[sa[0]] = r = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (!(rnk[sa[i - 1]] == rnk[sa[i]] && sa[i - 1] + n < s.size() && rnk[sa[i - 1] + n] == rnk[sa[i] + n])) r++;
            rkn[sa[i]] = r;
        }
        swap(rnk, rkn);
        if (r == s.size() - 1) break;
        sigma = r + 1;
    }
    for (int i = 0; i < s.size(); ++i) r[sa[i]] = i;
    int ind = 0; hi[0] = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!r[i]) { ind = 0; continue; }
        while (i + ind < s.size() && s[i + ind] == s[sa[r[i] - 1] + ind]) ++ind;
        hi[r[i]] = ind ? ind-- : 0;
    }
}
