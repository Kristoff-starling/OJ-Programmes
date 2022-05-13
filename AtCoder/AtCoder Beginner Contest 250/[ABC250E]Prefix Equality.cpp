#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;

int n,q,a[MAXN+48],b[MAXN+48],mina[MAXN+48],minb[MAXN+48];
unordered_map<int,int> ma,mb;

int main ()
{
    scanf("%d",&n);
    rep(i,1,n)
    {
        scanf("%d",a+i);
        if (ma.find(a[i])==ma.end()) ma[a[i]]=i;
    }
    rep(i,1,n)
    {
        scanf("%d",b+i);
        if (mb.find(b[i])==mb.end()) mb[b[i]]=i;
    }
    rep(i,1,n)
    {
        mina[i]=(mb.find(a[i])==mb.end())?(n+1):mb[a[i]];
        minb[i]=(ma.find(b[i])==ma.end())?(n+1):ma[b[i]];
        mina[i]=max(mina[i],mina[i-1]);minb[i]=max(minb[i],minb[i-1]);
    }
    int x,y;scanf("%d",&q);
    while (q--)
    {
        scanf("%d%d",&x,&y);
        if (mina[x]<=y && minb[y]<=x) puts("Yes"); else puts("No");
    }
    return 0;
}