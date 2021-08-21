#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=5000;

int n,b[MAXN+48];

struct node
{
    int val,id;
    void input(int _id) {scanf("%d",&val);id=_id;}
    bool operator < (const node &other) const {return val>other.val;}
}a[MAXN+48];

int ans1[MAXN+48],ans2[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) a[i].input(i);rep(i,1,n) scanf("%d",b+i);
        sort(a+1,a+n+1);sort(b+1,b+n+1);int cnt,pt;
        rep(i,1,n)
        {
            int s=a[i].val+b[n];cnt=0;pt=n-1;
            REP(j,n,1)
            {
                if (j==i) continue;
                while (pt>=1 && a[j].val+b[pt]>s) pt--;
                if (pt>=1) cnt++,pt--;
            }
            ans1[a[i].id]=n-cnt;
            s=a[i].val+b[1];cnt=0;pt=2;
            rep(j,1,n)
            {
                if (j==i) continue;
                while (pt<=n && a[j].val+b[pt]<=s) pt++;
                if (pt<=n) cnt++,pt++;
            }
            ans2[a[i].id]=cnt+1;
        }
        rep(i,1,n) printf("%d %d\n",ans1[i],ans2[i]);
    }
    return 0;
}