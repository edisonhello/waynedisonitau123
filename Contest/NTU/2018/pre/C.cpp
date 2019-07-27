#include <bits/stdc++.h>
using namespace std;

const int maxc = 1e7 + 1;
vector<int> pr;
bitset<maxc> v;

void sieve() {
    for (int i = 2; i < maxc; ++i) {
        if (!v[i]) pr.push_back(i);
        for (int j = 0; i * pr[j] < maxc; ++j) {
            v[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
}

int main() {
    sieve();
    int n; cin>>n;
    long long ans=0;
    for(int j=0;j<int(pr.size());++j){
        if(pr[j]>n)break;
        int py=pr[j];
        ans+=1ll*(n/py)*j;
    }
    cout<<ans*2<<endl;
}
