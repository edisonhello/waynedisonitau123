#include <bits/stdc++.h>
using namespace std;

int n, m, k;
string s[55];
int djs[111];
int pel[111];
int tak[111];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }
bool C(int x, int y) { return F(x) == F(y); }

bool ok(string &a, string &b) {
    int z = 0;
    for (int i = 0; i < m; ++i) z += a[i] == b[i];
    return z >= k;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; ++i) cin >> s[i];
        for (int i = 0; i < 2 * n; ++i) djs[i] = i;
        for (int i = 0; i < 2 * n; ++i) pel[i] = tak[i] = 0;
        
        vector<int> li;

        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
            int pos = ok(s[i], s[j]);
            reverse(s[j].begin(), s[j].end());
            int neg = ok(s[i], s[j]);
            reverse(s[j].begin(), s[j].end());
            if (pos && neg) continue;
            else if (pos) {
                U(i, j); U(i + n, j + n);
            } else if (neg) {
                U(i, j + n); U(i + n, j);
            } else {
                // cerr << i << " " << j << " jizz" << endl;
                cout << -1 << '\n';
                goto over;
            }
        }

        for (int i = 0; i < n; ++i) if (F(i) == F(i + n)) {
            // cerr << i << " need self reverse" << endl;
            cout << -1 << '\n';
            goto over;
        }

        for (int i = n; i < 2 * n; ++i) ++pel[F(i)];
        for (int i = 0; i < n; ++i) {
            if (tak[F(i)] || tak[F(i + n)]) continue;
            if (pel[F(i)] < pel[F(i + n)]) tak[F(i)] = 1;
            else tak[F(i + n)] = 1;
        }

        for (int i = 0; i < n; ++i) if (tak[F(i + n)]) li.push_back(i + 1);

        cout << li.size() << endl;
        for (int i = 0; i < (int)li.size(); ++i) {
            if (i) cout << ' ';
            cout << li[i];
        }
        cout << endl;

over:;
    }
}
