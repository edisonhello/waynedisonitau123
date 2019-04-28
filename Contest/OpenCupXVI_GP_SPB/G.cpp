#include <bits/stdc++.h>
using namespace std;

vector<string> ans;

vector<vector<int>> apply_row(vector<vector<int>> &mp, vector<int> &permu) {
    vector<vector<int>> res(4, vector<int>(4));
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
        res[i][j] = mp[permu[i]][j];
    }
    return res;
}
vector<vector<int>> apply_col(vector<vector<int>> &mp, vector<int> &permu) {
    vector<vector<int>> res(4, vector<int>(4));
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
        res[i][j] = mp[i][permu[j]];
    }
    return res;
}

void add_row(vector<string> &cur, vector<int> permu) {
    vector<int> ori(4); iota(ori.begin(), ori.end(), 0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) if (i != j) {
            if (permu[i] == ori[j]) {
                swap(ori[i], ori[j]);
                char s[10] = {0};
                sprintf(s, "%c-%c", 'a' + i, 'a' + j);
                cur.push_back(s);
            }
        }
    }
}
void add_col(vector<string> &cur, vector<int> permu) {
    vector<int> ori(4); iota(ori.begin(), ori.end(), 0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) if (i != j) {
            if (permu[i] == ori[j]) {
                swap(ori[i], ori[j]);
                char s[10] = {0};
                sprintf(s, "%d-%d", 1 + i, 1 + j);
                cur.push_back(s);
            }
        }
    }
}
void add_swap(vector<string> &cur, int i, int j, int ii, int jj) {
    char s[10] = {0};
    sprintf(s, "%c%d-%c%d", 'a' + i, 1 + j, 'a' + ii, 1 + jj);
    cur.push_back(s);
}

void update_answer(vector<string> &cur) {
    if (cur.size() < ans.size()) ans = cur;
}

void check_answer(vector<vector<int>> mp, vector<int> &permu1, vector<int> &permu2) {
    vector<string> cur;
    add_row(cur, permu1);
    add_col(cur, permu2);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int w = (i * 4) + j;
            for (int ii = 0; ii < 4; ++ii) {
                for (int jj = 0; jj < 4; ++jj) if (ii != i || jj != j) {
                    if (mp[ii][jj] == w) {
                        swap(mp[i][j], mp[ii][jj]);
                        add_swap(cur, i, j, ii, jj);
                    }
                }
            }
        }
    }
    update_answer(cur);
}

int main() {
    for (int i = 0; i < 100; ++i) ans.push_back("");
    vector<vector<int>> mp(4, vector<int>(4, 0));
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) {
        int t; cin >> t; --t; mp[i][j] = t;
    }
    vector<int> permu(4); iota(permu.begin(), permu.end(), 0);
    do {
        vector<vector<int>> mp2 = apply_row(mp, permu);
        vector<int> permu2(4); iota(permu2.begin(), permu2.end(), 0);
        do {
            vector<vector<int>> mp3 = apply_col(mp2, permu2);
            check_answer(mp3, permu, permu2);
        } while (next_permutation(permu2.begin(), permu2.end()));
    } while (next_permutation(permu.begin(), permu.end()));
    cout << ans.size() << endl;
    for (string s : ans) cout << s << endl;
}
