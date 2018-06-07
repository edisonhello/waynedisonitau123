namespace SAIS {
    enum type { L, S, LMS };
    const int maxn = 1e5 + 5;
    int bkt[maxn], cnt[maxn], lptr[maxn], rptr[maxn], tptr[maxn];
    int rev[maxn];
    void pre(const vector<int> &s, int sigma) {
        fill(bkt, bkt + s.size(), -1);
        fill(cnt, cnt + sigma, 0);
        for (int i = 0; i < s.size(); ++i) ++cnt[s[i]];
        int last = 0;
        for (int i = 0; i < sigma; ++i) {
            lptr[i] = last;
            last += cnt[i];
            rptr[i] = tptr[i] = last - 1;
        }
    }
    void induce(const vector<int> &s, const vector<type> &v) {
        for (int i = 0; i < s.size(); ++i) if (bkt[i] > 0) {
            if (v[bkt[i] - 1] == L) bkt[lptr[s[bkt[i] - 1]]++] = bkt[i] - 1;
        }
        for (int i = s.size() - 1; i >= 0; --i) if (bkt[i] > 0) {
            if (v[bkt[i] - 1] != L) bkt[rptr[s[bkt[i] - 1]]--] = bkt[i] - 1;
        }
    }
    bool equal(int l, int r, const vector<int> &s, const vector<type> &v) {
        do { if (s[l] != s[r]) return false; ++l, ++r; } while (v[l] != LMS && v[r] != LMS);
        return s[l] == s[r];
    }
    vector<int> radix_sort(const vector<int> &lms, const vector<int> &s, const vector<type> &v, int sigma) {
        pre(s, sigma); 
        for (int i = 0; i < lms.size(); ++i) bkt[tptr[s[lms[i]]]--] = lms[i];
        induce(s, v);
        vector<int> rt(lms.size());
        for (int i = 0; i < lms.size(); ++i) rev[lms[i]] = i;
        int prv = -1, rnk = 0;
        for (int i = 0; i < s.size(); ++i) {
            int x = bkt[i];
            if (v[x] != LMS) continue;
            if (prv == -1) {
                rt[rev[x]] = rnk;
                prv = x;
                continue;
            }
            if (!equal(prv, x, s, v)) ++rnk;
            rt[rev[x]] = rnk;
            prv = x;
        }
        return rt;
    }
    vector<int> counting_sort(const vector<int> &s) {
        vector<int> o(s.size());
        for (int i = 0; i < s.size(); ++i) o[s[i]] = i;
        return o;
    }
    vector<int> reconstruct(const vector<int> &sa, const vector<int> &s, const vector<type> &v) {
        vector<int> pos;
        for (int i = 0; i < s.size(); ++i) if (v[i] == LMS) pos.push_back(i);
        vector<int> rev(sa.size());
        for (int i = 0; i < sa.size(); ++i) rev[i] = pos[sa[i]];
        return rev;
    }
    vector<int> sais(const vector<int> &s, int sigma) {
        vector<type> v(s.size());
        v[s.size() - 1] = S;
        for (int i = s.size() - 2; i >= 0; --i) {
            if (s[i] < s[i + 1] || s[i] == s[i + 1] && v[i + 1] == S) v[i] = S;
            else v[i] = L;
        }
        for (int i = s.size() - 1; i >= 1; --i) {
            if (v[i] == S && v[i - 1] == L) v[i] = LMS;
        }
        vector<int> lms;
        for (int i = 0; i < s.size(); ++i) if (v[i] == LMS) lms.push_back(i);
        vector<int> r = radix_sort(lms, s, v, sigma);
        vector<int> sa;
        if (*max_element(r.begin(), r.end()) == r.size() - 1) sa = counting_sort(r);
        else sa = sais(r, *max_element(r.begin(), r.end()) + 1);
        sa = reconstruct(sa, s, v);
        pre(s, sigma);
        for (int i = sa.size() - 1; i >= 0; --i) bkt[tptr[s[sa[i]]]--] = sa[i];
        induce(s, v);
        return vector<int>(bkt, bkt + s.size());
    }
    vector<int> build(const string &s) {
        vector<int> v(s.size() + 1);
        for (int i = 0; i < s.size(); ++i) v[i] = s[i];
        v[v.size() - 1] = 0;
        vector<int> sa = sais(v, 256);
        return vector<int>(sa.begin() + 1, sa.end());
    }
}

