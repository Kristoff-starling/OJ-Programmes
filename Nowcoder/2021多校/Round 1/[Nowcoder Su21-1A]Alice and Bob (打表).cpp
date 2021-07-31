#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int X[5001],Y[5001],tot;

int main ()
{
    tot=1;X[1]=0;Y[1]=0;
    rep(i,1,5000)
    {
        bool f=false;
        rep(j,i,5000)
        {
            if (f) continue;
            bool ff=false;
            rep(k,1,tot)
            {
                if (i>=X[k] && j>=Y[k])
                {
                    int d1=i-X[k],d2=j-Y[k];
                    if (d1>d2) swap(d1,d2);
                    if (d1==0 || d2%d1==0) {ff=true;break;}
                }
                if (j>=X[k] && i>=Y[k])
                {
                    int d1=j-X[k],d2=i-Y[k];
                    if (d1>d2) swap(d1,d2);
                    if (d1==0 || d2%d1==0) {ff=true;break;}
                }
            }
            if (!ff)
            {
                ++tot;
                X[tot]=i;Y[tot]=j;
                f=true;
            }
        }
    }
    rep(i,1,tot) cout<<X[i]<<","<<Y[i]<<endl;
    return 0;
}