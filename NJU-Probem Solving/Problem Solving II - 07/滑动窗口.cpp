#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n,k;

multiset<int> s;

int a[1000048];

int minn[1000048],maxn[1000048];

int main ()
{
    scanf("%d%d",&n,&k);rep(i,1,n) scanf("%d",a+i);
    s.clear();rep(i,1,k) s.insert(a[i]);
    minn[1]=(*s.begin());maxn[1]=(*s.rbegin());
    rep(i,2,n-k+1)
    {
        multiset<int>::iterator iter=s.find(a[i-1]);s.erase(iter);s.insert(a[i+k-1]);
        minn[i]=(*s.begin());maxn[i]=(*s.rbegin());
    }
    rep(i,1,n-k+1) printf("%d ",minn[i]);puts("");
    rep(i,1,n-k+1) printf("%d ",maxn[i]);puts("");
    return 0;
}