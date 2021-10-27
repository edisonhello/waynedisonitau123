#include <bits/stdc++.h>
using namespace std;

const int digit[10] = {
    0b1110111,
    0b0100100,
    0b1011101,
    0b1101101,
    0b0101110,
    0b1101011,
    0b1111011,
    0b0100101,
    0b1111111,
    0b1101111,
};

int parse(vector<string> mp) {
    assert(mp.size() == 7u);
    int base_offset = 0;
    int parsed = 0;
    for (int offset : vector<int>{0, 5, 12, 17}) {
        int z = 0;
        if (mp[0][1 + offset] == 'X') z |= 1 << 0;
        if (mp[1][0 + offset] == 'X') z |= 1 << 1;
        if (mp[1][3 + offset] == 'X') z |= 1 << 2;
        if (mp[3][1 + offset] == 'X') z |= 1 << 3;
        if (mp[4][0 + offset] == 'X') z |= 1 << 4;
        if (mp[4][3 + offset] == 'X') z |= 1 << 5;
        if (mp[6][1 + offset] == 'X') z |= 1 << 6;
        parsed |= z << base_offset;
        base_offset += 7;
    }

    if (mp[2][10] == 'X') parsed |= 1 << 28;
    if (mp[4][10] == 'X') parsed |= 1 << 29;

    return parsed;
}

void output(vector<int> result) {
    vector<string> ans(7, string(21, '.'));

    auto print = [&] (int i, int j, int x) {
        ans[i][j] = 
            x == 0 ? '0' :
            x == 1 ? '1' :
            x == 2 ? 'W' : 
            '?';
    };

    int result_offset = 0;
    for (int offset : vector<int>{0, 5, 12, 17}) {
        print(0, 1 + offset, result[result_offset + 0]);
        print(0, 2 + offset, result[result_offset + 0]);
        print(1, 0 + offset, result[result_offset + 1]);
        print(2, 0 + offset, result[result_offset + 1]);
        print(1, 3 + offset, result[result_offset + 2]);
        print(2, 3 + offset, result[result_offset + 2]);
        print(3, 1 + offset, result[result_offset + 3]);
        print(3, 2 + offset, result[result_offset + 3]);
        print(4, 0 + offset, result[result_offset + 4]);
        print(5, 0 + offset, result[result_offset + 4]);
        print(4, 3 + offset, result[result_offset + 5]);
        print(5, 3 + offset, result[result_offset + 5]);
        print(6, 1 + offset, result[result_offset + 6]);
        print(6, 2 + offset, result[result_offset + 6]);
        result_offset += 7;
    }

    print(2, 10, result[28]);
    print(4, 10, result[29]);

    for (string s : ans) cout << s << endl;
}

int parse_time(int h, int m) {
    int z = 0;
    z |= h >= 10 ? digit[h / 10] : 0;
    z |= digit[h % 10] << 7;
    z |= digit[m / 10] << 14;
    z |= digit[m % 10] << 21;
    z |= 1 << 28;
    z |= 1 << 29;
    return z;
}

int main() {
    int n; cin >> n;
    
    vector<vector<string>> mp(n);
    for (int i = 0; i < n; ++i) {
        mp[i].resize(7);
        for (int j = 0; j < 7; ++j) cin >> mp[i][j];
    }

    vector<int> inp(n);
    for (int i = 0; i < n; ++i) {
        inp[i] = parse(mp[i]);
    }

    vector<int> all_time;
    for (int h = 0; h < 24; ++h) {
        for (int m = 0; m < 60; ++m) {
            all_time.push_back(parse_time(h, m));
        }
    }
    
    for (int i = 0; i < 24 * 60; ++i) all_time.push_back(all_time[i]);

    vector<vector<int>> results;
    for (int st = 0; st < 24 * 60; ++st) {
        bool impos = 0;
        vector<int> result;
        for (int y = 0; y < 30; ++y) {
            int all_light = 1;
            int all_dark = 1;
            for (int i = 0; i < n; ++i) {
                if (inp[i] & (1 << y)) all_dark = 0;
                else all_light = 0;
            }

            int req_light = 0;
            int req_dark = 0;
            for (int i = 0; i < n; ++i) {
                if (all_time[st + i] & (1 << y)) req_light = 1;
                else req_dark = 1;
            }

            if (all_light && req_dark) result.push_back(1);
            else if (all_light) result.push_back(-1);
            else if (all_dark && req_light) result.push_back(0);
            else if (all_dark) result.push_back(-1);
            else {
                int good = 1;
                for (int i = 0; i < n; ++i) {
                    if ((all_time[st + i] & (1 << y)) != (inp[i] & (1 << y))) good = 0;
                }
                if (!good) { impos = 1; break; }
                result.push_back(2);
            }
        }

        if (impos) continue;

        assert(result.size() == 30u);
        results.push_back(result);
    }

    if (results.empty()) {
        cout << "impossible" << endl;
        exit(0);
    }

    vector<int> result;
    for (int y = 0; y < 30; ++y) {
        int hasq = 0;
        // int has1 = 0;
        // int has0 = 0;
        int hasw = 0;
        for (int i = 0; i < (int)results.size(); ++i) {
            if (results[i][y] == 2) hasw = 1;
            else if (results[i][y] == -1) hasq = 1;
        }

        assert(hasq + hasw <= 1);
        if (hasq) result.push_back(-1);
        else if (hasw) result.push_back(2);
        else result.push_back(results[0][y]);
        // if (has0) result.push_back(0);
        // else if (has1) result.push_back(1);
        // else if (hasw) result.push_back(2);
        // else result.push_back(-1);
    }

    output(result);
}

