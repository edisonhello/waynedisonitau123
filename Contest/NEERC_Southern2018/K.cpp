#include<bits/stdc++.h>
using namespace std;

int a[100005],tot;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,k; cin>>n>>k;
    vector<int> gr;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        tot+=a[i];
    }
    if(tot%k){
        cout<<"No"<<endl;
        exit(0);
    }
    int ev=tot/k;
    int no=0,su=0;
    for(int i=1;i<=n;++i){
        if(su+a[i]>ev){
            cout<<"No"<<endl;
            exit(0);
        }
        if(su+a[i]==ev){
            su=0;
            gr.push_back(no+1);
            no=0;
        }
        else{
            ++no;
            su+=a[i];
        }
    }
    cout<<"Yes"<<endl;
    for(int i=0;i<int(gr.size())-1;++i){
        cout<<gr[i]<<" ";
    }
    cout<<gr.back()<<'\n';
}
