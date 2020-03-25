#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

int main() {
    string n; cin >> n;
    long long sum = 0;
    long long curn = 0;
    for (int i = 0; i < (int)n.size(); ++i) {
        curn = curn * 10 + (n[i] - '0');
        curn %= mod;
        if (i == (int)n.size() - 2) {
            sum += curn * 7;
            sum %= mod;
        } else if (i == (int)n.size() - 1) {

        } else {
            sum += curn * 9;
            sum %= mod;
        }
    }
    sum += curn;
    --sum;
    sum = (sum % mod + mod) % mod;
    cout << sum << endl;
}

