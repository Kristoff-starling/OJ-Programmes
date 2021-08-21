#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,x1,y1,x2,y2,x3,y3;
double L,d,pw[10048];

int main ()
{
    int ca;scanf("%d",&ca);
    pw[0]=1;rep(i,1,10000) pw[i]=pw[i-1]/2;
    while (ca--)
    {
        scanf("%d",&n);scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
        L=abs(y1-y2);d=abs(x2-x3);n--;
        double ans=d*L/2*(4*n-6)+d*L*3*pw[n];
        printf("%.3lf\n",ans);
    }
    return 0;
}