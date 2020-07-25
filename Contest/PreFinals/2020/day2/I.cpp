#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
        exit(0);
    } if (n == 2) {
        cout << -1 << endl;
        exit(0);
    } if (n == 3) {
        cout << 3 << endl;
        cout << "1 3 2" << endl;
        cout << "2 3 1" << endl;
        cout << "3 1 2" << endl;
        exit(0);
    } if (n == 4) {
        cout << 3 << endl;
        cout << "4 3 1 2" << endl;
        cout << "1 4 2 3" << endl;
        cout << "2 4 1 3" << endl;
        exit(0);
    } if (n % 2) {
        vector<vector<int>> ans;
        for (int i = 1; i < n; i <<= 1) {
            vector<int> v;
            for (int j = 1; j <= n; ++j) v.push_back((j + i - 1) % n + 1);
            ans.push_back(v);
        }

        cout << ans.size() << endl;
        for (auto v : ans) {
            for (int i : v) cout << i << ' ';
            cout << endl;
        }
        exit(0);
    } 
    if (n % 4) {
        vector<vector<int>> ans;
        {
            vector<int> v = {2, 1, 5, 6, 4, 3};
            for (int i = 7; i <= n; i += 4) {
                v.push_back(i + 2);
                v.push_back(i + 3);
                v.push_back(i + 1);
                v.push_back(i);
            }
            ans.push_back(v);
        } {
            vector<int> v = {5, 6, 4, 3, 2, 1};
            for (int i = 7; i <= n; i += 4) {
                v.push_back(i + 2);
                v.push_back(i + 3);
                v.push_back(i + 1);
                v.push_back(i);
            }
            ans.push_back(v);
        }

        for (int i = 2; i < n; i <<= 1) {
            vector<int> v;
            for (int j = 1; j <= n; ++j) v.push_back((j + i - 1) % n + 1);
            ans.push_back(v);
        }

        cout << ans.size() << endl;
        for (auto v : ans) {
            for (int i : v) cout << i << ' ';
            cout << endl;
        }
        exit(0);
    } {
        vector<vector<int>> ans;
        {
            vector<int> v;
            for (int i = 1; i <= n; i += 4) {
                v.push_back(i + 2);
                v.push_back(i + 3);
                v.push_back(i + 1);
                v.push_back(i);
            }
            ans.push_back(v);
        }
        for (int i = 1; i < n; i <<= 1) {
            vector<int> v;
            for (int j = 1; j <= n; ++j) v.push_back((j + i - 1) % n + 1);
            ans.push_back(v);
        }

        cout << ans.size() << endl;
        for (auto v : ans) {
            for (int i : v) cout << i << ' ';
            cout << endl;
        }
        exit(0);
    }
}

