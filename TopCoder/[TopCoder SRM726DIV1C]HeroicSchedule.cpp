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

const int MAXN=2e6;

struct node
{
    int st,ed,cost;
    inline bool operator < (const node &other) const {return cost>other.cost;}
}a[MAXN+48];int X[MAXN*3+48];

class HeroicSchedule
{
    int n;
    set<int> s;multiset<int> ss;
    vector<int> r[2048];int tor[2048],m;
    inline void getfree()
    {
        s.clear();ss.clear();
        for (register int i=0;i<m;i++)
        {
            for (auto item : r[i]) ss.insert(item);
            if (ss.empty()) tor[i]=m;
            else tor[i]=(*ss.begin()),ss.erase(ss.begin());
        }
        for (register int i=m-1;i>=0;i--)
            if (tor[i]==m || ((!s.empty()) && (*s.begin())<=tor[i])) s.insert(i);
    }
    inline void Clear()
    {
        for (register int i=0;i<m;i++) r[i].clear();
    }
    public:
        inline int getmax(int N,int A,int B,int C,int modStart,int modLen,int modCost)
        {
            n=N;
            X[0]=A;for (register int i=1;i<=n*3-1;i++) X[i]=(1ll*X[i-1]*B+C)%MOD;
            for (register int i=0;i<=n-1;i++)
            {
                a[i+1].st=X[i*3]%modStart;
                a[i+1].ed=a[i+1].st+(X[i*3+1]%modLen);
                a[i+1].cost=X[i*3+2]%modCost;
            }
            sort(a+1,a+n+1);m=modStart+modLen-1;
            Clear();
            getfree();int ans=0;
            for (register int i=1;i<=n;i++)
                if ((!s.empty()) && (*s.rbegin())>=a[i].st && *s.lower_bound(a[i].st)<=a[i].ed)
                {
                    ans+=a[i].cost;
                    r[a[i].st].pb(a[i].ed);
                    getfree();
                }
            return ans;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
    int nn,aa,bb,cc,ss,ll,co;
    HeroicSchedule A;
    while (cin>>nn>>aa>>bb>>cc>>ss>>ll>>co) cout<<A.getmax(nn,aa,bb,cc,ss,ll,co)<<endl;
    io.flush();
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
    return 0;
}
#endif