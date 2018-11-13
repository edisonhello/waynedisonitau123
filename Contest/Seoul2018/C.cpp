#include<bits/stdc++.h>
using namespace std;


int r[1005],pos[1005],x[1005];
double sqrtr[1005];
// double pos[1005];

int main(){
    int n; cin>>n;
    for(int i=1;i<=n;++i)cin>>r[i];
    sort(r+1,r+1+n);
    for(int i=1;i<=n;++i)sqrtr[i]=sqrt(r[i]);
    double mx=0;
    for(int z=1;z<=n;++z){
        pos[1]=z;
        if(z==1){
            pos[n]=2;
            int ll=2,rr=n-1;
            for(int x=3;x<=n;++x){
                pos[ll++]=x++;
                if(x>n)break;
                pos[rr--]=x;
            }
            // cout<<"here"<<endl;
        }
        else if(z==n){
            pos[n]=n-1;
            int ll=2,rr=n-1;
            for(int x=n-2;x>=1;--x){
                pos[ll++]=x--;
                if(x<1)break;
                pos[rr--]=x;
            }
        }
        else{
            pos[n]=z-1;
            pos[n-1]=z+1;
            int nl=2,nr=n-2;
            int l=z-2,r=z+2;
            bool small=1;
            while(l!=0 && r!=n+1){
                if(small){
                    if(pos[nr+2]==l+1){
                        pos[nl++]=l--;
                        pos[nl++]=r++;
                    }
                    else{
                        pos[nl++]=r++;
                        pos[nl++]=l--;
                    }
                }
                else{ // put big
                    if(pos[nl-2]==l+1){
                        pos[nr--]=l--;
                        pos[nr--]=r++;
                    }
                    else{
                        pos[nr--]=r++;
                        pos[nr--]=l--;
                    }
                }
                small=!small;
            }
            while(l!=0){
                if(small){
                    pos[nl++]=l--;
                }
                else{
                    pos[nr--]=l--;
                }
                small=!small;
            }
            while(r!=n+1){
                if(small){
                    pos[nl++]=r++;
                }
                else{
                    pos[nr--]=r++;
                }
                small=!small;
            }
        }
        for(int i=1;i<=n;++i)x[pos[i]]=i;
        // for(int i=1;i<=n;++i)cout<<x[i]<<" "; cout<endl;
        double cur=0;
#define sq(x) ((x)*(x))
        for(int i=2;i<=n;++i){
            // cout<<"sq of "<<sqrtr[x[i-1]]<<" - "<<sqrtr[x[i]]<<endl;
            cur+=sq(sqrtr[x[i-1]]-sqrtr[x[i]]);
        }
        mx=max(mx,cur);
    }
    // cout<<mx<<endl;
    double sigmar=0;
    for(int i=1;i<=n;++i)sigmar+=r[i];
    cout<<fixed<<setprecision(20)<<2*sigmar-mx<<endl;
    /* for(int i=2;i<=n;++i){
        double mx=-1;
        for(int j=1;j<i;++j){
            mx=max(mx,(2*pos[j]+sqrt(4*pos[j]*pos[j]-4*(pos[j]*pos[j]-4*r[i]*r[j])))/2);
        }
        pos[i]=mx;
    } */
    // cout<<pos[n]+r[1]+r[n]<<endl;
}
