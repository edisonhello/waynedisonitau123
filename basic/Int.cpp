#include <bits/stdc++.h>

struct Int {
    static const int inf = 1e9;
    std::vector<int> dig;
    bool sgn;
    Int() {
        dig.push_back(0);
        sgn = true;
    }
    Int(int n) {
        sgn = n >= 0;
        while (n) {
            dig.push_back(n % 10);
            n /= 10;
        }
        if (dig.size() == 0) dig.push_back(0);
    }
    Int(std::string s) {
        int i = 0; sgn = true;
        if (s[i] == '-') sgn = false, ++i;
        for (;i < s.length(); ++i) dig.push_back(s[i] - '0');
        reverse(dig.begin(), dig.end());
        if (dig.size() == 1 && dig[0] == '0') sgn = true;
    }
    Int(const std::vector<int>& d, const bool& s = true) {
        dig = std::vector<int>(d.begin(), d.end());
        sgn = s;
    }
    Int(const Int& n) {
        sgn = n.sgn;
        dig = n.dig;
    }
    bool operator<(const Int& rhs) const {
        if (sgn && !rhs.sgn) return true;
        if (!sgn && rhs.sgn) return false;
        if (!sgn && !rhs.sgn) return Int(dig) > Int(rhs.dig);
        if (dig.size() < rhs.dig.size()) return true;
        if (dig.size() > rhs.dig.size()) return false;
        for (int i = dig.size() - 1; i >= 0; --i) {
            if (dig[i] != rhs.dig[i]) return dig[i] < rhs.dig[i];
        }
        return false;
    }
    bool operator==(const Int& rhs) const {
        if (sgn != rhs.sgn) return false;
        return dig == rhs.dig;
    }
    bool operator>(const Int& rhs) const {
        return !(*this < rhs) && !(*this == rhs);
    }
    bool operator<(const int& n) const {
        return *this < Int(n);
    }
    bool operator>(const int& n) const {
        return *this > Int(n);
    }
    bool operator==(const int& n) const {
        return *this == Int(n);
    }
    Int operator-() const {
        return Int(dig, !sgn);
    }
    Int operator+(const Int& rhs) const {
        bool res = true;
        if (!sgn && !rhs.sgn) res = false;
        else if (!sgn && rhs.sgn) return rhs - (-*this);
        else if (sgn && !rhs.sgn) return *this - -rhs;
        std::vector<int> v1 = dig, v2 = rhs.dig;
        if (v2.size() > v1.size()) swap(v1, v2);
        int car = 0;
        std::vector<int> nvec;
        for (int i = 0; i < v2.size(); ++i) {
            int k = v1[i] + v2[i] + car;
            nvec.push_back(k % 10);
            car = k / 10;
        }
        for (int i = v2.size(); i < v1.size(); ++i) {
            int k = v1[i] + car;
            nvec.push_back(k % 10);
            car = k / 10;
        }
        return Int(nvec, res);
    }
    Int operator-(const Int& rhs) const {
        if (*this < rhs) {
            std::vector<int> nvec = (rhs - *this).dig;
            return Int(nvec, false);
        }
        if (*this == rhs) return Int(0);
        std::vector<int> v1 = dig, v2 = rhs.dig;
        std::vector<int> nvec;
        for (int i = 0; i < v2.size(); ++i) {
            int k = v1[i] - v2[i];
            if (k < 0) {
                for (int j = i + 1; j < v1.size(); ++j) if (v1[j] > 0) {
                    --v1[j]; k += 10;
                    break;
                }
            }
            nvec.push_back(k);
        }
        int rind = v1.size() - 1;
        while (rind >= v2.size() && v1[rind] == 0) --rind;
        for (int i = v2.size(); i <= rind; ++i) {
            nvec.push_back(v1[i]);
        }
        return Int(nvec);
    }
    Int operator*(const Int& rhs) const {
        if (sgn && !rhs.sgn || !sgn && rhs.sgn) return -(Int(dig, true) * Int(rhs.dig, true));
        if (*this == 0) return Int();
        if (rhs == 0) return Int();
        std::vector<int> v1 = dig, v2 = rhs.dig;
        if (v1.size() < v2.size()) swap(v1, v2);
        std::vector<int> res(v1.size() * v2.size(), 0);
        for (int i = 0; i < v2.size(); ++i) {
            int car = 0;
            for (int j = 0; j < v1.size(); ++j) {
                int k = car + v1[j] * v2[i];
                res[j + i] += k % 10;
                car = k / 10;
            }
        }
        int car = 0;
        for (int i = 0; i < res.size(); ++i) {
            int k = car + res[i];
            res[i] = k % 10;
            car = k / 10;
        }
        while (car) {
            res.push_back(car % 10);
            car /= 10;
        }
        int ind = res.size() - 1;
        while (ind >= 0 && res[ind] == 0) --ind;
        std::vector<int> nvec;
        for (int i = 0; i <= ind; ++i) nvec.push_back(res[i]);
        return Int(nvec);
    }
    Int operator+(const int& n) const {
        return *this + Int(n);
    }
    Int operator-(const int& n) const {
        return *this - Int(n);
    }
    Int& operator+=(const Int& n) {
        *this = (*this + n);
        return *this;
    }
    Int& operator-=(const Int& n) {
        *this = (*this - n);
        return *this;
    }
    Int& operator+=(const int& n) {
        *this += Int(n);
        return *this;
    }
    Int& operator-=(const int& n) {
        *this -= Int(n);
        return *this;
    }
    Int& operator*=(const Int& n) {
        *this = *this * n;
        return *this;
    }
    Int& operator*=(const int& n) {
        *this *= Int(n);
        return *this;
    }
    Int& operator++(int) {
        *this += 1;
        return *this;
    }
    Int& operator--(int) {
        *this -= 1;
        return *this;
    }
    friend std::istream& operator>>(std::istream& in, Int& n) {
        std::string s; in >> s;
        n = Int(s);
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Int& n) {
        if (!n.sgn) out << "-";
        for (int i = n.dig.size() - 1; i >= 0; --i) out << n.dig[i];
        return out;
    }
};
