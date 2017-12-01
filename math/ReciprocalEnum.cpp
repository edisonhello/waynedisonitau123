vector<int> solve(int n) {
    vector<int> vec;
    for (int t = 1; t < n; t = (n / (n / (t + 1)))) vec.push_back(t);
    vec.push_back(n);
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    return vec;
}
