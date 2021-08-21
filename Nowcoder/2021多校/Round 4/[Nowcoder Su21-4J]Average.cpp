#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;
const double eps=1e-6;

int n,m,X,Y;
int a[MAXN+48],b[MAXN+48];
double tmp[MAXN+48];

double solve(int A[],int n,int lim)
{
    double l=0,r=1e5,mid,res;
    while (r-l>1e-8)
    {
        mid=(l+r)/2;
        rep(i,1,n) tmp[i]=(double)A[i]-mid;
        rep(i,2,n) tmp[i]+=tmp[i-1];
        bool f=false;double minn=0;
        rep(i,lim,n)
        {
            if (tmp[i]-minn>=eps) {f=true;break;}
            minn=min(minn,tmp[i-lim+1]);
        }
        if (f) res=mid,l=mid; else r=mid;
    }
    return res;
}

int main ()
{
    scanf("%d%d%d%d",&n,&m,&X,&Y);
    rep(i,1,n) scanf("%d",a+i);rep(i,1,m) scanf("%d",b+i);
    printf("%.7lf\n",solve(a,n,X)+solve(b,m,Y));return 0;
}