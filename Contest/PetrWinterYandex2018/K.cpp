#include <bits/stdc++.h>
using namespace std;

bool change[500005];
int label[500005];
int edge[500005][2], deg[500005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> change[i];
        label[i] = i;
    }
    for (int i = 1; i < n; ++i) {
        cin >> edge[i][0] >> edge[i][1];
        ++deg[edge[i][0]], ++deg[edge[i][1]];
    }
    vector<int> odd;
    int xorodd = 0;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] & 1) {
            odd.push_back(i);
            xorodd ^= i;
        }
    }
    if (xorodd ^ n) {
        vector<int> odd_change;
        for (int i : odd) {
            if (change[i]) odd_change.push_back(i);
        }
        if (odd_change.size() >= 2u) {
            // cout << "odd_change size = " << odd_change.size() << endl;
            int target = n;
            label[odd_change[0]] ^= 131072;
            xorodd ^= 131072;
            label[odd_change[1]] = xorodd ^ target ^ odd_change[1];
            if (label[odd_change[1]] == label[odd_change[0]]) {
                if (odd_change.size() == 2u) {
                    cout << -1 << endl;
                    exit(0);
                } else {
                    label[odd_change[1]] ^= 262144;
                    label[odd_change[2]] ^= 262144;
                }
            }
        } else if (odd_change.size() == 1u) {
            int to = n ^ xorodd ^ odd_change[0];
            if (to > n) {
                label[odd_change[0]] = to;
            } else if (change[to]) {
                label[to] ^= 131072;
                label[odd_change[0]] = to;
            } else {
                cout << -1 << endl;
                exit(0);
            }
        } else {
            cout << -1 << endl;
            exit(0);
        }
    }
    cout << n << endl;
    for (int i = 1; i < n; ++i) {
        cout << label[edge[i][0]] << ' ' << label[edge[i][1]] << '\n';
    }
}
