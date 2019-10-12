#include <bits/stdc++.h>
using namespace std;

void NO() {
    cout << "NO" << endl;
    exit(0);
}

int a[205][205];
int p[205], pp[205];

int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) cin >> a[i][j];
    }
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int j = n - 1; j >= 1; --j) {
        int i = n - 1, jj = j;
        while (jj != 0) {
            // cout << "i = " << i << ", jj = " << jj << ", a[i][jj] = " << a[i][jj] << endl;
            // i, i + 1
            if (a[i][jj] == 0) { // 
                if (p[i] > p[i + 1]) NO();
            } else {
                if (p[i] > p[i + 1]) NO();
                swap(p[i], p[i + 1]);
            }
            --i, --jj;
        }
    }
    // cout << "first ok" << endl;
    for (int i = 1; i <= n; ++i) pp[i] = p[i];
    // cout << "p = "; for (int i = 1; i <= n; ++i) cout << p[i] << ' '; cout << endl;
    for (int j = 1; j < n; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            // cout << "i = " << i << ", j = " << j << ", a[i][j] = " << a[i][j] << endl;
            if (a[i][j] == 0) {
                if (pp[i] > pp[i + 1]) NO();
            } else {
                if (pp[i] < pp[i + 1]) NO();
                swap(pp[i], pp[i + 1]);
            }
        }
    }
    // cout << "second ok" << endl;
    for (int i = 1; i <= n; ++i) if (pp[i] != i) NO();
    cout << "YES" << endl;
    for (int i = 1; i <= n; ++i) cout << p[i] << " ";
}
