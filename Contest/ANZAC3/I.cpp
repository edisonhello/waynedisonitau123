#include <bits/stdc++.h>
using namespace std;

long long f(long long n, long long m) {
    if (n == 1) return 0;
    if (m > (n - 1) * 1ll * (n - 2) / 2) {
        return f(n - 1, 1ll * (n - 1) * (n - 2) / 2) + 1ll * (n - 1) * (n - 2) / 2 + 1;
    } else return f(n - 1, m - 1) + m;
}

int main (){
    long long n, m; cin >> n >> m;
    cout << f(n, m) << endl;
}
