#include <bits/stdc++.h>
using namespace std;

vector<int> g[1000006];

int n;
int d[1000006];

void Dfs(int now, int pa) {
    for (int i : g[now]) if (i != pa && i <= n) {
        d[i] = d[now] + 1;
        Dfs(i, now);
    }
}

int main() {
    cin >> n;
    n -= 2;
    g[1].push_back(2);
    g[2].push_back(1);
    g[1].push_back(3);
    g[3].push_back(1);
    g[1].push_back(4);
    g[4].push_back(1);
    int nn = 4;
    for (int i = 2; nn <= 1000000; ++i) {
        g[i].push_back(++nn);
        g[nn].push_back(i);
        g[i].push_back(++nn);
        g[nn].push_back(i);
    }

    Dfs(1, 0);

    int x = max_element(d, d + n + 1) - d;

    d[x] = 0;
    Dfs(x, 0);

    cout << *max_element(d, d + n + 1) << '\n';
}

