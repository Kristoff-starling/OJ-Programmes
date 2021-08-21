#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1e5;

int n,k,L,R,a[MAXN+48],sum[MAXN+48];

void update(int l,int r) {if (L==n+1 || r-l<=R-L) L=l,R=r;}

namespace trie
{
    int tot=0,lson[MAXN*30+48],rson[MAXN*30+48],minn[MAXN*30+48],cnt[MAXN*30+48],root;
    int Create() {++tot;lson[tot]=rson[tot]=cnt[tot]=0;minn[tot]=MAXN+48;return tot;}
    void init() {tot=0;minn[0]=MAXN+48;root=Create();}
    void pushup(int cur) {minn[cur]=min(minn[lson[cur]],minn[rson[cur]]);cnt[cur]=cnt[lson[cur]]+cnt[rson[cur]];}
    void insert(int &cur,int val,int pos,int loc)
    {
        if (!cur) cur=Create();
        if (pos==-1) {cnt[cur]++;minn[cur]=min(minn[cur],loc);return;}
        int curval=(val&(1<<pos));
        if (!curval) insert(lson[cur],val,pos-1,loc); else insert(rson[cur],val,pos-1,loc);
        pushup(cur);
    }
    void insert(int x,int pos)
    {
        insert(root,x,29,pos);
    }
    void query(int pos,int v)
    {
        int cur=root;
        REP(i,29,0)
        {
            int tar=(k&(1<<i));
            if (!tar)
            {
                int t=((1<<i)^(v&(1<<i)));
                if (!t && cnt[lson[cur]])
                {
                    int ppos=minn[lson[cur]];
                    update(pos,ppos);
                }
                if (t && cnt[rson[cur]])
                {
                    int ppos=minn[rson[cur]];
                    update(pos,ppos);
                }
            }
            int t=(tar^(v&(1<<i)));
            if (!t) cur=lson[cur]; else cur=rson[cur];
            if (i==0 && cnt[cur]) update(pos,minn[cur]);
            if (!cnt[cur]) break;
        }
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&k);rep(i,1,n) scanf("%d",a+i);
        sum[0]=0;rep(i,1,n) sum[i]=(sum[i-1]^a[i]);
        L=R=n+1;trie::init();
        REP(i,n,1)
        {
            trie::insert(sum[i],i);
            trie::query(i,sum[i-1]);
        }
        if (L==n+1) puts("-1"); else printf("%d %d\n",L,R);
    }
    return 0;
}