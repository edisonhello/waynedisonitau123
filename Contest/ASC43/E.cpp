

#include<bits/stdc++.h>
using namespace std;

int a[155];
double b[155];
pair<int,int> p[155];

int main(){
#ifdef ONLINE_JUDGE
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,s; while(cin>>n>>s,n){
        for(int i=1;i<=n;++i)cin>>a[i];
        int L,U; cin>>L>>U;
        double t=0;
        for(int i=1;i<=n;++i)t+=double(1)/a[i];
        for(int i=1;i<=n;++i)b[i]=double(s)/t/a[i];
        long long totp=0;
        for(int i=1;i<=n;++i){
            p[i].second=i;
            p[i].first=round(b[i]);
            p[i].first=max(p[i].first,L);
            p[i].first=min(p[i].first,U);
            totp+=p[i].first;
            // cout<<"initial p["<<i<<"] = "<<p[i].first<<endl;
        }
        if(totp<s){
            // cout<<"totp: "<<totp<<endl;
            sort(p+1,p+1+n,[&](const pair<int,int> &a,const pair<int,int> &r){ return make_pair(a.first-b[a.second],a.second)<make_pair(r.first-b[r.second],r.second); });
            int st=1;
            while(totp<s){
                int ADDL=0,ADDR=U-p[st].first;
                while(ADDL<ADDR){
                    int ADD=(ADDL+ADDR+1)>>1;
                    double all_less=(p[st].first-b[p[st].second]+ADD-1);
                    long long deltatot=ADD;
                    for(int i=st+1;i<=n;++i){
                        if((p[i].first-b[p[i].second])>=all_less)break;
                        int MYADD=int(all_less-(p[i].first-b[p[i].second]))+1;
                        MYADD=min(MYADD,U-p[i].first);
                        MYADD=max(MYADD,0);
                        deltatot+=MYADD;
                    }
                    // cout<<"when ADD: "<<ADD<<" , deltatot: "<<deltatot<<endl;
                    if(deltatot+totp<=s)ADDL=ADD;
                    else ADDR=ADD-1;
                }
                // cout<<"ADDL ADDR: "<<ADDL<<" "<<ADDR<<endl;
                int ADD=ADDL;
                double all_less=(p[st].first-b[p[st].second]+ADD-1);
                p[st].first+=ADD;
                totp+=ADD;
                for(int i=st+1;i<=n;++i){
                    if((p[i].first-b[p[i].second])>=all_less)break;
                    int MYADD=int(all_less-(p[i].first-b[p[i].second]))+1;
                    MYADD=min(MYADD,U-p[i].first);
                    MYADD=max(MYADD,0);
                    p[i].first+=MYADD;
                    totp+=MYADD;
                }
                ++st;
                sort(p+st,p+1+n,[&](const pair<int,int> &a,const pair<int,int> &r){ return make_pair(a.first-b[a.second],a.second)<make_pair(r.first-b[r.second],r.second); });
                // cout<<"now totp: "<<totp<<" , current ps: "; for(int i=1;i<=n;++i)cout<<p[i].first<<"("<<b[p[i].second]<<") "; cout<<endl;
                // cout<<"-------------"<<endl;
            }
        }
        else{
            sort(p+1,p+1+n,[&](const pair<int,int> &a,const pair<int,int> &r){ return make_pair(a.first-b[a.second],a.second)>make_pair(r.first-b[r.second],r.second); });
            // cout<<"init totp: "<<totp<<" , current ps: "; for(int i=1;i<=n;++i)cout<<p[i].first<<"("<<b[p[i].second]<<") "; cout<<endl;
            int st=1;
            while(totp>s){
                int DECL=0,DECR=p[st].first-L;
                while(DECL<DECR){
                    int DEC=(DECL+DECR+1)>>1;
                    double all_less=(b[p[st].second]-p[st].first+DEC-1);
                    long long deltatot=DEC;
                    for(int i=st+1;i<=n;++i){
                        if((b[p[i].second]-p[i].first)>=all_less)break;
                        int MYDEC=int(all_less-(b[p[i].second]-p[i].first))+1;
                        MYDEC=min(MYDEC,p[i].first-L);
                        MYDEC=max(MYDEC,0);
                        deltatot+=MYDEC;
                        // cout<<"MYDEC of "<<i<<" is "<<MYDEC<<endl;
                    }
                    // cout<<"when DEC: "<<DEC<<" , deltatot: "<<deltatot<<endl;
                    if(totp-deltatot>=s)DECL=DEC;
                    else DECR=DEC-1;
                }
                // cout<<"DECL DECR: "<<DECL<<" "<<DECR<<endl;
                int DEC=DECL;
                double all_less=((b[p[st].second]-p[st].first)+DEC-1);
                p[st].first-=DEC;
                totp-=DEC;
                for(int i=st+1;i<=n;++i){
                    if((b[p[i].second]-p[i].first)>=all_less)break;
                    int MYDEC=int(all_less-(b[p[i].second]-p[i].first))+1;
                    MYDEC=min(MYDEC,p[i].first-L);
                    MYDEC=max(MYDEC,0);
                    p[i].first-=MYDEC;
                    totp-=MYDEC;
                    // cout<<"MYDEC of "<<i<<" is "<<MYDEC<<endl;
                }
                ++st;
                sort(p+st,p+1+n,[&](const pair<int,int> &a,const pair<int,int> &r){ return make_pair(a.first-b[a.second],a.second)>make_pair(r.first-b[r.second],r.second); });
                // cout<<"now totp: "<<totp<<" , current ps: "; for(int i=1;i<=n;++i)cout<<p[i].first<<"("<<b[p[i].second]<<") "; cout<<endl;
                // cout<<"-------------"<<endl;
            }
        }
        sort(p+1,p+1+n,[&](const pair<int,int> &a,const pair<int,int> &b){ return a.second<b.second; });
        for(int i=1;i<=n;++i)cout<<p[i].first<<" "; cout<<'\n';
    }
}
