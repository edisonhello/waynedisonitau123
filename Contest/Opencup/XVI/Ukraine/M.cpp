#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> pol;
vector<long long> nmx;

long long pw(long long b, long long n, long long a = 1) {
    while (n) {
        if (n & 1) a = a * b;
        b = b * b; n >>= 1;
    } return a;
}

long long get_val(vector<long long> &v, long long x) {
    long long nx = 1;
    long long sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += nx * v[i];
        nx *= x;
    }
    return sum;
}
long double get_val_double(vector<long long> &v, long long x) {
    long double nx = 1;
    long double sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += nx * v[i];
        nx *= x;
    }
    return sum;
}

long long n;

long long cnt(long long val) { // how many terms < val
    long long ret = 0;
    for (int i = 0; i < (int)pol.size(); ++i) {
        long long L = 0, R = min(n, nmx[i]);
        while (L < R) {
            long long m = (L + R + 1) >> 1;
            if (get_val(pol[i], m) >= val) R = m - 1;
            else L = m;
        }
        ret += L;
        if (ret >= 100000000000000000) return ret;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        vector<long long> v(8, 0);
        for (int j = 7; j >= 0; --j) cin >> v[j];
        pol.push_back(v);
        long long L = 0, R = 100000000000000000;
        while (R > L) {
            long long m = (L + R + 1) >> 1;
            if (get_val_double(v, m) > 100000000000000000) R = m - 1;
            else L = m;
        }
        nmx.push_back(L);
    }
    cin >> n;
    long long L = 0, R = 100000000000000000;
    while (L < R) {
        long long m = (L + R + 1) / 2;
        if (cnt(m) >= n) R = m - 1;
        else L = m;
    }
    cout << L << endl;
}
