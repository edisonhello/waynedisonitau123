#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005 * 2;

namespace sfxarray {
    bool t[maxn * 2];
    int hi[maxn], rev[maxn];
    int _s[maxn * 2], sa[maxn * 2], c[maxn * 2], x[maxn], p[maxn], q[maxn * 2];

    void pre(int *sa, int *c, int n, int z) {
        memset(sa, 0, n << 2);
        memcpy(x, c, z << 2);
    }
    void induce(int *sa, int *c, int *s, bool *t, int n, int z) {
        memcpy(x + 1, c, (z - 1) << 2);
        for (int i = 0 ; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
        memcpy(x, c, z << 2);
        for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
    }

    void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
        bool uniq = t[n - 1] = true;
        int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
        memset(c, 0, z << 2);
        for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
        for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
        if (uniq) {
            for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
            return;
        }
        for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
        pre(sa, c, n, z);
        for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1] ) sa[--x[s[i]]] = p[q[i] = nn++] = i;
        induce(sa, c, s, t, n, z);
        for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
            bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) << 2);
            ns[q[last = sa[i]]] = nmxz += neq;
        }
        sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
        pre(sa, c, n, z);
        for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
        induce(sa, c, s, t, n, z);
    }
    void build(const string &s) {
        for (int i = 0; i < (int)s.size(); ++i) _s[i] = s[i];
        _s[(int)s.size()] = 0;
        sais(_s, sa, p, q, t, c, (int)s.size() + 1, 256);
        for (int i = 0; i < (int)s.size(); ++i) sa[i] = sa[i + 1];
        for (int i = 0; i < (int)s.size(); ++i) rev[sa[i]]= i;
        int ind = 0; hi[0] = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (!rev[i]) {
                ind = 0;
                continue;
            }
            while (i + ind < (int)s.size() && s[i + ind] == s[sa[rev[i] - 1] + ind]) ++ind;
            hi[rev[i]] = ind ? ind-- : 0;
        }
    }
}

int z[maxn * 2];

void manacher(const string &s) {
    memset(z, 0, sizeof(z));
    string t = ".";
    for (int i = 0; i < (int)s.size(); ++i) t += s[i], t += '.';
    int l = 0, r = 0;
    for (int i = 1; i < (int)t.size(); ++i) {
        z[i] = (r > i ? min(z[2 * l - i], r - i) : 1);
        while (i - z[i] >= 0 && i + z[i] < (int)t.size() && t[i - z[i]] == t[i + z[i]]) ++z[i];
        if (i + z[i] > r) r = i + z[i], l = i;
    }
}

int stmax[20][maxn], stmin[20][maxn];

int qmax(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1);
    return max(stmax[p][l], stmax[p][r - (1 << p) + 1]);
}

int qmin(int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1);
    return min(stmin[p][l], stmin[p][r - (1 << p) + 1]);
}

int lcp(int x, int y) {
    return qmin(x + 1, y);
    x = sfxarray::rev[x];
    y = sfxarray::rev[y];
    if (x > y) swap(x, y);
    return qmin(x + 1, y);
}

