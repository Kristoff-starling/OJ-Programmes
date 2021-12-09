#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MAXN=1e5+10;

int n,q,a[MAXN+48];

struct node
{
    int l,r,lim,id;
    node () {}
    node (int _l,int _r,int _lim,int _id) {l=_l;r=_r;lim=_lim;id=_id;}
};
vector<node> v[MAXN+48];
int ans[MAXN+48];

int t[MAXN+48];

struct Node
{
    int x,y,id,d;
    Node () {}
    Node(int _x,int _y,int _id,int _d) {x=_x;y=_y;id=_id;d=_d;}
    bool operator < (const Node &other) const {return x<other.x;}
}seq[MAXN*6+48],tmp1[MAXN*6+48],tmp2[MAXN*6+48];int tot;

namespace BIT
{
	int c[MAXN+48];int history[MAXN*20+48],htot;
	void init() {htot=0;}
	void modify(int x,int delta) {while (x<=MAXN) c[x]+=delta,history[++htot]=x,x+=LOWBIT(x);}
	int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    int Query(int l,int r) {int res=query(r);if (l) res-=query(l-1);return res;}
	void undo() {rep(i,1,htot) c[history[i]]=0;}
}

void cdq(int l,int r)
{
    if (l==r) return;
    int mid=(l+r)>>1;cdq(l,mid);
    int tot1=mid-l+1,tot2=r-mid;
    rep(i,1,tot1) tmp1[i]=seq[l+i-1];rep(i,1,tot2) tmp2[i]=seq[mid+i];
    sort(tmp1+1,tmp1+tot1+1);sort(tmp2+1,tmp2+tot2+1);
    BIT::init();
    for (int k1=1,k2=1;k2<=tot2;)
        if (k1<=tot1 && tmp1[k1].x<=tmp2[k2].x)
        {
            if (!tmp1[k1].id) BIT::modify(tmp1[k1].y,tmp1[k1].d);
            k1++;
        }
        else
        {
            if (tmp2[k2].id) ans[tmp2[k2].id]+=BIT::Query(tmp2[k2].d,tmp2[k2].y);
            k2++;
        }
    BIT::undo();cdq(mid+1,r);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&q);rep(i,1,n) scanf("%d",a+i);
        rep(i,1,n) v[i].clear();
        int L,R,U,D;
        rep(i,1,q)
        {
            scanf("%d%d%d%d",&L,&D,&R,&U);
            v[L].pb(node(D,U,R,i));
        }
        rep(i,0,MAXN) t[i]=MAXN+48;tot=0;
        REP(i,n,1)
        {
            if (t[a[i]]!=MAXN+48) seq[++tot]=Node(t[a[i]]+1,a[i]+1,0,-1);
            seq[++tot]=Node(i+1,a[i]+1,0,1);
            t[a[i]]=i;
            for (auto item : v[i]) seq[++tot]=Node(item.lim+1,item.r+1,item.id,item.l+1);
        }
        rep(i,1,q) ans[i]=0; cdq(1,tot);
        rep(i,1,q) printf("%d\n",ans[i]);
    }
    return 0;
}