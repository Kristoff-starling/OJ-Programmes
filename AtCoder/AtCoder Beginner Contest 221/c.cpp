#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n;
int b[48],tot;

vector<int> v1,v2;

int main ()
{
    scanf("%d",&n);
    while (n) b[++tot]=n%10,n/=10;
    long long ans=0;
    rep(Mask,1,(1<<tot)-1)
    {
        v1.clear();v2.clear();
        rep(i,1,tot) if (Mask&(1<<(i-1))) v1.push_back(b[i]); else v2.push_back(b[i]);
        sort(v1.begin(),v1.end());sort(v2.begin(),v2.end());
        reverse(v1.begin(),v1.end());reverse(v2.begin(),v2.end());
        if (v1[0]==0 || v2[0]==0) continue;
        long long x1=0,x2=0;
        for (auto t : v1) x1=x1*10+t;
        for (auto t : v2) x2=x2*10+t;
        ans=max(ans,x1*x2);
    }
    printf("%lld\n",ans);
    return 0;
}