struct SuffixArray {
    int sa[maxn], tmp[2][maxn], c[maxn], _lcp[maxn], r[maxn], n;
    string s;
    SparseTable st;
    void suffixarray() {
         int* rank = tmp[0];
        int* nRank = tmp[1];
        int A = 128;
        for (int i = 0; i < A; ++i) c[i] = 0;
        for (int i = 0; i < s.length(); ++i) c[rank[i] = s[i]]++;
        for (int i = 1; i < A; ++i) c[i] += c[i - 1];
        for (int i = s.length() - 1; i >= 0; --i) sa[--c[s[i]]] = i;
        for (int n = 1; n < s.length(); n *= 2) {
            for (int i = 0; i < A; ++i) c[i] = 0;
            for (int i = 0; i < s.length(); ++i) c[rank[i]]++;
            for (int i = 1; i < A; ++i) c[i] += c[i - 1];
            int* sa2 = nRank;
            int r = 0;
            for (int i = s.length() - n; i < s.length(); ++i) sa2[r++] = i;
            for (int i = 0; i < s.length(); ++i) if (sa[i] >= n) sa2[r++] = sa[i] - n;
            for (int i = s.length() - 1; i >= 0; --i) sa[--c[rank[sa2[i]]]] = sa2[i];
            nRank[sa[0]] = r = 0;
            for (int i = 1; i < s.length(); ++i) {
                if (!(rank[sa[i - 1]] == rank[sa[i]] && sa[i - 1] + n < s.length() && rank[sa[i - 1] + n] == rank[sa[i] + n])) r++;
                nRank[sa[i]] = r;
            }
            swap(rank, nRank);
            if (r == s.length() - 1) break;
            A = r + 1;
        }
    }
    void solve() {
        suffixarray();
        for (int i = 0; i < n; ++i) r[sa[i]] = i;
        int ind = 0; _lcp[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (!r[i]) { ind = 0; continue; }
            while (i + ind < n && s[i + ind] == s[sa[r[i] - 1] + ind]) ++ind;
            _lcp[r[i]] = ind ? ind-- : 0;
        }
        st = SparseTable(n, _lcp);
    }
    int lcp(int L, int R) {
        if (L == R) return n - L - 1;
        L = r[L]; R = r[R];
        if (L > R) swap(L, R);
        ++L;
        return st.query(L, R);
    }
    SuffixArray(string s): s(s), n(s.length()) {}
    SuffixArray() {}
};
