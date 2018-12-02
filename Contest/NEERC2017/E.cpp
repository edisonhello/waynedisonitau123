#include<bits/stdc++.h>
using namespace std;



int main(){
    int n; cin>>n;
    queue<int> q;
    queue<int> ans;
    multiset<int> st;
    while(n--){
        int x; cin>>x; 
        if(x==0){
            q.push(x);
        }
        else if(x>0){
            st.insert(x);
        }
        else{
            if(st.count(-x)){
                st.erase(st.find(-x));
            }
            else{
                if(q.empty()){
                    cout<<"No"<<endl;
                    exit(0);
                }
                ans.push(-x);
                q.pop();
            }
        }
    }
    cout<<"Yes"<<endl;
    while(ans.size()){
        cout<<ans.front()<<" ";
        ans.pop();
    }
    while(q.size()){
        cout<<"1"<<" ";
        q.pop();
    }
    cout<<endl;
}
