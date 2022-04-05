#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}
 
const int MAXN=1e5;

int n,k;LL fans;

struct node
{
    int l,r,mid;
    node () {}
    inline node (int _l,int _r) {l=_l;r=_r;mid=(l+r)>>1;}
    inline bool operator < (const node &other) const {return mid<other.mid;}
}a[MAXN+48];int tot;

struct StrangeSet
{
    multiset<int> s1,s2;
    int sz1,sz2;LL sum1,sum2;
    inline void clear() {sz1=sz2=sum1=sum2=0;s1.clear();s2.clear();}
    inline void insert(int x1,int x2)
    {
        if (x1>x2) swap(x1,x2);
        if (!sz1) {s1.insert(x1);sum1=x1;s2.insert(x2);sum2=x2;sz1=sz2=1;return;}
        int cmp=(*s2.begin());
        if (x1>=cmp)
        {
            s2.insert(x1);sum2+=x1;s2.insert(x2);sum2+=x2;
            multiset<int>::iterator iter=s2.begin();
            s1.insert(*iter);sum1+=(*iter);sum2-=(*iter);s2.erase(iter);
            sz1++;sz2++;
        }
        else if (x2<=cmp)
        {
            s1.insert(x1);sum1+=x1;s1.insert(x2);sum1+=x2;
            multiset<int>::iterator iter=s1.find(*s1.rbegin());
            s2.insert(*iter);sum2+=(*iter);sum1-=(*iter);s1.erase(iter);
            sz1++;sz2++;
        }
        else
        {
            s1.insert(x1);s2.insert(x2);
            sum1+=x1;sum2+=x2;
            sz1++;sz2++;
        }
    }
    inline void del(int x1,int x2)
    {
        if (s1.find(x1)!=s1.end()) {multiset<int>::iterator iter=s1.find(x1);sum1-=(*iter);s1.erase(iter);sz1--;}
        else {multiset<int>::iterator iter=s2.find(x1);sum2-=(*iter);s2.erase(iter);sz2--;}
        if (s1.find(x2)!=s1.end()) {multiset<int>::iterator iter=s1.find(x2);sum1-=(*iter);s1.erase(iter);sz1--;}
        else {multiset<int>::iterator iter=s2.find(x2);sum2-=(*iter);s2.erase(iter);sz2--;}
        int delta=sz1-sz2;
        while (delta>0)
        {
            multiset<int>::iterator iter=s1.find(*s1.rbegin());
            sum1-=(*iter);sum2+=(*iter);
            s2.insert(*iter);s1.erase(iter);
            delta-=2;sz1--;sz2++;
        }
        while (delta<0)
        {
            multiset<int>::iterator iter=s2.begin();
            sum1+=(*iter);sum2-=(*iter);
            s1.insert(*iter);s2.erase(iter);
            delta+=2;sz1++;sz2--;
        }
    }
    inline LL query()
    {
        if (!sz1) return 0;
        int val=(*s1.rbegin());
        return 1ll*val*sz1-sum1+sum2-1ll*val*sz2;
    }
}S1,S2;

namespace small
{
    StrangeSet S;
    inline void solve()
    {
        S.clear();
        for (register int i=1;i<=tot;i++) S.insert(a[i].l,a[i].r);
        printf("%lld\n",S.query()+fans+tot);
    }
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&k,&n);char type1[3],type2[3];int p1,p2;
    for (register int i=1;i<=n;i++)
    {
        scanf("%s%d%s%d",type1+1,&p1,type2+1,&p2);
        if (type1[1]==type2[1]) fans+=myabs(p1-p2);
        else
        {
            if (p1>p2) swap(p1,p2);
            a[++tot]=node(p1,p2);
        }
    }
    if (k==1) {small::solve();return 0;}
    sort(a+1,a+tot+1);
    S1.clear();S2.clear();
    for (register int i=1;i<=tot;i++) S2.insert(a[i].l,a[i].r);
    LL curans=S1.query()+S2.query();
    for (register int i=1;i<=tot-1;i++)
    {
        S1.insert(a[i].l,a[i].r);S2.del(a[i].l,a[i].r);
        check_min(curans,S1.query()+S2.query());
    }
    printf("%lld\n",fans+curans+tot);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
