#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=1e5;

int n;
int a[MAXN+48],mark[MAXN+48],pt[MAXN+48];

template<typename T> T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
        memset(mark+1,0,n*sizeof(int));memset(pt+1,0,n*sizeof(int));
        rep(i,1,n) if (!mark[i])
        {
            mark[i]=i;int cur=a[i];
            for (;;)
                if (!mark[cur]) {mark[cur]=i;cur=a[cur];}
                else {if (mark[cur]==i) pt[i]=cur;break;}
        }
        LL a1=0,a2=0,c1,c2;bool f=true;
        rep(i,1,n) if (pt[i])
        {
            int st=pt[i],cur=a[st];c1=st;c2=1;
            while (cur!=st) c1+=cur,c2++,cur=a[cur];
            if (!a1) a1=c1,a2=c2;
            else {if (a1*c2!=a2*c1) f=false;}
        }
        if (f) puts("YES"); else puts("NO");
    }
}