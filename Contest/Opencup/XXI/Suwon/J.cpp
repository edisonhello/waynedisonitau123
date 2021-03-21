#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    sort(A.begin(), A.end());
    int ans = -1;
    vector<pair<int, int>> B;
    for (int i = 0; i + 1 < N; ++i) B.emplace_back(A[i + 1] - A[i], i); 
    sort(B.begin(), B.end());
    set<pair<int, int>> s;
    for (int i = 0, j = 0; i + 7 <= N; ++i) {
        int x = A[i] + A[i + 1] + A[i + 2] + A[i + 3];
        int y = A[i + 4];
        while (j < B.size() && B[j].first < y) {
            s.insert(make_pair(A[B[j].second], B[j].second));
            j++;
        }
        auto it = s.lower_bound(make_pair(x - y, -1));
        if (it != s.begin()) {
            int p = prev(it)->second;
            if (p > i + 4 && y + A[p] < x) {
                int q = p;
                for (int d = 20; d >= 0; --d) {
                    if (q + (1 << d) < N && A[q + (1 << d)] < y + A[p])
                        q += (1 << d);
                }
                assert(q > p);
                ans = max(ans, x + y + A[p] + A[q]);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}

