#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* lc = nullptr;
    Node* rc = nullptr;
    int value;

    explicit Node(int v) : value(v) {}
};

Node* BuildTree(const vector<int>& A) {
    Node* nd = new Node(A[0]);
    for (int i = 1; i < A.size(); ++i) {
        Node** ptr = &nd;
        while (*ptr) {
            if (A[i] > (*ptr)->value) {
                ptr = &((*ptr)->rc);
            } else {
                ptr = &((*ptr)->lc);
            }
        }
        *ptr = new Node(A[i]);
    }
    return nd;
}

bool Equal(Node* x, Node* y) {
    if (x && !y) return false;
    if (y && !x) return false;
    if (!x && !y) return true;
    return Equal(x->lc, y->lc) && Equal(x->rc, y->rc);
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<Node*> tree(N);
    for (int i = 0; i < N; ++i) {
        vector<int> A(K);
        for (int j = 0; j < K; ++j) {
            cin >> A[j]; 
        }
        tree[i] = BuildTree(A);
    }
    vector<bool> used(N);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (used[i]) continue;
        ans++;
        for (int j = i + 1; j < N; ++j) {
            if (Equal(tree[i], tree[j])) {
                used[j] = true;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}

