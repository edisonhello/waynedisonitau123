#include <bits/stdc++.h>
using namespace std;

char ans[1004][1004];
bool blk[1004][1004];
int id[1004][1004];
int djs[1004 * 1004];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }
bool C(int x, int y) { return F(x) == F(y); }

void U(int a, int b, int c, int d) { U(id[a][b], id[c][d]); }
bool C(int a, int b, int c, int d) { return C(id[a][b], id[c][d]); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, f; cin >> n >> m >> f;
    auto output = [&] () -> void {
        return;
        for (int j = m; j >= 1; --j) {
            for (int i = 1; i <= n; ++i) {
                if (blk[i][j]) cout << " ";
                else cout << ans[i][j];
            }
            cout << endl;
        }
        cout << endl;
    };
    int N = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) id[i][j] = ++N;
    for (int i = 1; i <= N; ++i) djs[i] = i;
    for (int j = 1; j <= m; j += 2) {
        for (int i = 1; i <= n; ++i) ans[i][j] = 'P'; ans[n][j] = 'G';
        for (int i = 1; i <= n; ++i) ans[i][j + 1] = 'L'; ans[1][j + 1] = 'D';
    }
    while (f--) {
        int x, y; cin >> x >> y;
        blk[x][y] = blk[x + 1][y] = blk[x][y + 1] = blk[x + 1][y + 1] = 1;
        if (ans[x][y] == 'P') {
            ans[x - 1][y] = 'G';
            ans[x + 2][y + 1] = 'D';
        } else {
            ans[x - 1][y + 1] = 'D';
            ans[x + 2][y] = 'G';
        }
    }
    output();
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        if (ans[i][j] == 'P') U(i, j, i + 1, j);
        if (ans[i][j] == 'G') U(i, j, i, j + 1);
        if (ans[i][j] == 'L') U(i, j, i - 1, j);
        if (ans[i][j] == 'D') U(i, j, i, j - 1);
    }
    for (int j = 2; j < m; j += 2) for (int i = 1; i < n; ++i) {
        if (blk[i][j] || blk[i][j + 1] || blk[i + 1][j] || blk[i + 1][j + 1]) continue;
        if (!C(i, j, i, j + 1)) {
            ans[i + 1][j] = 'G';
            ans[i][j + 1] = 'D';
            U(i, j, i, j + 1);
        }
    }
    output();
    for (int j = 3; j < m - 1; j += 2) for (int i = 1; i < n; ++i) {
        if (blk[i][j] || blk[i][j + 1] || blk[i + 1][j] || blk[i + 1][j + 1]) continue;
        if (!C(i, j, i, j + 1)) {
            ans[i][j] = 'G';
            ans[i + 1][j + 1] = 'D';
            U(i, j, i, j + 1);
        }
    }
    output();
    string s = "";
    int x = 1, y = 1;
    while (x != 1 || y != 1 || s == "") {
        s += ans[x][y];
        if (ans[x][y] == 'P') ++x;
        else if (ans[x][y] == 'L') --x;
        else if (ans[x][y] == 'G') ++y;
        else if (ans[x][y] == 'D') --y;
    }
    cout << "TAK" << endl;
    cout << s << endl;
}
