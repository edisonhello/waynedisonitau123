#include<bits/stdc++.h>
using namespace std;


int main(){
#ifdef ONLINE_JUDGE
    freopen("embedding.in", "r", stdin);
    freopen("embedding.out", "w", stdout);
#endif
    int n; while(cin>>n,n){
        n*=2;
        if(n==6){
            cout<<"1 2 3 4 5 6"<<endl;
            cout<<"1 4 5 3 2 6"<<endl;
            cout<<"2 6 1 3 4 5"<<endl;
        }
        /* else if(n==8){
            cout<<"1 3 6 4 7 5 8 2"<<endl;
            cout<<"3 8 5 1 4 7 2 6"<<endl;
            cout<<"1 2 3 4 5 6 7 8"<<endl;
        } */
        /* else if(n==10){
            cout<<"1 2 3 4 5 6 7 8 9 10"<<endl;
            cout<<"1 7 8 9 10 6 5 4 3 2"<<endl;
            cout<<"1 3 5 2 4 6 8 9 10 7"<<endl;
        } */
        else{
            vector<int> r1(n),r2(n),r3(n);
            iota(r1.begin(),r1.end(),1);
            iota(r2.begin(),r2.end(),1);
            iota(r3.begin(),r3.end(),1);
            auto pr=[&](int i,int j)->pair<int,int>{
                if(i>j)swap(i,j);
                return make_pair(i,j);
            };
            set<pair<int,int>> st;
            do{
                st.clear();
                random_shuffle(r1.begin(),r1.end());
                random_shuffle(r2.begin(),r2.end());
                random_shuffle(r3.begin(),r3.end());
                for(int i=0;i<n/2;++i){
                    st.insert(pr(r1[i],r1[i+1]));
                    st.insert(pr(r2[i],r2[i+1]));
                    st.insert(pr(r3[i],r3[i+1]));
                }
                for(int i=1;i<n/2;++i){
                    st.insert(pr(r1[i],r1[i+n/2]));
                    st.insert(pr(r2[i],r2[i+n/2]));
                    st.insert(pr(r3[i],r3[i+n/2]));
                }
            }while(int(st.size())!=3*(n-1));
            for(int i:r1)cout<<i<<" "; cout<<endl;
            for(int i:r2)cout<<i<<" "; cout<<endl;
            for(int i:r3)cout<<i<<" "; cout<<endl;
        }
    }
}
