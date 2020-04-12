#include <bits/stdc++.h>
using namespace std;

void NO() {
    cout << "NO" << endl;
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    vector<int> cnt(300, 0);
    for (char c : s) ++cnt[c];

    int n = s.size();
    if (n == 2) {
        if (*max_element(cnt.begin(), cnt.end()) == 2) {
            NO();
        }
    }
    if (*max_element(cnt.begin(), cnt.end()) <= 2) {
        cout << "YES" << endl;
        for (int i = 0; i < 300; ++i) while (cnt[i]--) {
            cout << char(i);
        }
        cout << endl;
        exit(0);
    }

    int x = max_element(cnt.begin(), cnt.end()) - cnt.begin();

    if (cnt[x] >= n - 1) NO();
    if (cnt[x] == n - 2) {
        for (int i = 0; i < 300; ++i) if (i != x && cnt[i] == 2) NO();
    }

    int othercnt = 0;
    for (int i = 0; i < 300; ++i) if (i != x) othercnt += cnt[i];

    cout << "YES" << endl;
    if (cnt[x] > othercnt) {
        for (int i = 1; i <= n / 2; ++i) cout << char(x);
        cnt[x] -= n / 2;
        for (int i = 0; i < 300; ++i) if (i != x && cnt[i] > 0) {
            --cnt[i];
            cout << char(i);
            break;
        }
        while (cnt[x]--) cout << char(x);
        for (int i = 0; i < 300; ++i) if (i != x) {
            while (cnt[i] > 0) cout << char(i), --cnt[i];
        }
        cout << endl;
    } else {
        int cc = 0;
        for (int i = 0; i < 300; ++i) if (i != x && cnt[i] > 0) {
            while (cnt[i] > 0 && cc < n / 2) {
                --cnt[i];
                cout << char(i);
                ++cc;
            }
        }
        cout << char(x);
        --cnt[x];
        for (int i = 0; i < 300; ++i) if (i != x && cnt[i] > 0) {
            while (cnt[i] > 0) {
                --cnt[i];
                cout << char(i);
            }
        }
        while (cnt[x] > 0) --cnt[x], cout << char(x);
        cout << endl;
    }
}

