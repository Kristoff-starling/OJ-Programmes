#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MOD=998244353;

int n;

unordered_set<int> f[701];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);
        rep(i,0,n) f[i].clear(),f[i].insert(i);
        rep(i,2,n) REP(j,n,1) for (int k=1;k*i<=j;k++) for (auto item : f[j-k*i]) if (f[j].find(item+i*i*k)==f[j].end()) f[j].insert(item+i*i*k);
        for (auto item : f[n]) printf("%d ",(n*n-item)/2);
        puts("");
    }
    return 0;
}