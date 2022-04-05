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

char s[MAXN+48];int len,k;
int sa[MAXN+48],rnk[MAXN+48],tmp[MAXN+48],lcp[MAXN+48];
int ST[MAXN+48][21],Log[MAXN+48];

inline bool compare_sa(int x,int y)
{
    if (rnk[x]!=rnk[y]) return rnk[x]<rnk[y];
    int tmp1=((x+k<=len)?rnk[x+k]:-1),tmp2=((y+k<=len)?rnk[y+k]:-1);
    return tmp1<tmp2;
}

inline void construct_sa()
{
    for (register int i=1;i<=len;i++) sa[i]=i,rnk[i]=s[i];
    for (k=0;k<=len;k==0?k++:k<<=1)
    {
        sort(sa+1,sa+len+1,compare_sa);
        tmp[sa[1]]=1;int cnt=0;
        for (register int i=2;i<=len;i++)
        {
            tmp[sa[i]]=(tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0));
            cnt+=(tmp[sa[i-1]]!=tmp[sa[i]]);
        }
        for (register int i=1;i<=len;i++) rnk[i]=tmp[i];
        if (cnt>=len-1) break;
    }
}

inline void construct_lcp()
{
    for (register int i=1;i<=len;i++) rnk[sa[i]]=i;
    int i,j,h=0;
    for (i=1;i<=len;i++)
    {
        j=sa[rnk[i]-1];
        if (h) h--;
        while (i+h<=len && j+h<=len && s[i+h]==s[j+h]) h++;
        lcp[rnk[i]-1]=h;
    }
}

inline void construct_ST()
{
    for (register int i=1;i<=len-1;i++) ST[i][0]=lcp[i];
    Log[0]=Log[1]=0;for (register int i=2;i<=len;i++) Log[i]=Log[i>>1]+1;
    for (register int j=1;j<=20;j++)
        for (register int i=1;i<=len-1;i++)
        {
            ST[i][j]=ST[i][j-1];
            if (i+(1<<(j-1))<=len) check_min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
        }
}

inline int query(int l,int r)
{
    int k=r-l+1;
    return min(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
}

inline int getw(int x)
{
    if (x==0) return 1;
    int res=0;while (x) res++,x/=10;
    return res;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int l,r,pl,pr,n;LL ans1,ans2;
    while (scanf("%s",s+1)!=EOF)
    {
        len=strlen(s+1);
        construct_sa();construct_lcp();construct_ST();
        pl=pr=ans1=ans2=0;scanf("%d",&n);
        for (register int i=1;i<=n;i++)
        {
            scanf("%d%d",&l,&r);l++;r++;ans1+=r-l+1;
            if (i==1)
            {
                ans2+=r-l+1+1+1;
                pl=l;pr=r;continue;
            }
            int L=rnk[pl],R=rnk[l],res;
            if (L>R) swap(L,R);
            if (L<R) res=query(L,R-1); else res=len;
            check_min(res,r-l);check_min(res,pr-pl);
            ans2+=r-l-res+getw(res)+1+1;
            pl=l;pr=r;
        }
        printf("%lld %lld\n",ans1,ans2);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}