#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5, maxk = 5000 + 5;
int tp[maxn * maxk];
int b[maxn][maxk];

int main() {
    int d, s; cin >> d >> s;
    tp[0] = 1;
    for (int i = 1; i < maxn * maxk; ++i) tp[i] = tp[i - 1] * 10 % d;
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxk; ++j) b[i][j] = -1;
    }
    b[0][0] = 0;
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while (q.size()) {
        int x, y; tie(x, y) = q.front(); q.pop();
        for (int i = 0; i < 10; ++i) {
            if (y + i < maxk && b[(x * 10 + i) % d][y + i] == -1) {
                b[(x * 10 + i) % d][y + i] = b[x][y] + 1;
                q.emplace((x * 10 + i) % d, y + i);
            }
        }
    }
    if (b[0][s] == -1) {
        cout << "-1" << endl;
        return 0;
    }
    int r = 0, k = 0;
    string ans = "";
    for (int i = b[0][s]; i > 0; --i) {
        int c = -1;
        for (int j = 0; j < 10; ++j) {
            int tr = (r + j * tp[i - 1] % d) % d, tk = k + j;
            if (b[(d - tr) % d][s - tk] != -1 && b[(d - tr) % d][s - tk] <= i - 1) {
                c = j;
                break;
            }
        }
        ans += (char)(c + '0');
        (r += c * tp[i - 1]) %= d;
        k += c;
    }
    cout << ans << endl;
}
