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

const int MAXN=2000;

int p[]={19260817,998244353};
unordered_map<ull,int> Mp;

char s[MAXN+48],s1[MAXN+48],s2[MAXN+48];int len,len1,len2;
ull cmp1[2],cmp2[2];
ull hsh[2][MAXN+48],pw[2][MAXN+48];

inline void init_hash()
{
    for (register int op=0;op<=1;op++)
    {
        pw[op][0]=1;
        for (register int i=1;i<=len;i++) pw[op][i]=pw[op][i-1]*p[op];
    }
    for (register int op=0;op<=1;op++)
    {
        hsh[op][0]=0;
        for (register int i=1;i<=len;i++) hsh[op][i]=hsh[op][i-1]*p[op]+s[i];
    }
    for (register int op=0;op<=1;op++)
    {
        cmp1[op]=0;
        for (register int i=1;i<=len1;i++) cmp1[op]=cmp1[op]*p[op]+s1[i];
    }
    for (register int op=0;op<=1;op++)
    {
        cmp2[op]=0;
        for (register int i=1;i<=len2;i++) cmp2[op]=cmp2[op]*p[op]+s2[i];
    }
}

inline ull gethash(int op,int left,int right)
{
    return hsh[op][right]-hsh[op][left-1]*pw[op][right-left+1];
}

int pos1[MAXN+48],pos2[MAXN+48],tot1,tot2;

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.getstring(s+1);io.getstring(s1+1);io.getstring(s2+1);
    len=strlen(s+1);len1=strlen(s1+1);len2=strlen(s2+1);
    if (len1>len || len2>len) {printf("0\n");return 0;}
    init_hash();
    for (register int i=1;i<=len-len1+1;i++)
        if (gethash(0,i,i+len1-1)==cmp1[0]) pos1[++tot1]=i;
    for (register int i=1;i<=len-len2+1;i++)
        if (gethash(0,i,i+len2-1)==cmp2[0]) pos2[++tot2]=i;
    Mp.clear();int ans=0;
    for (register int i=1;i<=tot1;i++)
        for (register int j=1;j<=tot2;j++)
            if (pos1[i]<=pos2[j] && pos1[i]+len1-1<=pos2[j]+len2-1)
            {
                ull val=gethash(0,pos1[i],pos2[j]+len2-1);
                // val.x=gethash(0,pos1[i],pos2[j]+len2-1);
                // val.y=gethash(1,pos1[i],pos2[j]+len2-1);
                if (Mp[val]==0) Mp[val]=1,ans++;
            }
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}