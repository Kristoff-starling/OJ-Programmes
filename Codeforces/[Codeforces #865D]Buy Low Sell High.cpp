#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,a[300048];

priority_queue<int> q;

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    long long ans=0;
    rep(i,1,n)
    {
        if (!q.empty() && a[i]+q.top()>0)
        {
            ans+=a[i]+q.top();
            q.pop();q.push(-a[i]);
        }
        q.push(-a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}