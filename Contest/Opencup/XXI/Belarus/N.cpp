#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> o(n);
    iota(o.begin(), o.end(), 1);
    sort(o.begin(), o.end(), [&] (int i, int j) { return a[i] < a[j]; });

    vector<int> start(n + 2, 0); 
    vector<int> djs(n + 2); iota(djs.begin(), djs.end(), 0);
    vector<int> sz(n + 2, 1);
    vector<int> L(n + 2, 0), R(n + 2, 0);

    auto index_cmp = [&] (int i, int j) { return a[i] > a[j]; };
    vector<priority_queue<int, vector<int>, decltype(index_cmp)>> pq(n + 2, priority_queue<int, vector<int>, decltype(index_cmp)>(index_cmp));
    vector<int> lose(n + 2, 0);

    function<int(int)> F = [&] (int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); };
    auto U = [&] (int x, int y) {
        x = F(x);
        y = F(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        L[y] = min(L[y], L[x]);
        R[y] = max(R[y], R[x]);
        djs[x] = y;
        sz[y] += sz[x];
        // cerr << "merge djs " << x << ' ' << y << endl;
        while (pq[x].size()) {
            int z = pq[x].top();
            pq[x].pop();
            pq[y].push(z);
            // cerr << "move " << z << " from " << x  << " to " << y << endl;
        }
    };

    for (int i = 0; i < n; ) {
        int j = i;
        while (a[o[j]] == a[o[i]]) {
            // cerr << "j o[j] " << j << ' ' << o[j] << endl;
            int at = o[j];
            start[at] = 1;
            L[at] = R[at] = at;
            pq[at].push(at);
            int le = F(at - 1);
            // cerr << "le = " << le << " start " << start[le] << endl;
            if (start[le]) {
                while (pq[le].size()) {
                    int z = pq[le].top();
                    // cerr << "validate index " << z << " with index " << at << endl;
                    if (a[z] + sz[le] - 1 < a[at]) {
                        // cerr << "lose" << endl;
                        lose[z] = 1;
                        pq[le].pop();
                    } else break;
                }
                U(at - 1, at);
            }
            // cerr << "at + 1 = " << at + 1 << endl;
            // cerr << "F = " << F(at + 1) << endl;
            int ri = F(at + 1);
            // cerr << "ri = " << ri << endl;
            if (start[ri]) {
                while (pq[ri].size()) {
                    int z = pq[ri].top();
                    // cerr << "validate index " << z << " with index " << at << endl;
                    if (a[z] + sz[ri] - 1 < a[at]) {
                        // cerr << "lose" << endl;
                        lose[z] = 1;
                        pq[ri].pop();
                    } else break;
                }
                U(at + 1, at);
            }
            ++j;
        }
        i = j;
    }

    vector<int> win;
    for (int i = 1; i <= n; ++i) if (!lose[i]) win.push_back(i);
    cout << win.size() << endl;
    for (int i : win) cout << i << ' ';
    cout << endl;
}

