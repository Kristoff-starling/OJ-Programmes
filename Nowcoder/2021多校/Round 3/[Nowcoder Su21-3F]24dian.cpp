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

int n,m;

struct frac
{
    LL A,B;
    frac () {A=0;B=1;}
    frac (LL _A,LL _B) {A=_A;B=_B;}
    bool operator < (const frac &other) const {return A*other.B<other.A*B;}
    frac operator + (frac other)
    {
        frac res;res.B=B*other.B/mygcd(B,other.B);
        res.A=A*res.B/B+other.A*res.B/other.B;
        if (res.B<0) res.A*=-1,res.B*=-1;
        LL g=mygcd(res.A,res.B);res.A/=g;res.B/=g;return res;
    }
    frac operator - (frac other)
    {
        frac res;res.B=B*other.B/mygcd(B,other.B);
        res.A=A*res.B/B-other.A*res.B/other.B;
        if (res.B<0) res.A*=-1,res.B*=-1;
        LL g=mygcd(res.A,res.B);res.A/=g;res.B/=g;return res;
    }
    frac operator * (frac other)
    {
        frac res;res.A=A*other.A;res.B=B*other.B;
        if (res.B<0) res.A*=-1,res.B*=-1;
        LL g=mygcd(res.A,res.B);res.A/=g;res.B/=g;return res;
    }
    frac operator / (frac other)
    {
        frac res;res.A=A*other.B;res.B=B*other.A;
        if (res.B<0) res.A*=-1,res.B*=-1;
        LL g=mygcd(res.A,res.B);res.A/=g;res.B/=g;return res;
    }
};

int cnt,fcnt;

void dfs(vector<frac> cur,bool f)
{
    if (cnt!=fcnt) return;
    if (int(cur.size())==1)
    {
        if (cur[0].A==m && cur[0].B==1)
        {
            cnt++;
            if (f) fcnt++;
        }
        return;
    }
    vector<frac> to;
    rep(i,0,int(cur.size())-1) rep(j,i+1,int(cur.size())-1)
    {
        //+
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        to.pb(cur[i]+cur[j]);
        dfs(to,f);
        //-
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        to.pb(cur[i]-cur[j]);
        dfs(to,f);
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        to.pb(cur[j]-cur[i]);
        dfs(to,f);
        //*
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        to.pb(cur[i]*cur[j]);
        dfs(to,f);
        ///
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        if (cur[j].A)
        {
            frac res=cur[i]/cur[j];
            bool ff=f;
            if (res.B!=1) ff=true;
            to.pb(res);
            dfs(to,ff);
        }
        to.clear();
        rep(k,0,int(cur.size())-1) if (k!=i && k!=j) to.pb(cur[k]);
        if (cur[i].A)
        {
            frac res=cur[j]/cur[i];
            bool ff=f;
            if (res.B!=1) ff=true;
            to.pb(res);
            dfs(to,ff);
        }
    }
}

vector<vector<frac> > ans;
vector<frac> cur;

void Dfs(int pos,int c)
{
    if (pos==n+1)
    {
        cnt=0;fcnt=0;
        dfs(cur,false);
        if (cnt && cnt==fcnt) ans.pb(cur);
        return;
    }
    rep(nxt,c,13) cur.pb(frac(nxt,1)),Dfs(pos+1,nxt),cur.pop_back();
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&m);
    Dfs(1,0);
    printf("%d\n",int(ans.size()));
    for (auto item : ans)
    {
        for (auto item2: item) printf("%lld ",item2.A);
        puts("");
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}