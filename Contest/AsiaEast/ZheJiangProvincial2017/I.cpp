#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        map<int, int> id;
        auto gid = [&] (int x) {
            auto it = id.find(x);
            if (it != id.end()) return it->second;
            int y = id.size();
            return id[x] = y;
        };

        vector<int> djs(2 * n);
        vector<int> sz(2 * n, 1);
        iota(djs.begin(), djs.end(), 0);
        function<int(int)> Find = [&] (int x) { return djs[x] == x ? x : djs[x] = Find(djs[x]); };
        auto Union = [&] (int x, int y) { 
            x = Find(x);
            y = Find(y);
            if (x == y) return ;
            djs[x] = y;
            sz[y] += sz[x];
        };

        while (n--) {
            int a, b; cin >> a >> b;
            a = gid(a);
            b = gid(b);
            Union(a, b);
        }

        cout << *max_element(sz.begin(), sz.end()) << '\n';
    }
}

