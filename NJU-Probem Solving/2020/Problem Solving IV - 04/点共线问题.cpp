#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define LD long double
using namespace std;

const int MAXN=1000;
const LD pi=acos(-1);

int n;
int X[MAXN+48],Y[MAXN+48];

unordered_map<LD,int> Mp;

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d%d",X+i,Y+i);
    int ans=1;
    rep(i,1,n)
    {
        Mp.clear();
        int cnt=0;
        rep(j,1,n)
        {
            if (X[i]==X[j] && Y[i]==Y[j]) {cnt++;continue;}
            LD ang=atan2(X[j]-X[i],Y[j]-Y[i]);
            if (ang<0) ang+=pi;
            Mp[ang]++;
        }
        int maxn=0;
        for (unordered_map<LD,int>::iterator iter=Mp.begin();iter!=Mp.end();iter++)
            maxn=max(maxn,iter->second);
        ans=max(ans,maxn+cnt);
    }
    printf("%d\n",ans);
    return 0;
}