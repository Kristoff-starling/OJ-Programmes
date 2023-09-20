//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

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
template<typename T> inline T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
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

const int MAXBIT=13000;

namespace BigInt
{
    const int lim=1e8;
    struct Bigint
    {
        LL b[13048];int len,sgn;
        Bigint() {len=1;rep(i,1,MAXBIT) b[i]=0;sgn=1;}
        inline void input(string s)
        {
            if (int(s.size())==1 && s[0]=='0') return;
            int down=0;len=0;
            if (s[0]=='-') sgn=-1,down++; else sgn=1;
            for (int i=int(s.size())-1;i>=down;i-=8)
            {
                b[++len]=0;
                for (int j=max(down,i-7);j<=i;j++) b[len]=b[len]*10+s[j]-'0';
            }
        }
        inline void Print()
        {
            if (sgn==-1) printf("-");
            REP(i,len,1)
            {
                if (i!=len)
                {
                    LL tmp=b[i];int w=0;while (tmp) tmp/=10,w++;
                    if (b[i]==0) w=1;
                    w=8-w;while (w--) printf("0");
                }
                printf("%lld",b[i]);
            }
            puts("");
        }
        inline int Len()
        {
            if (len==1 && b[1]==0) return 1;
            int res=(len-1)*8;int tmp=b[len];
            while (tmp) res++,tmp/=10;
            return res;
        }
        inline void dprint()
        {
            rep(i,1,len) cerr<<b[i]<<' ';
            cerr<<endl;
        }
    };
    Bigint myabs(Bigint x) {x.sgn=1;return x;}
    void Swap(Bigint &x,Bigint &y)
    {
        swap(x.sgn,y.sgn);swap(x.len,y.len);
        rep(i,1,MAXBIT) swap(x.b[i],y.b[i]);
    }
    bool operator == (Bigint x,Bigint y)
    {
        if (x.sgn!=y.sgn) return false;
        if (x.Len()!=y.Len()) return false;
        rep(i,1,x.len) if (x.b[i]!=y.b[i]) return false;
        return true;
    }
    bool operator != (Bigint x,Bigint y) {return !(x==y);}
    bool operator > (Bigint x,Bigint y)
    {
        if (x.sgn!=y.sgn) return x.sgn>y.sgn;
        int len1=x.Len(),len2=y.Len();
        if (x.sgn==1)
        {
            if (len1!=len2) return len1>len2;
            REP(i,x.len,1) if (x.b[i]!=y.b[i]) return x.b[i]>y.b[i];
            return false;
        }
        else
        {
            if (len1!=len2) return len1<len2;
            REP(i,x.len,1) if (x.b[i]!=y.b[i]) return x.b[i]<y.b[i];
            return false;
        }
    }
    bool operator < (Bigint x,Bigint y) {return x!=y && !(x>y);}
    Bigint operator + (Bigint x,Bigint y)
    {
        Bigint res;
        if (x.sgn==y.sgn)
        {
            res.sgn=x.sgn;res.len=max(x.len,y.len);
            rep(i,1,res.len) res.b[i]+=x.b[i]+y.b[i],res.b[i+1]+=res.b[i]/lim,res.b[i]%=lim;
            if (res.b[res.len+1]) res.len++;
            return res;
        }
        if (myabs(x)==myabs(y)) return res;
        if (myabs(x)<myabs(y)) {Swap(x,y);}
        res.sgn=x.sgn;res.len=x.len;
        rep(i,1,x.len)
        {
            res.b[i]+=x.b[i]-y.b[i];
            if (res.b[i]<0) res.b[i+1]--,res.b[i]+=lim;
        }
        while (!res.b[res.len]) res.len--;
        return res;
    }
    Bigint operator - (Bigint x,Bigint y)
    {
        if (y.len==1 && y.b[1]==0) return x;
        y.sgn=-y.sgn;return x+y;
    }
    Bigint operator * (Bigint x,Bigint y)
    {
        if (x.len==1 && x.b[1]==0) return x;
        if (y.len==1 && y.b[1]==0) return y;
        Bigint res;res.sgn=x.sgn*y.sgn;res.len=x.len+y.len-1;
        rep(i,1,x.len) rep(j,1,y.len) res.b[i+j-1]+=x.b[i]*y.b[j];
        rep(i,1,res.len) res.b[i+1]+=res.b[i]/lim,res.b[i]%=lim;
        if (res.b[res.len+1]) res.len++;
        return res;
    }
}

string a,b;

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    using namespace BigInt;
    string a,b;cin>>a>>b;
    Bigint x,y;x.input(a);y.input(b);
    x=x*y;x.Print();
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}