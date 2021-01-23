#include <bits/stdc++.h>
using namespace std;

string mp[1010];

void dfs(int x, int y, int type) {
    if (type == 1) { // U D
        int x1 = x, x2 = x;
        while (mp[x1 - 1][y] == 1) --x1;
        while (mp[x2 + 1][y] == 1) ++x2;
        if (x1 == x2) { dfs(x, y, 3 - type); return; }
        for (int xx = x1; xx <= x2; ++xx) {
            mp[xx][y] = 3;
        }
        if ((x2 - x1 + 1) % 2 == 1) {
            mp[x2][y] = mp[x2 - 1][y] = mp[x2 - 2][y] = 5;
        }

        for (int xx = x1; xx <= x2; ++xx) {
            if (mp[xx][y - 1] == 1) dfs(xx, y - 1, type);
            if (mp[xx][y + 1] == 1) dfs(xx, y + 1, type);
        }
    } else {
        int y1 = y, y2 = y;
        while (mp[x][y1 - 1] == 1) --y1;
        while (mp[x][y2 + 1] == 1) ++y2;
        if (y1 == y2) { dfs(x, y, 3 - type); return; }
        for (int yy = y1; yy <= y2; ++yy) {
            mp[x][yy] = 2;
        }
        if ((y2 - y1 + 1) % 2 == 1) {
            mp[x][y2] = mp[x][y2 - 1] = mp[x][y2 - 2] = 4;
        }

        for (int yy = y1; yy <= y2; ++yy) {
            if (mp[x - 1][yy] == 1) dfs(x - 1, yy, type);
            if (mp[x + 1][yy] == 1) dfs(x + 1, yy, type);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    mp[0].resize(n + 2, ' ');
    for (int i = 1; i <= n; ++i) {
        cin >> mp[i];
        for (char &c : mp[i]) c -= '0';
        mp[i] = " " + mp[i] + " ";
    }
    mp[n + 1].resize(n + 2, ' ');


    int si = -1, sj = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mp[i][j] == 1) {
                int c = 0;
                if (mp[i - 1][j] == 1) ++c;
                if (mp[i + 1][j] == 1) ++c;
                if (mp[i][j - 1] == 1) ++c;
                if (mp[i][j + 1] == 1) ++c;
                if (c == 2) {
                    if (mp[i - 1][j] == mp[i + 1][j]) {
                        si = i, sj = j;
                        break;
                    }
                }
            }
        }
        if (si != -1) break;
    }

    if (si == -1) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (mp[i][j] == 1) {
                    si = i, sj = j;
                    break;
                }
            }
            if (si != -1) break;
        }
    }

    if (si != -1) {
        if (mp[si + 1][sj]) dfs(si, sj, 1);
        else dfs(si, sj, 2);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << (int)mp[i][j];
        }
        cout << '\n';
    }
}

