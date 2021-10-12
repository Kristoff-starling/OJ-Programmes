#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=8e5;

int n;
int L[MAXN+48],R[MAXN+48];
int ans[MAXN+48];

pair<int,int> val[MAXN+48];int tot;

int main ()
{
    scanf("%d",&n);int st,len;
    rep(i,1,n)
    {
        scanf("%d%d",&st,&len);L[i]=st;R[i]=st+len;
        val[++tot]=make_pair(L[i],1);val[++tot]=make_pair(R[i],-1);
    }
    sort(val+1,val+tot+1);int cnt=0;
    rep(i,1,tot)
    {
        cnt+=val[i].second;
        if (cnt && i!=tot) ans[cnt]+=val[i+1].first-val[i].first;
    }
    rep(i,1,n) printf("%d ",ans[i]);puts("");
    return 0;
}