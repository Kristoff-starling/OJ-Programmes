#include <bits/stdc++.h>
#define Pair pair<int,int> 
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;

int n;
Pair q[MAXN+48];int head,tail;


int main ()
{
    scanf("%d",&n);int op,x,c;head=1;tail=0;
    while (n--)
    {
        scanf("%d",&op);
        if (op==1)
        {
            scanf("%d%d",&x,&c);
            q[++tail]=make_pair(c,x);
        }
        else
        {
            scanf("%d",&c);long long ans=0;
            while (c>0 && c>=q[head].first)
            {
                c-=q[head].first;
                ans+=1ll*q[head].first*q[head].second;
                head++;
            }
            if (c!=0)
            {
                q[head].first-=c;
                ans+=1ll*c*q[head].second;
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}