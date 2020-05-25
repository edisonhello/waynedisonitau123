#include <bits/stdc++.h>
using namespace std;

int djs[100005];

int main() {
    int b, m; cin >> b >> m;

    vector<int> group(m);
    int cgroup = m;
    for (int i = 0; i < m; ++i) group[i] = i;

    while (true) {
        vector<bool> used(cgroup);
        vector<vector<int>> to(cgroup);
        vector<vector<int>> v;
        for (int i = 0; i < m; ++i) {
            if (used[group[i]]) continue;
            used[group[i]] = true;
            vector<int> w(b);
            for (int j = 0; j < b; ++j) {
                int k = group[(b * i + j) % m];
                w[j] = k;
            }
            v.push_back(w);
            to[group[i]] = w;
        }
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        vector<int> ngroup(m);
        for (int i = 0; i < m; ++i) {
            int t = lower_bound(v.begin(), v.end(), to[group[i]]) - v.begin();
            ngroup[i] = t;
        }

        bool collide = false;
        for (int i = 1; i < m; ++i) {
            if (ngroup[i] == ngroup[0]) collide = true;
        }
        int ncgroup = v.size();
        if (collide) {
            ngroup[0] = ncgroup++;
        }
        if (cgroup == ncgroup) break;
        group = ngroup;
        cgroup = ncgroup;
    }
    cout << cgroup << " " << group[0] << "\n";
    for (int i = 0; i < cgroup; ++i) {
        if (i == group[0]) cout << "G ";
        else cout << "B ";
    }
    cout << "\n";
    vector<vector<int>> rep(cgroup);
    for (int i = 0; i < m; ++i) rep[group[i]].push_back(i);
    // for (int i = 0; i < cgroup; ++i) {
    //     for (int j = 0; j < b; ++j) {
    //         int ref = group[(rep[i][0] * b + j) % m];
    //         for (int k : rep[i]) assert(group[(k * b + j) % m] == ref);
    //     }
    // }
    for (int i = 0; i < cgroup; ++i) {
        for (int j = 0; j < b; ++j) {
            int k = (rep[i][0] * b + j) % m;
            cout << group[k] << " ";
        }
        cout << "\n";
    }
    // if (d == 1) {
    //     cout << m / d << ' ' << 0 << endl;
    //     for (int i = 0; i < m / d; ++i) 
    //         if (i) cout << "B ";
    //         else cout << "G ";
    //     cout << endl;

    //     int mm = m / d;

    //     for (int i = 0; i < m / d; ++i) {
    //         for (int j = 0; j < b; ++j) {
    //             int x = (i * b + j) % mm;
    //             cout << x << ' ';
    //         }
    //         cout << '\n';
    //     }
    // } else {
    //     cout << m / d + 1 << ' ' << 0 << endl;
    //     for (int i = 0; i <= m / d; ++i) 
    //         if (i) cout << "B ";
    //         else cout << "G ";
    //     cout << endl;

    //     int mm = m / d;

    //     for (int i = 0; i <= m / d; ++i) {
    //         for (int j = 0; j < b; ++j) {
    //             int x = (i * b + j) % m;
    //             if (x == 0) cout << 0 << ' ';
    //             else {
    //                 if (x % mm == 0) cout << mm << ' ';
    //                 else cout << x % mm << ' ';
    //             }
    //         }
    //         cout << '\n';
    //     }
    // }
}

