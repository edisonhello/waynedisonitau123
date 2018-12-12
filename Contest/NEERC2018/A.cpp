#include<bits/stdc++.h>
using namespace std;

int a,b;

/* struct game{
    int awin,bwin;
    vector<pair<int,int>> gs;
    game():awin(0),bwin(0){}
} ans; */


void output(vector<pair<int,int>> ans){
    int aw=0,bw=0;
    for(auto p:ans)if(p.first>p.second)++aw; else ++bw;
    cout<<aw<<":"<<bw<<'\n';
    for(auto p:ans)cout<<p.first<<":"<<p.second<<" ";
    cout<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m; cin>>m; while(m--){
        cin>>a>>b;
        // ans=game();
        [&](){
            
        }();
        [&](){ // 3:0
            /* int amore=a-75,bmore=b;
            if(a<0 || b<0)return;
            vector<pair<int,int>> v;
            v.emplace_back(25,0);
            v.emplace_back(25,0);
            v.emplace_back(25,0);
            if(amore==0){
                if(bmore>23*3)return;
                for(int i=0;i<3;++i){
                    while(v[i].second<23){
                        if(bmore==0)break;
                        --bmore;
                        ++v[i].second;
                    }
                }
                output(v);
                return;
            }
            else{
                if(bmore<23)return;
                int add=min(23,bmore);
                bmore-=add;
                v[0].second+=bmore;
                int use_in_tie=min(amore,bmore);
                amore-=use_in_tie;
                bmore-=use_in_tie;
                if(amore>0)return;
                if(bmore>23*2)return;

            } */
        }();
        auto go=[&](vector<pair<int,int>> v)->bool{
            int aa=a,bb=b;
            for(auto p:v)aa-=p.first,bb-=p.second;
            if(aa<0 || bb<0)return 0;
            /* int alose=-1,blose=-1;
            for(int i=int(v.size())-1;i>=0;--i){
                if(v[i].first==0)alose=i;
                if(v[i].second==0)blose=i;
            } */
            int cantie=-1;
            if(aa>bb){
                for(int i=int(v.size())-1;i>=0;--i){
                    auto &p=v[i];
                // for(auto &p:v){
                    if(p.first==0){
                        while(aa>bb && p.first<p.second-2){
                            --aa;
                            ++p.first;
                        }
                        if(p.first==p.second-2)cantie=i;
                    }
                }
            }
            else if(aa<bb){
                for(int i=int(v.size())-1;i>=0;--i){
                    auto &p=v[i];
                // for(auto &p:v){
                    if(p.second==0){
                        while(aa<bb && p.second<p.first-2){
                            --bb;
                            ++p.second;
                        }
                        if(p.second==p.first-2)cantie=i;
                    }
                }
            }
            if(aa!=bb)return 0;
            if(aa==0)return output(v),1;
            // cout<<"initial cantie: "<<cantie<<endl;
            if(cantie!=-1){
                v[cantie].first+=aa;
                v[cantie].second+=aa;
                output(v);
                return 1;
            }
            while(aa && cantie==-1){
                    int aput=-1,bput=-1;
                    for(int i=0;i<int(v.size());++i){
                        auto &p=v[i];
                        if(p.second==(i==4?15:25)){
                            if(p.first<(i==4?13:23)){
                                aput=i;
                            }
                        }
                        if(p.first==(i==4?15:25)){
                            if(p.second<(i==4?13:23)){
                                bput=i;
                            }
                        }
                    }
                    if(aput==-1 || bput==-1)return 0;
                    --aa;
                    ++v[aput].first;
                    ++v[bput].second;
                    if(v[aput].first==v[aput].second-2)cantie=aput;
                    if(v[bput].second==v[bput].first-2)cantie=bput;
            }
            if(aa==0)return output(v),1;
            if(cantie!=-1){
                v[cantie].first+=aa;
                v[cantie].second+=aa;
                output(v);
                return 1;
            }
            return 0;
        };
        vector<pair<int,int>> v;
        v.emplace_back(25,0);
        v.emplace_back(25,0);
        v.emplace_back(25,0);
        if(go(v))continue;
        v.clear();
        v.emplace_back(25,0);
        v.emplace_back(25,0);
        v.emplace_back(0,25);
        v.emplace_back(25,0);
        if(go(v))continue;
        v.clear();
        v.emplace_back(25,0);
        v.emplace_back(25,0);
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        v.emplace_back(15,0);
        if(go(v))continue;
        v.clear();
        v.emplace_back(25,0);
        v.emplace_back(25,0);
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        v.emplace_back(0,15);
        if(go(v))continue;
        v.clear();
        v.emplace_back(25,0);
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        if(go(v))continue;
        v.clear();
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        v.emplace_back(0,25);
        if(go(v))continue;
        v.clear();
        cout<<"Impossible"<<'\n';
    }
}
