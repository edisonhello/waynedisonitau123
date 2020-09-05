#include <bits/stdc++.h>
using namespace std;
#define ll long long 

ll sign(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

pair<ll, ll> input(int x) {
    vector<ll> v(x);
    for (int i = 0; i < x; ++i) cin >> v[i];
    pair<ll, ll> cur(v.back(), 1);
    v.pop_back();
    while (v.size() >= 1u) {
        swap(cur.first, cur.second);
        cur.first += cur.second * v.back();
        v.pop_back();
    }
    return cur;
}

void output(pair<ll, ll> cur) {
    ll g = __gcd(cur.first, cur.second);
    cur.first /= g;
    cur.second /= g;

    if (cur.second < 0) {
        cur.first *= -1;
        cur.second *= -1;
    }

    ll a0 = cur.first / cur.second;
    if (sign(cur.first) * sign(cur.second) == -1) {
        if (cur.first % cur.second) --a0;
        cur.first -= cur.second * a0;
    } else {
        cur.first -= cur.second * a0;
    }
    cout << a0 << " ";

    while (true) {
        swap(cur.first, cur.second);
        if (cur.second == 0) {
            cout << endl;
            break;
        }
        ll x = cur.first / cur.second;
        cur.first -= cur.second * x;
        cout << x << " ";
    }
    
}

int main() {
    int T = 1;
    int n, m; while (cin >> n >> m, n) {
        pair<ll, ll> a = input(n);
        pair<ll, ll> b = input(m);

        cout << "Case " << (T++) << ":\n";
        pair<ll, ll> add = pair<ll, ll>(a.first * b.second + a.second * b.first, a.second * b.second);
        pair<ll, ll> sub = pair<ll, ll>(a.first * b.second - a.second * b.first, a.second * b.second);
        pair<ll, ll> mul = pair<ll, ll>(a.first * b.first, a.second * b.second);
        pair<ll, ll> div = pair<ll, ll>(a.first * b.second, a.second * b.first);

        output(add);
        output(sub);
        output(mul);
        output(div);
    }
}

