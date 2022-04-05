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

int inv2;
struct Matrix
{
    int b[5][5];
    Matrix () {}
    inline void clear() {memset(b,0,sizeof(b));}
    inline void init_I() {clear();b[1][1]=b[2][2]=1;}
    inline Matrix operator + (Matrix other)
    {
        Matrix res;res.clear();
        for (register int i=1;i<=2;i++)
            for (register int j=1;j<=2;j++)
                res.b[i][j]=add(b[i][j]+other.b[i][j]);
        return res;
    }
    inline Matrix operator * (Matrix other)
    {
        Matrix res;res.clear();
        for (register int i=1;i<=2;i++)
            for (register int j=1;j<=2;j++)
                for (register int k=1;k<=2;k++)
                    Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%MOD);
        return res;
    }
    inline void print()
    {
        cerr<<"------------"<<endl;
        cerr<<b[1][1]<<' '<<b[1][2]<<endl;
        cerr<<b[2][1]<<' '<<b[2][2]<<endl;
        cerr<<"------------"<<endl;
    }
}trans,sta;

inline Matrix quick_pow(Matrix x,int y)
{
    Matrix res;res.init_I();
    while (y)
    {
        if (y&1) res=res*x;
        x=x*x;y>>=1;
    }
    return res;
}

class MatrixPower
{
    int ans[100048],pw[100048];
    vector<int> res;
    public:
        inline vector<int> getElements(int d,int q,int n,int k,vector<int> trow,vector<int> tcol)
        {
            inv2=quick_pow(2,MOD-2);int t=int(trow.size());
            trans.b[1][1]=1ll*d*(n-1)%MOD*n%MOD*inv2%MOD;trans.b[1][2]=n;
            int c1=0,c2=1;for (register int i=0;i<=n-1;i++) Add(trans.b[2][1],1ll*c1*c2%MOD),Add(c1,d),c2=1ll*c2*q%MOD;
            c2=1;for (register int i=0;i<=n-1;i++) Add(trans.b[2][2],c2),c2=1ll*c2*q%MOD;
            pw[0]=1;for (register int i=1;i<=n-1;i++) pw[i]=1ll*pw[i-1]*q%MOD;
            sta.clear();sta.b[1][1]=1;sta=sta*quick_pow(trans,k-1);
            for (register int i=0;i<=t-1;i++) Add(ans[i],1ll*d*trow[i]%MOD*sta.b[1][1]%MOD);
            for (register int i=0;i<=t-1;i++) Add(ans[i],1ll*d*trow[i]%MOD*pw[tcol[i]]%MOD*sta.b[1][2]%MOD);
            sta.clear();sta.b[1][2]=1;sta=sta*quick_pow(trans,k-1);
            for (register int i=0;i<=t-1;i++) Add(ans[i],sta.b[1][1]);
            for (register int i=0;i<=t-1;i++) Add(ans[i],1ll*pw[tcol[i]]*sta.b[1][2]%MOD);
            for (register int i=0;i<=t-1;i++) res.pb(ans[i]);
            return res;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
    int dd,qq,nn,kk;vector<int> rr,cc,res;MatrixPower A;
    while (cin>>dd>>qq>>nn>>kk)
    {
        rr.clear();cc.clear();
        int nu,x;cin>>nu;
        for (register int i=1;i<=nu;i++) cin>>x,rr.pb(x);
        for (register int i=1;i<=nu;i++) cin>>x,cc.pb(x);
        res=A.getElement(dd,qq,nn,kk,rr,cc);
        for (auto item : res) cout<<item<<' ';
        cout<<endl;
    }
    io.flush();
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
    return 0;
}
#endif