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

class Posters
{
    int n,m,x[48],y[48],N;
    int posx[48],posy[48],res=0;
    int popcount[1048];
    inline void init_popcount()
    {
        for (register int Mask=0;Mask<=(1<<N)-1;Mask++)
        {
            popcount[Mask]=0;
            for (register int cur=Mask;cur;cur^=LOWBIT(cur)) popcount[Mask]++;
        }
    }
    inline int calc_area(int Mask)
    {
        int x1,y1,x2,y2,res=0;
        for (register int sub=Mask;sub;sub=(sub-1)&Mask)
        {
            x1=y1=-INF;x2=y2=INF;
            for (register int i=1;i<=N;i++)
                if (sub&(1<<(i-1)))
                {
                    check_max(x1,posx[i]);check_max(y1,posy[i]);
                    check_min(x2,posx[i]+x[i]-1);check_min(y2,posy[i]+y[i]-1);
                }
            int tmp=max(x2-x1+1,0)*max(y2-y1+1,0);
            if (popcount[sub]&1) res+=tmp; else res-=tmp;
        }
        return res;
    }
    map<ull,int> Mp;
    static const int p=107;
    inline ull gethash(int Mask)
    {
        ull res=0;
        for (register int i=1;i<=N;i++)
            if (Mask&(1<<(i-1))) res=res*p+posx[i],res=res*p+posy[i];
            else res=res*p+(n+1),res=res*p+(m+1);
        return res;
    }
    // inline void Go(int Mask);
    inline void puty(int Mask,int id,int pos)
    {
        if (!(1<=pos && pos<=m)) return;
        if (pos+y[id]-1>m) return;
        posy[id]=pos;Mask|=(1<<(id-1));
        int curarea=calc_area(Mask);check_max(res,curarea);
        int max_possible=curarea;
        for (register int i=1;i<=N;i++)
            if (!(Mask&(1<<(i-1)))) max_possible+=x[i]*y[i];
        if (max_possible<=res) return;
        ull hsh=gethash(Mask);
        if (Mp.find(hsh)==Mp.end())
        {
            Mp[hsh]=1;
            Go(Mask);
        }
    }
    inline void putx(int Mask,int id,int pos)
    {
        if (!(1<=pos && pos<=n)) return;
        if (pos+x[id]-1>n) return;
        posx[id]=pos;
        puty(Mask,id,1);puty(Mask,id,m-y[id]+1);
        for (register int i=1;i<=N;i++)
            if (Mask&(1<<(i-1))) puty(Mask,id,posy[i]-y[id]),puty(Mask,id,posy[i]+y[i]);
    }
    inline void Go(int Mask)
    {
        for (register int i=1;i<=N;i++)
            if (!(Mask&(1<<(i-1))))
            {
                putx(Mask,i,1);putx(Mask,i,n-x[i]+1);
                for (register int j=1;j<=N;j++)
                    if (Mask&(1<<(j-1))) putx(Mask,i,posx[j]-x[i]),putx(Mask,i,posx[j]+x[j]);
            }
    }
    public:
        inline int maxCover(int NN,int MM,vector<int> X,vector<int> Y)
        {
            n=NN;m=MM;N=int(X.size());res=0;
            for (register int i=1;i<=N;i++) x[i]=X[i-1],y[i]=Y[i-1];
            init_popcount();Go(0);return res;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;int N,M,k;
    Posters A;
    while (cin>>N>>M>>k)
    {
        vector<int> v1,v2;v1.clear();v2.clear();int x;
        for (register int i=1;i<=k;i++) cin>>x,v1.pb(x);
        for (register int i=1;i<=k;i++) cin>>x,v2.pb(x);
        cout<<A.maxCover(N,M,v1,v2)<<endl;
    }
    io.flush();
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
    return 0;
}
#endif