#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 2) {
        cout << "10\n";
        return 0;
    }
    const int m = n / 2;
    vector<vector<int>> adj(m, vector<int>(m));
    for (int i = 0; i < m; ++i) {
        adj[i][(i * 2) % m]++;
        adj[i][(i * 2 + 1) % m]++;
    }
    adj[0][1]--;

    vector<int> euler;

    auto Dfs = [&](auto self, int x) -> void {
        for (int i = 0; i < m; ++i) {
            if (adj[x][i] > 0) {
                adj[x][i]--;
                self(self, i);
            }
        }
        euler.push_back(x);
    };

    Dfs(Dfs, 1);
    reverse(euler.begin(), euler.end());
    cout << 1;
    int x = 1;
    vector<bool> used(n);
    used[1] = true;
    for (int i = 0; i + 1 < euler.size(); ++i) {
        int a = euler[i], b = euler[(i + 1) % euler.size()];
        if ((a * 2) % m == b) cout << 0, x = (x * 2) % n;
        else cout << 1, x = (x * 2 + 1) % n;
        assert(!used[x]);
        used[x] = true;
    }
    cout << endl;
}

