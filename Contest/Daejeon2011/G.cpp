#include<bits/stdc++.h>
using namespace std;

pair<int,int> a[100005];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        int n; cin>>n;
        for(int i=0;i<n;++i)cin>>a[i].first>>a[i].second;
        for(int i=0;i<n;++i)--a[i].second;
        sort(a,a+n,[&](const pair<int,int> &a,const pair<int,int> &b){ return a.second==b.second?a.first<b.first:a.second<b.second; });
        int ans=-1;
        int head=-1e9,end=-1e8;
        for(int i=0;i<n;++i){
            if(a[i].first<=end+1){
                if(end+1<=a[i].second){
                    ++end;
                }
                else{
                    --head;
                }
            }
            else{
                ++ans;
                head=a[i].second;
                end=a[i].second;
            }
            // cout<<i<<" "<<ans<<" "<<head<<" "<<end<<endl;
        }
        cout<<ans<<endl;
    }
}
