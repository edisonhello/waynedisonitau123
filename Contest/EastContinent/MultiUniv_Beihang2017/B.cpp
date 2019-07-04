#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1000000007;
 
string s[100005];
vector<int> pos[26];
// int pw[26][100005];
int pw[100005];
bool ban[26];
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // for (int i = 1; i < 26; ++i) pw[i][0] = 1;
    // for (int i = 1; i < 26; ++i) for (int j = 1; j < 100005; ++j) pw[i][j] = 1ll * pw[i][j - 1] * i % mod;
    pw[0] = 1;
    for (int i = 1; i < 100005; ++i) pw[i] = pw[i - 1] * 26ll % mod;
    int n, T = 0; while (cin >> n) {
        memset(ban, 0, sizeof(ban));
        cout << "Case #" << (++T) << ": ";
        for (int i = 0; i < n; ++i) cin >> s[i];
        for (int i = 0; i < n; ++i) reverse(s[i].begin(), s[i].end());
        for (int i = 0; i < n; ++i) for (char &c : s[i]) c -= 'a';
        int mxl = 0;
        for (int i = 0; i < n; ++i) mxl = max(mxl, (int)s[i].size());
        for (int i = 0; i < 26; ++i) pos[i] = vector<int>(mxl + 5, 0);
        for (int i = 0; i < n; ++i) for (int j = 0; j < (int)s[i].size(); ++j) {
            ++pos[s[i][j]][j];
        }
        for (int i = 0; i < n; ++i) {
            if (s[i].size() > 1u) {
                ban[s[i].back()] = 1;
            }
        }
        for (int i = 0; i < 26; ++i) for (int j = 0; j < (int)pos[i].size(); ++j) {
            if (pos[i][j] >= 26) {
                pos[i][j + 1] += pos[i][j] / 26;
                pos[i][j] %= 26;
            }
        }
        vector<int> id(26); iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](const int &a, const int &b) -> bool {
            for (int i = (int)pos[a].size() - 1; i >= 0; --i) {
                if (pos[a][i] != pos[b][i]) return pos[a][i] < pos[b][i];
            }
            return false;
        });
        // cerr << "ban: "; for (int i = 0; i < 26; ++i) cerr << ban[i] << " "; cerr << endl;
        // cerr << "id: "; for (int i : id) cerr << i << " "; cerr << endl;
        for (int i = 0; i < 26; ++i) if (!ban[id[i]]) {
            int oo = id[i];
            for (int j = i; j > 0; --j) id[j] = id[j - 1];
            id[0] = oo;
            break;
        }
        // cerr << "id: "; for (int i : id) cerr << i << " "; cerr << endl;
        long long ans = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < (int)pos[id[i]].size(); ++j) {
                ans += 1ll * i * pw[j] % mod * pos[id[i]][j] % mod;
            }
        }
        cout << ans % mod << endl;
    }
}