int main() {
    string s;
    cin >> s;
    string _s = s;
    reverse(_s.begin(), _s.end());
    if (s == _s) {
        cout << s.size() << endl;
        cout << 1 << ' ' << s.size() << endl;
        cout << -1 << ' ' << -1 << endl;
        return 0;
    }
    string t = s;
    reverse(t.begin(), t.end());
    string S = s + "#" + t;
    sfxarray::build(S);
    manacher(s);

    // cerr << "sa: ";
    /* for (int i = 0; i < (int)S.size(); ++i) {
       cerr << sfxarray::sa[i] << ' ';
       } cerr << endl; */

    for (int i = 0; i < (int)S.size(); ++i) {
        stmax[0][i] = sfxarray::sa[i];
        stmin[0][i] = sfxarray::hi[i];
    }
    for (int z = 1; (1 << z) <= (int)S.size(); ++z) {
        for (int j = 0; j + (1 << z) - 1 < (int)S.size(); ++j) {
            stmax[z][j] = max(stmax[z - 1][j], stmax[z - 1][j + (1 << (z - 1))]);
            stmin[z][j] = min(stmin[z - 1][j], stmin[z - 1][j + (1 << (z - 1))]);
        }
    }

    int BDlen = -1;
    int BSTART = 0, BEND = 0, DSTART = 0, DEND = 0;
    for (int i = 0; i < (int)s.size(); ++i) { // odd length
        int len = (z[i * 2 + 1] + 1) / 2;
        int lstart = i - len;
        int reverse_start = (int)S.size() - 1 - lstart;
        int pos = sfxarray::rev[i + len];
        int to_up = pos;
        for (int i = 20; i >= 0; --i) if (to_up - (1 << i) >= 0) {
            if (qmax(to_up - (1 << i), pos) < reverse_start) to_up -= 1 << i;
        }
        int to_down = pos;
        for (int i = 20; i >= 0; --i) if (to_down + (1 << i) < (int)S.size()) {
            if (qmax(pos, to_down + (1 << i)) < reverse_start) to_down += 1 << i;
        }
        // cerr << "normal, odd length, i = " << i << " lstart = " << lstart << " reverse_start " << reverse_start << " " << "pos = " << pos << " to_up = " << to_up << " to_down = " << to_down << endl;
        if (to_up != 0 && qmax(to_up - 1, pos) >= reverse_start) {
            int start = sfxarray::sa[to_up - 1];
            int blen = lcp(to_up - 1, pos);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len + 1;
            int dend = i + len + blen - 1;
            // cerr << "to_up update, bstart = " << bstart << " bend = " << bend << " dstart = " << dstart << " dend = " << dend << endl;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BSTART = bstart;
                BEND = bend;
                DSTART = dstart;
                DEND = dend;
            }
        }
        if (to_down != (int)S.size() - 1 && qmax(pos, to_down + 1) >= reverse_start) {
            int start = sfxarray::sa[to_down + 1];
            int blen = lcp(pos, to_down + 1);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len + 1;
            int dend = i + len + blen - 1;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BSTART = bstart;
                BEND = bend;
                DSTART = dstart;
                DEND = dend;
            }
        }
    }

    // cout << BDlen << endl;
    // cout << BSTART << " " << BEND << endl;
    // cout << DSTART << " " << DEND << endl;

    for (int i = 1; i < (int)s.size(); ++i) { // even length
        int len = (z[i * 2]) / 2;
        int lstart = i - len - 1;
        int reverse_start = (int)S.size() - 1 - lstart;
        int pos = sfxarray::rev[i + len];
        int to_up = pos;
        for (int i = 20; i >= 0; --i) if (to_up - (1 << i) >= 0) {
            if (qmax(to_up - (1 << i), pos) < reverse_start) to_up -= 1 << i;
        }
        int to_down = pos;
        for (int i = 20; i >= 0; --i) if (to_down + (1 << i) < (int)S.size()) {
            if (qmax(pos, to_down + (1 << i)) < reverse_start) to_down += 1 << i;
        }
        // cerr << "normal, even length, i = " << i << " len = " << len << " lstart = " << lstart << " reverse_start " << reverse_start << " " << "pos = " << pos << " to_up = " << to_up << " to_down = " << to_down << endl;
        if (to_up != 0 && qmax(to_up - 1, pos) >= reverse_start) {
            int start = sfxarray::sa[to_up - 1];
            int blen = lcp(to_up - 1, pos);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len;
            int dend = i + len + blen - 1;
            // cerr << "to_up update, bstart = " << bstart << " bend = " << bend << " dstart = " << dstart << " dend = " << dend << endl;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BSTART = bstart;
                BEND = bend;
                DSTART = dstart;
                DEND = dend;
            }
        }
        if (to_down != (int)S.size() - 1 && qmax(pos, to_down + 1) >= reverse_start) {
            int start = sfxarray::sa[to_down + 1];
            int blen = lcp(pos, to_down + 1);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len;
            int dend = i + len + blen - 1;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BSTART = bstart;
                BEND = bend;
                DSTART = dstart;
                DEND = dend;
            }
        }
    }

    // cout << BDlen << endl;
    // cout << BSTART << " " << BEND << endl;
    // cout << DSTART << " " << DEND << endl;

    S = t + "#" + s;
    sfxarray::build(S);
    manacher(t);
    /* // cerr << "sa: ";
       for (int i = 0; i < (int)S.size(); ++i) {
    // cerr << sfxarray::sa[i] << ' ';
    } cerrhh << endl;
    cerr << "hi: "; 
    for (int i = 0; i < (int)S.size(); ++i) {
    cerr << sfxarray::hi[i] << ' ';
    } cerr << endl; */

    for (int i = 0; i < (int)S.size(); ++i) {
        stmax[0][i] = sfxarray::sa[i];
        stmin[0][i] = sfxarray::hi[i];
    }
    for (int z = 1; (1 << z) <= (int)S.size(); ++z) {
        for (int j = 0; j + (1 << z) - 1 < (int)S.size(); ++j) {
            stmax[z][j] = max(stmax[z - 1][j], stmax[z - 1][j + (1 << (z - 1))]);
            stmin[z][j] = min(stmin[z - 1][j], stmin[z - 1][j + (1 << (z - 1))]);
        }
    }

    for (int i = 0; i < (int)s.size(); ++i) { // odd length
        int len = (z[i * 2 + 1] + 1) / 2;
        int lstart = i - len;
        int reverse_start = (int)S.size() - 1 - lstart;
        int pos = sfxarray::rev[i + len];
        int to_up = pos;
        for (int i = 20; i >= 0; --i) if (to_up - (1 << i) >= 0) {
            if (qmax(to_up - (1 << i), pos) < reverse_start) to_up -= 1 << i;
        }
        int to_down = pos;
        for (int i = 20; i >= 0; --i) if (to_down + (1 << i) < (int)S.size()) {
            if (qmax(pos, to_down + (1 << i)) < reverse_start) to_down += 1 << i;
        }
        // cerr << "reverse, odd length, i = " << i << " len = " << len << " lstart = " << lstart << " reverse_start " << reverse_start << " " << "pos = " << pos << " to_up = " << to_up << " to_down = " << to_down << endl;
        // cerr << "ZZZZZ " << sfxarray::sa[to_down] << endl;
        if (to_up != 0 && qmax(to_up - 1, pos) >= reverse_start) {
            int start = sfxarray::sa[to_up - 1];
            int blen = lcp(to_up - 1, pos);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len + 1;
            int dend = i + len + blen - 1;
            // cerr << "to_up update, blen = " << blen << " bstart = " << s.size() - 1 - dend << " bend = " << s.size() - 1 - dstart << " dstart = " << s.size() - 1 - bend << " dend = " << s.size() - 1 - bstart << endl;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                DEND = s.size() - 1 - bstart;
                DSTART = s.size() - 1 - bend;
                BEND = s.size() - 1 - dstart;
                BSTART = s.size() - 1 - dend;
            }
        }
        if (to_down != (int)S.size() - 1 && qmax(pos, to_down + 1) >= reverse_start) {
            int start = sfxarray::sa[to_down + 1];
            int blen = lcp(pos, to_down + 1);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len + 1;
            int dend = i + len + blen - 1;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                DEND = s.size() - 1 - bstart;
                DSTART = s.size() - 1 - bend;
                BEND = s.size() - 1 - dstart;
                BSTART = s.size() - 1 - dend;
            }
        }
    }

    // cout << BDlen << endl;
    // cout << BSTART << " " << BEND << endl;
    // cout << DSTART << " " << DEND << endl;

    for (int i = 1; i < (int)s.size(); ++i) { // even length
        int len = (z[i * 2]) / 2;
        int lstart = i - len - 1;
        int reverse_start = (int)S.size() - 1 - lstart;
        int pos = sfxarray::rev[i + len];
        int to_up = pos;
        for (int i = 20; i >= 0; --i) if (to_up - (1 << i) >= 0) {
            if (qmax(to_up - (1 << i), pos) < reverse_start) to_up -= 1 << i;
        }
        int to_down = pos;
        for (int i = 20; i >= 0; --i) if (to_down + (1 << i) < (int)S.size()) {
            if (qmax(pos, to_down + (1 << i)) < reverse_start) to_down += 1 << i;
        }
        if (to_up != 0 && qmax(to_up - 1, pos) >= reverse_start) {
            int start = sfxarray::sa[to_up - 1];
            int blen = lcp(to_up - 1, pos);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len;
            int dend = i + len + blen - 1;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BEND = s.size() - 1 - bstart;
                BSTART = s.size() - 1 - bend;
                DEND = s.size() - 1 - dstart;
                DSTART = s.size() - 1 - dend;
            }
        }
        if (to_down != (int)S.size() - 1 && qmax(pos, to_down + 1) >= reverse_start) {
            int start = sfxarray::sa[to_down + 1];
            int blen = lcp(pos, to_down + 1);

            int bstart = ((int)S.size() - 1) - (start + blen - 1);
            int bend = bstart + blen - 1;
            int dstart = i - len;
            int dend = i + len + blen - 1;
            if (bend - bstart + 1 + dend - dstart + 1 > BDlen) {
                BDlen = bend - bstart + 1 + dend - dstart + 1;
                BEND = s.size() - 1 - bstart;
                BSTART = s.size() - 1 - bend;
                DEND = s.size() - 1 - dstart;
                DSTART = s.size() - 1 - dend;
            }
        }
    }

    cout << BDlen << endl;
    if (BSTART > DSTART) {
        swap(BSTART, DSTART);
        swap(BEND, DEND);
    }
    if (BSTART <= BEND) cout << BSTART + 1 << " " << BEND + 1 << endl;
    else cout << -1 << ' ' << -1 << endl;
    if (DSTART <= DEND) cout << DSTART + 1 << " " << DEND + 1 << endl;
    else cout << -1 << ' ' << -1 << endl;

    auto check = [&]() {
        string z = "";
        if (BSTART <= BEND) {
            z += s.substr(BSTART, BEND - BSTART + 1);
        }
        if (DSTART <= DEND) {
            z += s.substr(DSTART, DEND - DSTART + 1);
        }
        assert(z.size() == BDlen);
        string zz = z;
        reverse(zz.begin(), zz.end());
        assert(zz == z);

        for (int i = 0; i < s.size(); ++i) {
            for (int j = i; j < s.size(); ++j) {
                string t = s.substr(i, j - i + 1);
                string tt = t;
                reverse(tt.begin(), tt.end());
                if (tt == t) {
                    assert(j - i + 1 <= BDlen);
                }
            }
        }
        for (int i = 0; i < s.size(); ++i) {
            for (int j = i; j < s.size(); ++j) {
                for (int k = j + 1; k < s.size(); ++k) {
                    for (int l = k; l < s.size(); ++l) {
                        string t = s.substr(i, j - i + 1) + s.substr(k, l - k + 1);
                        string tt = t;
                        reverse(tt.begin(), tt.end());
                        if (t == tt) {
                            assert(j - i + 1 + l - k + 1 <= BDlen);
                        }
                    }
                }
            }
        }
    };

    //    check();
}
