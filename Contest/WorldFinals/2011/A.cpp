#include <bits/stdc++.h>
using namespace std;

#define int long long

#define Ans pair<int, vector<pair<int, char>>>

bool operator < (Ans a, Ans b) {
    if (a.first != b.first) return a.first < b.first;
    for (int32_t ai = 0, bi = 0; ; ) {
        if (ai == a.second.size() && bi == b.second.size()) return false;
        if (ai == a.second.size()) return true;
        if (bi == b.second.size()) return false;

        if (a.second[ai].first == 0) ++ai;
        else if (b.second[bi].first == 0) ++bi;
        else if (a.second[ai].second != b.second[bi].second) {
            return a.second[ai].second < b.second[bi].second;
        } else {
            int z = min(a.second[ai].first, b.second[bi].first);
            a.second[ai].first -= z;
            b.second[bi].first -= z;
        }
    }
}

Ans regular(Ans tmp) {
    Ans rt; rt.first = tmp.first;
    for (auto &p : tmp.second) {
        if (p.first == 0) continue;
        if (rt.second.empty() || rt.second.back().second != p.second) {
            rt.second.push_back(p);
        } else rt.second.back().first += p.first;
    }
    return rt;
}

void print_ans(Ans ans) {
    for (int i = 0; i < (int)ans.second.size(); ++i) {
        cout << ans.second[i].first << ans.second[i].second << " \n"[i == (int)ans.second.size() - 1];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int a, m, p, q, r, s;
    int ks = 0;
    while (cin >> a >> m >> p >> q >> r >> s) {
        if ((a|m|p|q|r|s) == 0) break;

        ++ks;
        cout << "Case " << ks << ": ";

        if (m == 1) {
            int L = r - p, R = s - q;
            L = L / a + !!(L % a), R /= a;
            if (L > R) {
                cout << "impossible" << '\n';
            } else {
                if (L <= 0 && 0 <= R) cout << "empty" << '\n';
                else if (R < 0) cout << "impossible" << '\n';
                else cout << L << 'A' << '\n';
            }
        } else {
            Ans ans; ans.first = 1e18;

            auto update = [&] (Ans tmp) {
                if (tmp < ans) ans = tmp;
            };
            int mm = 1;
            for (int i = 0; ; ++i) {
                int L = r - p, R = s - q;
                // cout << "i = " << i << " p = " << p << " q = " << q << " r = " << r << " s = " << s << " L = " << L << " R = " << R << endl;
                if (R < 0) break;
                if (L > R) break;
                if (L <= 0 && 0 <= R) {
                    Ans tmp;
                    tmp.first = i;
                    tmp.second.emplace_back(i, 'M');
                    update(tmp);
                } else {
                    L = L / a + !!(L % a), R /= a;
                    if (L <= R) {
                        // cout << "new L R " << L << " " << R << endl;
                        int mmm = mm;
                        vector<int> add_before(i + 1, 0);
                        int ab4it = 0, tota = 0;

                        auto make_answer = [&] () {
                            Ans tmp; 
                            tmp.first = i + tota;
                            tmp.second.emplace_back(add_before[0], 'A');
                            for (int i = 1; i < (int)add_before.size(); ++i) {
                                tmp.second.emplace_back(1, 'M');
                                tmp.second.emplace_back(add_before[i], 'A');
                            }
                            return tmp;
                        };
                        while (mmm) {
                            int tt = L / mmm;
                            if (tt * mmm == L) {
                                add_before[ab4it] = tt;
                                tota += tt;

                                Ans tmp = make_answer();
                                update(tmp);
                                break;
                            } else if ((tt + 1) * mmm <= R) {
                                add_before[ab4it] = tt + 1;
                                tota += tt + 1;

                                Ans tmp = make_answer();
                                update(tmp);
                                break;
                            } else {
                                add_before[ab4it] = tt;
                                tota += tt;

                                L -= tt * mmm, R -= tt * mmm;
                            }
                            ++ab4it;
                            mmm /= m;
                        }
                    }
                }

                p *= m, q *= m; mm *= m;
            }

            ans = regular(ans);
            if (ans.first > 5e17) cout << "impossible" << '\n';
            else if (ans.first == 0) cout << "empty" << '\n';
            else print_ans(ans);
        }
        fflush(stdout);
    }
}
