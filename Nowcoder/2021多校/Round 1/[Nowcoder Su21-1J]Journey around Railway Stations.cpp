#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=1e6;

int n,q;
int st[MAXN+48],ed[MAXN+48],t[MAXN+48];

struct sta
{
    LL y,x1,x2;
    sta () {}
    sta (LL _x1,LL _x2,LL _y) {y=_y;x1=_x1;x2=_x2;}
};

namespace SegmentTree
{
    sta info[MAXN<<2];
    sta pushup(sta A,sta B)
    {
        if (A.x2==-1 || B.x2==-1 || A.y>B.x2) return sta(0,0,-1);
        sta res;
        if (B.x1<=A.y)
        {
            res.y=B.y+A.y-B.x1;
            res.x1=A.x1;res.x2=A.x1+min(B.x2-A.y,A.x2-A.x1);
        }
        else
        {
            res.y=B.y;
            if (A.x2-A.x1<=B.x1-A.y) res.x1=res.x2=A.x2;
            else
            {
                res.x1=A.x1+B.x1-A.y;
                if (A.y+A.x2-A.x1<=B.x2) res.x2=A.x2; else res.x2=A.x1+B.x2-A.y;
            }
        }
        return res;
    }
    void modify(int cur,int pos,sta val,int l,int r)
    {
        if (l==r) {info[cur]=val;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) modify(cur<<1,pos,val,l,mid); else modify(cur<<1|1,pos,val,mid+1,r);
        info[cur]=pushup(info[cur<<1],info[cur<<1|1]);
    }
    sta query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return info[cur];
        int mid=(l+r)>>1;
        if (right<=mid) return query(cur<<1,left,right,l,mid);
        if (mid+1<=left) return query(cur<<1|1,left,right,mid+1,r);
        return pushup(query(cur<<1,left,right,l,mid),query(cur<<1|1,left,right,mid+1,r));
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",st+i);rep(i,1,n) scanf("%d",ed+i);
        rep(i,1,n-1) scanf("%d",t+i);t[n]=0;
        rep(i,1,n) SegmentTree::modify(1,i,sta(st[i],ed[i],st[i]+t[i]),1,n);
        scanf("%d",&q);int op,l,r,p,w;
        while (q--)
        {
            scanf("%d",&op);
            if (!op)
            {
                scanf("%d%d",&l,&r);
                sta res=SegmentTree::query(1,l,r,1,n);
                if ((long long)st[l]>res.x2) puts("No"); else puts("Yes");
            }
            else
            {
                if (op==1) scanf("%d%d",&p,&w),t[p]=w;
                if (op==2) scanf("%d%d%d",&p,&l,&r),st[p]=l,ed[p]=r;
                SegmentTree::modify(1,p,sta(st[p],ed[p],st[p]+t[p]),1,n);
            }
        }
    }
    return 0;
}