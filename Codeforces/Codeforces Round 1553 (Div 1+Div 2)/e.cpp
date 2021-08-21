#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MAXN=3e5;

int n,m;
int a[MAXN+48],tmp[MAXN+48],b[MAXN+48];
int pos[MAXN+48];

int cnt[MAXN+48];
vector<int> ans;

bool check(int x)
{
    rep(i,1+x,n) b[i]=i-x;
    rep(i,1,x) b[i]=n-x+i;
    rep(i,1,n) tmp[i]=a[i];
    rep(i,1,n) pos[a[i]]=i;
    int cnt=0;
    rep(i,1,n) if (a[i]!=b[i])
    {
        cnt++;
        int tar=pos[b[i]];
        pos[a[i]]=tar;
        swap(a[i],a[tar]);
        pos[b[i]]=i;
    }
    rep(i,1,n) a[i]=tmp[i];
    if (cnt<=m) return true; else return false;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);rep(i,1,n) scanf("%d",a+i);
        rep(i,1,n) if (a[i]<=i) cnt[i-a[i]]++; else cnt[i+(n-a[i])]++;
        ans.clear();rep(i,0,n-1) if (cnt[i]+m*2>=n && check(i)) ans.pb(i);
        printf("%d ",int(ans.size()));for (auto item : ans) printf("%d ",item);puts("");
    }
    return 0;
}