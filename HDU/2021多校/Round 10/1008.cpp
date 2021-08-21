#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define ull unsigned long long
#define pb push_back
#define Pair pair<int,int>
#define LOWBIT(x) ((x) & (-x))
using namespace std;

const int MAXN=2e5;
const int P=998244353;

char s[MAXN+48];int n,q;
int X[MAXN+48],Y[MAXN+48];
int L[MAXN+48],R[MAXN+48];
int g1,g2;

ull hsh[MAXN+48],pw[MAXN+48];
ull query_hsh(int l,int r) {return hsh[r]-hsh[l-1]*pw[r-l+1];}

vector<int> Lin[MAXN+48],Lout[MAXN+48],Rin[MAXN+48],Rout[MAXN+48];

set<int> lp,rp;

struct node1
{
    int type,val;
    node1 () {}
    node1 (int _t,int _v) {type=_t;val=_v;} 
    bool operator < (const node1 &other) const
    {
        if (val!=other.val) return val>other.val;
        return type<other.type;
    }
};

struct node2
{
    int type,s1,s2;
    node2 () {}
    node2 (int _t,int _s1,int _s2) {type=_t;s1=_s1;s2=_s2;}
    bool operator < (const node2 &other) const
    {
        if (s1!=other.s1) return s1>other.s1;
        return type<other.type;
    }
};

unordered_map<LL,int> ans1;
unordered_map<LL,vector<node1> > ans2,ans3;
unordered_map<LL,vector<node2> > ans4;
unordered_set<LL> need2,need3,need4;

vector<node1> t1;vector<node2> t2;

LL ss(int x,int y) {return 1ll*x*(n+1)+y;}

int ans[MAXN+48];

void Clear()
{
    lp.clear();rp.clear();
    rep(i,1,n) Lin[i].clear(),Lout[i].clear(),Rin[i].clear(),Rout[i].clear();
    ans1.clear();ans2.clear();ans3.clear();ans4.clear();
    g1=g2=0;need2.clear();need3.clear();need4.clear();
    rep(i,1,q) ans[i]=0;
}

namespace BIT
{
    int c[MAXN+48],his[MAXN*20+48],htot;
    void init() {htot=0;}
    void update(int x) {while (x) c[x]++,x^=LOWBIT(x),his[++htot]=x;}
    int query(int x) {int res=0;while (x<=n) res+=c[x],x+=LOWBIT(x);return res;}
    void undo() {rep(i,1,htot) c[his[i]]=0;}
}

int main ()
{
    // freopen ("input.txt","r",stdin);
    // freopen ("a.out","w",stdout);
    int ca;scanf("%d",&ca);
    pw[0]=1;rep(i,1,MAXN) pw[i]=pw[i-1]*P;
    while (ca--)
    {
        scanf("%d%d%s",&n,&q,s+1);rep(i,1,q) scanf("%d%d",X+i,Y+i);
        Clear();
        hsh[0]=0;rep(i,1,n) hsh[i]=hsh[i-1]*P+s[i];
        rep(i,1,n)
        {
            if (s[i]!=s[1]) {L[i]=0;continue;}
            int l=1,r=n-i+1,mid;
            while (l<=r)
            {
                mid=(l+r)>>1;
                if (query_hsh(1,mid)==query_hsh(i,i+mid-1)) L[i]=mid,l=mid+1; else r=mid-1;
            }
        }
        rep(i,1,n)
        {
            if (s[i]!=s[n]) {R[i]=0;continue;}
            int l=1,r=i,mid;
            while (l<=r)
            {
                mid=(l+r)>>1;
                if (query_hsh(i-mid+1,i)==query_hsh(n-mid+1,n)) R[i]=mid,l=mid+1; else r=mid-1;
            }
        }
        rep(i,1,n) if (L[i]) Lin[i].pb(i),Lout[i+L[i]].pb(i);
        rep(i,1,n) if (R[i]) Rin[i-R[i]].pb(i),Rout[i].pb(i);
        for (auto item : Rin[0]) rp.insert(item);
        rep(i,1,n-1)
        {
            for (auto item : Lin[i]) lp.insert(item);
            for (auto item : Lout[i]) lp.erase(lp.find(item));
            for (auto item : Rin[i]) rp.insert(item);
            for (auto item : Rout[i]) rp.erase(rp.find(item));
            if (int(lp.size())<=2 && int(rp.size())<=2)
            {
                for (auto item1 : lp) for (auto item2 : rp)
                    ans1[ss(i-item1+1,item2-i)]++;
            }
            else if (int(lp.size())<=2)
            {
                g2=(*--rp.end())-(*----rp.end());
                int st=((*rp.begin())-i)%g2,nu=((*--rp.end())-i-st)/g2;
                for (auto item : lp) ans2[ss(i-item+1,st)].pb(node1(0,nu));
            }
            else if (int(rp.size())<=2)
            {
                g1=(*++lp.begin())-(*lp.begin());
                int st=(i-(*--lp.end())+1)%g1,nu=(i-(*lp.begin())+1-st)/g1;
                for (auto item : rp) ans3[ss(st%g1,item-i)].pb(node1(0,nu));
            }
            else
            {
                g1=(*++lp.begin())-(*lp.begin());g2=(*--rp.end())-(*----rp.end());
                int st1=(i-(*--lp.end())+1)%g1,st2=((*rp.begin())-i)%g2,nu1=(i-(*lp.begin())+1-st1)/g1,nu2=((*--rp.end())-i-st2)/g2;
                ans4[ss(st1,st2)].pb(node2(0,nu1,nu2));
            }
        }
    }
    rep(i,1,q) ans[i]+=ans1[ss(X[i],Y[i])];
    if (g2) rep(i,1,q) ans2[ss(X[i],Y[i]%g2)].pb(node1(i,Y[i]/g2)),need2.insert(ss(X[i],Y[i]%g2));
    if (g1) rep(i,1,q) ans3[ss(X[i]%g1,Y[i])].pb(node1(i,X[i]/g1)),need3.insert(ss(X[i]%g1,Y[i]));
    if (g1 && g2) rep(i,1,q) ans4[ss(X[i]%g1,Y[i]%g2)].pb(node2(i,X[i]/g1,Y[i]/g2)),need4.insert(ss(X[i]%g1,Y[i]%g2));
    for (auto item : need2)
    {
        t1=ans2[item];int cnt=0;
        for (auto item2 : t1)
            if (item2.type==0) cnt++; else ans[item2.type]+=cnt;
    }
    for (auto item : need3)
    {
        t1=ans3[item];int cnt=0;
        for (auto item2 : t1)
            if (item2.type==0) cnt++; else ans[item2.type]+=cnt;
    }
    for (auto item : need4)
    {
        t2=ans4[item];BIT::init();
        for (auto item2 : t2)
            if (item2.type==0) BIT::update(item2.s2); else ans[item2.type]+=BIT::query(item2.s2);
        BIT::undo();
    }
    rep(i,1,q) printf("%d\n",ans[i]);
    return 0;
}