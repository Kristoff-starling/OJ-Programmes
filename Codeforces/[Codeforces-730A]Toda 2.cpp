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
#define LOCAL true

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

int n;
int a[148];
typedef bitset<148> bs;

vector<bs> ope;
multiset<Pair> s;

inline bool check(int cmp)
{
    ope.clear();s.clear();int cnt=0;
    for (register int i=1;i<=n;i++) if (a[i]-cmp>0) s.insert(mp(a[i]-cmp,i)),cnt+=a[i]-cmp;
    if (!cnt) return true;
    if (cnt==1) return false;
    int cc=((cnt%2==0)?cnt/2:(cnt-3)/2);
    while (cc--)
    {
        if (int(s.size())<2) return false;
        multiset<Pair>::iterator iter=(--s.end());
        int val1=iter->x,ind1=iter->y;s.erase(iter);
        iter=(--s.end());int val2=iter->x,ind2=iter->y;s.erase(iter);
        bs ins;ins=0;ins[ind1]=1;ins[ind2]=1;ope.pb(ins);
        if (val1>1) --val1,s.insert(mp(val1,ind1));
        if (val2>1) --val2,s.insert(mp(val2,ind2));
    }
    if (cnt%2==1)
    {
        if (int(s.size())!=3) return false;
        bs ins=0;
        for (multiset<Pair>::iterator iter=s.begin();iter!=s.end();iter++)
            ins[iter->y]=1;
        ope.pb(ins);
    }
    return true;
}

inline void print(int ans)
{
    printf("%d\n",ans);
    printf("%d\n",int(ope.size()));
    for (bs Mask : ope)
    {
        for (register int i=1;i<=n;i++) if (Mask[i]==1) printf("1"); else printf("0");
        printf("\n");
    }
}

inline void doit_zero()
{
    ope.clear();
    for (register int i=2;i<=n;i++)
    {
        bs ins=0;ins[i]=1;ins[1]=1;
        while (a[i])
        {
            ope.pb(ins);a[i]--;
            if (a[1]) a[1]--;
        }
    }
    if (a[1])
    {
        bs ins=0;ins[1]=1;ins[2]=1;
        while (a[1]) ope.pb(ins),a[1]--;
    }
    print(0);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(a[i]);
    if (n==1)
    {
        printf("%d\n",a[1]);
        printf("0\n");
        return 0;
    }
    int minn=a[1],minpos=1;
    for (register int i=2;i<=n;i++) if (a[i]<minn) minn=a[i],minpos=i;
    for (register int i=a[minpos];i>=1;i--)
        if (check(i)) {print(i);return 0;}
    doit_zero();
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}