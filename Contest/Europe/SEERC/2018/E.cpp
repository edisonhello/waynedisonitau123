#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second

int n,m,l; 
pair<int,int> f[200005];
struct fisher{
    int x,i,ans;
} a[200005];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m>>l;
    for(int i=0;i<n;++i)cin>>f[i].x>>f[i].y;
    for(int i=0;i<m;++i){
        a[i].i=i;
        cin>>a[i].x;
    }
    sort(f,f+n);
    sort(a,a+m,[&](const fisher &a,const fisher &b){ return a.x<b.x; });
    {
        int it=n-1;
        priority_queue<int,vector<int>,less<int>> pq;
        for(int i=m-1;i>=0;--i){
            while(it>=0 && f[it].x>=a[i].x)pq.push(f[it].x+f[it].y),--it;
            while(pq.size() && pq.top()>a[i].x+l)pq.pop();
            a[i].ans+=pq.size();
        }
    }
    {
        int it=0;
        priority_queue<int,vector<int>,greater<int>> pq;
        for(int i=0;i<m;++i){
            while(it<n && f[it].x<a[i].x)pq.push(f[it].x-f[it].y),++it;
            while(pq.size() && pq.top()<a[i].x-l)pq.pop();
            a[i].ans+=pq.size();
        }
    }
    sort(a,a+m,[&](const fisher &a,const fisher &b){ return a.i<b.i; });
    for(int i=0;i<m;++i)cout<<a[i].ans<<'\n';
}
