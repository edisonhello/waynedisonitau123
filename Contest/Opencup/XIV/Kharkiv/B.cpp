#include <bits/stdc++.h>
using namespace std;
#define f128 __float128
#define i128 __int128

ostream& operator<< (ostream &o, i128 x) {
    bool tag = 0;
    if (x < 0) tag = 1, x = -x;
    stack<int> st;
    if (x == 0) st.push(0);
    while (x) {
        st.push(x % 10);
        x /= 10;
    }
    if (tag) o << "-";
    while (st.size()) o << st.top(), st.pop();
    return o;
}

f128 abs(f128 x) {
    return x >= 0 ? x : -x;
}

f128 pi = acos(-1);

f128 get_angle(f128 r, f128 l) {
    // return acos((long double)((r * r + r * r - l * l) / 2 / r / r));
    return 2 * asin((long double)(l / (2 * r)));
}

bool no_sol(vector<int> len) {
    sort(len.begin(), len.end());
    if (len[0] < 0) return true;
    long long sum = 0;
    for (int i = 0; i < (int)len.size() - 1; ++i) {
        sum += len[i];
    }
    if (sum <= len.back()) return true;
    return false;
}

int test(vector<int> len) {
    sort(len.begin(), len.end());
    f128 r = (f128)len.back() / 2;
    f128 totang = 0;
    for (int i = 0; i < (int)len.size() - 1; ++i) {
        totang += get_angle(r, len[i]);
    }
    if (totang < pi) return 1;
    return 0;
}

f128 pos[100005][2];
f128 ang[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> len(n);
    for (int i = 0; i < n; ++i) cin >> len[i];
    int mx = max_element(len.begin(), len.end()) - len.begin();
    if (no_sol(len)) {
        cout << "Impossible" << endl;
        exit(0);
    }
    int first_reverse = test(len);
    long long sum = 0;
    for (int i : len) sum += i;
    f128 L = (f128)len[mx] / 2, R = max(100 * sum, 1000000000ll);
    int cnt = 150;
    while (cnt--) {
        auto get_ans = [&] (f128 r) -> f128 {
            f128 totang = 0;
            for (int i = 0; i < (int)len.size(); ++i) {
                ang[i] = get_angle(r, len[i]);
            }
            if (first_reverse) ang[mx] = 2 * pi - ang[mx];
            for (int i = 0; i < (int)len.size(); ++i) totang += ang[i];
            return totang;
        };
        i128 LL = *(i128*)(&L), RR = *(i128*)(&R);
        i128 MM = LL + (RR - LL) / 2;
        f128 M = *(f128*)(&MM);
        f128 ang = get_ans(M);
        if (first_reverse) {
            if (ang > 2 * pi) R = M;
            else L = M;
        } else {
            if (ang > 2 * pi) L = M;
            else R = M;
        }
    }
    for (int i = 1; i < n; ++i) ang[i] += ang[i - 1];
    for (int i = 0; i < n; ++i) ang[i] = ang[i] / ang[n - 1] * (2 * pi);
    for (int i = n - 1; i > 0; --i) ang[i] = ang[i - 1]; ang[0] = 0;
    for (int i = 0; i < n; ++i) pos[i][0] = cos((long double)ang[i]) * L, pos[i][1] = sin((long double)ang[i]) * L;
    for (int i = 0; i < n; ++i) {
        assert(abs(pos[i][0]) <= 2e9 && abs(pos[i][1]) <= 2e9);
        cout << fixed << setprecision(10) << (long double)pos[i][0] << " " << (long double)pos[i][1] << '\n';
    }
    /* for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        cerr << fixed << setprecision(10) << (long double)hypot((long double)(pos[i][0] - pos[j][0]), (long double)(pos[i][1] - pos[j][1])) << '\n';
    }
    cerr << "R = " << (long double)L << endl; */
}
