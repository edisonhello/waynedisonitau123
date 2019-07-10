#include <bits/stdc++.h>
using namespace std;

const int maxn = 18;
bool vs[maxn][1 << maxn];

bool walked[1 << maxn];
int main() {
    int n; scanf("%d", &n);
    vector<int> v = {0, 0};
    for (int i = 1; i < n; ++i) {
        int z = v.size();
        v.push_back(i);
        memset(walked, 0, sizeof(walked));
        walked[0] = 1;
        int now = 0;
        for (int j = 0; j < z; ++j) {
            v.push_back(v[j]);
            now ^= 1 << v[j];
            if (!walked[now]) {
                walked[now] = 1;
                v.push_back(i);
                v.push_back(i);
            }
        }
        v.push_back(i);
    }
    /* vector<int> u;
    for (int i = 0; i < (int)v.size(); ++i) {
        int j = (i + 1) % v.size();
        u.push_back(__builtin_ctz(v[i] ^ v[j]));
    }
    int z = u.size();
    for (int j = 1; j < n; ++j) {
        for (int k = 0; k < z; ++k) u.push_back((u[k] + j) % n);
    } */
    /* int s = 0;
    for (int i : v) {
        s ^= (1 << i);
        assert(!vs[i][s]);
        vs[i][s] = true;
    } */
    cout << v.size() << endl;
    for (int i : v) cout << i + 1 << " "; cout << endl;
}
