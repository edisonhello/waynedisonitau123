#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> lis;
        vector<int> pos(n, -1);
        for (int i = 0; i < n; ++i) {
            if (lis.empty() || a[i] > lis.back()) {
                pos[i] = lis.size();
                lis.push_back(a[i]);
            } else {
                auto it = upper_bound(lis.begin(), lis.end(), a[i]);
                pos[i] = it - lis.begin();
                *it = a[i];
            }
        }
        vector<int> inlis(n, 0);
        int nowl = lis.size() - 1;
        vector<int> lismem;
        for (int i = n - 1; i >= 0; --i) {
            if (pos[i] == nowl) {
                --nowl;
                inlis[i] = 1;
                lismem.push_back(i);
            }
        }
        reverse(lismem.begin(), lismem.end());

        // cerr << "lis: ";
        // for (int i : lismem) cerr << i << ' ';
        // cerr << endl;

        vector<int> dsmem;
        for (int i = 0; i < n; ++i) if (!inlis[i]) dsmem.push_back(i);
        // cerr << "dsmem: ";
        // for (int i : dsmem) cerr << i << ' ';
        // cerr << endl;

        auto IsDs = [&] (const vector<int> &mem) {
            for (int i = 1; i < (int)mem.size(); ++i) if (a[mem[i - 1]] < a[mem[i]]) return false;
            return true;
        };

        if (IsDs(dsmem)) {
            cout << "YES" << '\n';
            cout << lis.size();
            for (int i = 0; i < n; ++i) if (inlis[i]) cout << ' ' << a[i];
            cout << endl << n - lis.size();
            for (int i = 0; i < n; ++i) if (!inlis[i]) cout << ' ' << a[i];
            cout << endl;
            continue;
        }

        vector<int> prebad(dsmem.size(), 0);
        for (int i = 1; i < (int)dsmem.size(); ++i) if (a[dsmem[i - 1]] < a[dsmem[i]]) {
            prebad[i]++;
        }
        for (int i = 1; i < (int)dsmem.size(); ++i) prebad[i] += prebad[i - 1];

        if (prebad.back() > 1) {
            cout << "NO" << endl;
            continue;
        }
        assert(prebad.back() == 1);

        vector<int> sufbad(dsmem.size(), 0);
        for (int i = dsmem.size() - 2; i >= 0; --i) if (a[dsmem[i + 1]] > a[dsmem[i]]) {
            sufbad[i]++;
        }
        for (int i = dsmem.size() - 2; i >= 0; --i) sufbad[i] += sufbad[i + 1];
        assert(sufbad[0] == 1);

        bool printed = 0;

        auto Print = [&] (vector<int> &ma, vector<int> &mb) {
            cout << "YES" << endl;
            cout << ma.size();
            for (int i : ma) cout << ' ' << a[i];
            cout << endl;
            cout << mb.size();
            for (int i : mb) cout << ' ' << a[i];
            cout << endl;
            printed = 1;
        };

        auto PogNew = [&] (int pos) -> pair<int, vector<int>> {
            for (int i = 0; i < (int)lismem.size(); ++i) {
                if (i == 0 || (lismem[i - 1] < pos && a[lismem[i - 1]] < a[pos])) {
                    if (i == (int)lismem.size() - 1 || (pos < lismem[i + 1] && a[pos] < a[lismem[i + 1]])) {
                        vector<int> nlismem = lismem;
                        nlismem[i] = pos;
                        return make_pair(lismem[i], nlismem);
                    }
                }
            }
            return make_pair(-1, vector<int>());
        };

        for (int i = 0; i < (int)dsmem.size() - 1; ++i) {
            if (a[dsmem[i]] < a[dsmem[i + 1]]) {
                // if ((i == 0 || prebad[i - 1] == 0) && (i + 1 == (int)dsmem.size() - 1 || sufbad[i + 2] == 0) && (i == 0 || a[dsmem[i - 1]] > a[dsmem[i + 1]]) && (i + 1 == (int)dsmem.size() - 1 || a[dsmem[i + 1]] > a[dsmem[i + 2]])) {
                //     if (dsmem[i] < lismem[0]) {
                //         if (
                //     }
                // }
                for (int j = i; j <= i + 1; ++j) {
                    // cerr << "j = " << j << endl;
                    vector<int> ndsmem;
                    for (int k : dsmem) if (k != dsmem[j]) ndsmem.push_back(k);

                    int swap_pos; vector<int> nismem;
                    tie(swap_pos, nismem) = PogNew(dsmem[j]);
                    if (swap_pos == -1) continue;

                    ndsmem.push_back(swap_pos);
                    sort(ndsmem.begin(), ndsmem.end());
                    if (IsDs(ndsmem)) {
                        Print(nismem, ndsmem);
                        break;
                    }
                }
                break;
            }
        }

        if (!printed) {
            cout << "NO" << endl;
            continue;
        }

    }
}

