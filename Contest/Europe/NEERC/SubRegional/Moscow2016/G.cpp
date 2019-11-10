#include <bits/stdc++.h>
using namespace std;

const int kN = 100 + 5;
int adj[kN][kN];
vector<int> euler;

void Dfs(int x, int n) {
    for (int i = 0; i < n; ++i) {
        if (adj[x][i] > 0) {
            --adj[x][i];
            Dfs(i, n);
        }
    }
    euler.push_back(x);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) adj[i][j]++;
        }
    }
    Dfs(0, n);
    // for (int u : euler) printf("%d ", u);
    for (int i = 0; i < euler.size(); ++i) {
        if (i == euler.size() - 1) {
            printf("%d %d %d\n", 0, euler[i] + 1, euler[i - 1] + 1);
        } else if (i == 0) {
            printf("%d %d %d\n", euler[i] + 1, euler[i] + 1, 0);
        } else {
            printf("%d %d %d\n", euler[i] + 1, euler[i] + 1, euler[i - 1] + 1);
        }
    }
}
