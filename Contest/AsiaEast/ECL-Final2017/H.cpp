#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int ary[1000006], b[1000006];
int vowel[10000];

int main() {
    vowel['a'] = vowel['e'] = vowel['i'] = vowel['o'] = vowel['u'] = 1;
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        string s; cin >> s;
        int x, y; cin >> x >> y;
        int n = s.size();
        for (int i = 0; i < n; ++i) ary[i] = vowel[s[i]];
        for (int i = 0; i < n; ++i) if (!ary[i]) ary[i] = -1;
        for (int i = 0; i < n; ++i) if (s[i] == '?') ary[i] = 0;
        ary[n] = ary[n + 1] = b[n] = b[n + 1] = 0;
        // cout << "Ary: "; for (int i = 0; i < n; ++i) cout << ary[i] << " "; cout << endl;
        bool like = [&] () -> bool {
            for (int i = 0; i < n; ++i) b[i] = ary[i];
            for (int i = 0, j; j < n; i = j) {
                if (b[i]) { j = i + 1; continue; }
                for (j = i; j < n && !b[j]; ++j);
                int best = -1, last = b[j], lastcnt = 1010101;
                int front = (i ? b[i - 1] : 0), fc = 0;
                for (int z = i - 1; z >= 0 && b[z] == front; --z) ++fc;

                // cerr << "fc = " << fc << endl;
                auto check = [&] (int id) -> void {
                    int cntf = 1;
                    if (b[i] == front) { cntf = fc + 1; }
                    if (b[i + 1] == b[i]) cntf++;
                    if (b[i] == 1) {
                        if (cntf >= x) return;
                    } else if (b[i] == -1) {
                        if (cntf >= y) return;
                    }
                    // cerr << "check " << id << ", cntf = " << cntf << endl;
                    // for (int i = 0; i < n; ++i) cout << b[i] << " "; cout << endl;

                    for (int ii = i, jj; ii < j; ii = jj) {
                        for (jj = ii; jj < j && b[ii] == b[jj]; ++jj);
                        if (b[ii] == 1) {
                            if (jj - ii >= x) return;
                        } else {
                            if (jj - ii >= y) return;
                        }
                    }

                    int cntl = 1;
                    if (b[j - 1] == last) ++cntl;
                    if (b[j - 2] == last && b[j - 1] == last) ++cntl;

                    // cerr << "cntl = " << cntl << endl;
                    if (lastcnt > cntl) {
                        lastcnt = cntl;
                        best = id;
                    }
                };

                auto case1 = [&] () -> void {
                    for (int z = i; z < j; ++z) if ((z - i) & 1) b[z] = 1; else b[z] = -1;
                };
                auto case2 = [&] () -> void {
                    for (int z = i; z < j; ++z) if ((z - i) & 1) b[z] = -1; else b[z] = 1;
                };
                auto case3 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = -1;
                        else if ((z - i) & 1) b[z] = -1;
                        else b[z] = 1;
                    }
                };
                auto case4 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = 1;
                        else if ((z - i) & 1) b[z] = 1;
                        else b[z] = -1;
                    }
                };
                auto case5 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = -1;
                        else if (z == i + 1) b[z] = 1;
                        else if ((z - i) & 1) b[z] = -1;
                        else b[z] = 1;
                    }
                };
                auto case6 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = 1;
                        else if (z == i + 1) b[z] = -1;
                        else if ((z - i) & 1) b[z] = 1;
                        else b[z] = -1;
                    }
                };
                auto case7 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = 1;
                        else if (z == i + 1) b[z] = -1;
                        else if (z <= i + 3) b[z] = 1;
                        else if ((z - i) & 1) b[z] = 1;
                        else b[z] = -1;
                    }
                };
                auto case8 = [&] () -> void {
                    for (int z = i; z < j; ++z) {
                        if (z == i) b[z] = -1;
                        else if (z == i + 1) b[z] = 1;
                        else if (z <= i + 3) b[z] = -1;
                        else if ((z - i) & 1) b[z] = -1;
                        else b[z] = 1;
                    }
                };

                case1(); check(1);
                case2(); check(2);
                case3(); check(3);
                case4(); check(4);
                case5(); check(5);
                case6(); check(6);
                case7(); check(7);
                case8(); check(8);

                if (best == -1) return 0;
                if (best == 1) case1();
                if (best == 2) case2();
                if (best == 3) case3();
                if (best == 4) case4();
                if (best == 5) case5();
                if (best == 6) case6();
                if (best == 7) case7();
                if (best == 8) case8();
                // cerr << i << " to " << j - 1 << ", use case = " << best << endl;
            }

            for (int i = 0, j; i < n; i = j) {
                for (j = i; j < n && b[i] == b[j]; ++j);
                if (b[i] == 1) {
                    if (j - i >= x) return 0;
                } else {
                    if (j - i >= y) return 0;
                }
            }
            return 1;
        }();
        bool dislike = [&] () -> bool {
            for (int i = 0; i < n; ++i) b[i] = ary[i];
            for (int i = 0; i < n; ++i) if (!b[i]) b[i] = 1;
            for (int i = 0, j; i < n; i = j) {
                for (j = i; j < n && b[i] == b[j]; ++j);
                if (b[i] == 1) {
                    if (j - i >= x) return 1;
                } else {
                    if (j - i >= y) return 1;
                }
            }
            for (int i = 0; i < n; ++i) b[i] = ary[i];
            for (int i = 0; i < n; ++i) if (!b[i]) b[i] = -1;
            for (int i = 0, j; i < n; i = j) {
                for (j = i; j < n && b[i] == b[j]; ++j);
                if (b[i] == 1) {
                    if (j - i >= x) return 1;
                } else {
                    if (j - i >= y) return 1;
                }
            }
            return 0;
        }();
        if (like && dislike) cout << "SURPRISE" << endl;
        else if (like) cout << "LIKE" << endl;
        else cout << "DISLIKE" << endl;
    }
}
