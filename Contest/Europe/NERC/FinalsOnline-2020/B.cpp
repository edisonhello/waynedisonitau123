#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string a, b; cin >> a >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (char &c : a) c -= 'A';
    for (char &c : b) c -= 'A';

    int n; cin >> n;

    vector<int> count(26, 0);
    set<int> appear;
    vector<int> enu(26, -1);
    vector<int> carry(20, 0);
    vector<int> used(10, 0);

    vector<string> anss;

    while (n--) {
        string s; cin >> s;
        string os = s;
        for (char &c : s) c -= 'A';

        int nn = s.size();
        int nnn = max(a.size(), b.size());

        if (nn != nnn && nn != nnn + 1) continue;

        reverse(s.begin(), s.end());
        fill(count.begin(), count.end(), 0);
        appear.clear();
        for (char i : a) ++count[i];
        for (char i : b) ++count[i];
        for (char i : s) ++count[i];
        for (char i : a) appear.insert(i);
        for (char i : b) appear.insert(i);
        for (char i : s) appear.insert(i);

        if (appear.size() > 10) continue;

        bool twoone = 0;
        for (int i = 0; i < (int)min(a.size(), b.size()); ++i) {
            if (count[a[i]] == 1 && count[b[i]] == 1) twoone = 1;
        }

        if (twoone) continue;

        fill(enu.begin(), enu.end(), -1);
        fill(used.begin(), used.end(), 0);

        if (nn != nnn) enu[s.back()] = 1, used[1] = 1;
        
        fill(carry.begin(), carry.end(), 0);

        int sol = 0;

        bool print = false;
        auto dfs = [&] (auto dfs, int i) -> void {
            if (sol > 1) return;

            if (i == (int)max(a.size(), b.size())) {
                ++sol;
                // cerr << "a sol" << endl;
                // for (int i = 0; i < 26; ++i) if (enu[i] != -1) {
                //     cerr << "char " << char(i + 'A') << " = " << enu[i] << endl;
                // }
                return;
            }

            int al = 0, ar = 9;

            if (i >= (int)a.size()) al = ar = 0;
            else if (enu[a[i]] != -1) al = ar = enu[a[i]];

            if (i == (int)a.size() - 1) al = max(al, 1);

            for (int ai = al; ai <= ar; ++ai) {
                if (i < (int)a.size() && used[ai] && enu[a[i]] != ai) continue;
                bool aalready = i < (int)a.size() && enu[a[i]] == ai;
                if (i < (int)a.size() && !aalready) {
                    enu[a[i]] = ai;
                    used[ai] = 1;
                }

                // cerr << i << " a try " << char(a[i] + 'A') << " as " << ai << endl;

                int bl = 0, br = 9;

                if (i >= (int)b.size()) bl = br = 0;
                else if (enu[b[i]] != -1) bl = br = enu[b[i]];

                if (i == (int)b.size() - 1) bl = max(bl, 1);

                bool ok = 1;
                if (enu[s[i]] != -1) {
                    int tar = enu[s[i]] - ai - carry[i];
                    tar += 10;
                    tar %= 10;
                    if (tar < bl || br < tar) ok = 0;
                    else bl = br = tar;
                }

                if (ok) {
                    for (int bi = bl; bi <= br; ++bi) {
                        if (i < (int)b.size() && used[bi] && enu[b[i]] != bi) continue;

                        // cerr << i << " b try " << char(b[i] + 'A') << " as " << bi << endl;

                        int sum = ai + bi + carry[i];
                        int dig = sum % 10;
                        if (i == nnn - 1 && nn != nnn && sum < 10) continue;
                        if (i == nnn - 1 && nn == nnn && sum >= 10) continue;

                        // cerr << "try " << char(b[i] + 'A') << " as " << bi << endl;

                        bool balready = i < (int)b.size() && enu[b[i]] == bi;
                        if (i < (int)b.size() && !balready) {
                            enu[b[i]] = bi;
                            used[bi] = 1;
                        }

                        if (enu[s[i]] == -1 || enu[s[i]] == dig) {
                            bool already = enu[s[i]] == dig;
                            if (!(!already && used[dig])) {
                                if (!(i < (int)b.size() && bi == dig && b[i] != s[i])) {
                                    if (!already) {
                                        enu[s[i]] = dig;
                                        used[dig] = 1;
                                    }

                                    // cerr << i << " try s " << char(s[i] + 'A') << " as " << dig << endl;

                                    carry[i + 1] = sum >= 10;
                                    dfs(dfs, i + 1);

                                    if (!already) {
                                        enu[s[i]] = -1;
                                        used[dig] = 0;
                                    } 
                                }
                            }
                        }

                        if (i < (int)b.size() && !balready) {
                            enu[b[i]] = -1;
                            used[bi] = 0;
                        }
                    }
                }

                if (i < (int)a.size() && !aalready) {
                    enu[a[i]] = -1;
                    used[ai] = 0;
                }
            }
        };

        dfs(dfs, 0);

        // cerr << os << " solution " << sol << endl;

        if (sol == 1) {
            anss.push_back(os);
        }
    }

    cout << anss.size() << endl;
    for (auto s : anss) cout << s << '\n';

}

