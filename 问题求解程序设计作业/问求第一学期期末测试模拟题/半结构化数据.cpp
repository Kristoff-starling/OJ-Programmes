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

struct Datatype
{
    string s;int cur;
    Datatype () {s="";cur=0;}
    bool operator < (const Datatype &other) const
    {
        if (cur!=other.cur) return cur<other.cur;
        return s<other.s;
    }
    void print()
    {
        if (cur==1) cout<<s<<"(string)"<<endl;
        if (cur==2) cout<<s<<"(integer)"<<endl;
        if (cur==3) cout<<s<<"(float)"<<endl;
    }
};

map<string,Datatype> m_string,m_int,m_float;

Datatype identify(string s)
{
    Datatype res;res.s=s;
    for (int i=0;i<int(s.size());i++)
    {
        if (isalpha(s[i])) {res.cur=1;return res;}
        if (s[i]=='.') {res.cur=3;return res;}
    }
    res.cur=2;return res;
}

void Set(string s,Datatype val)
{
    for (map<string,Datatype>::iterator iter=m_string.begin();iter!=m_string.end();iter++)
        if (iter->x==s) {m_string.erase(iter);break;}
    for (map<string,Datatype>::iterator iter=m_int.begin();iter!=m_int.end();iter++)
        if (iter->x==s) {m_int.erase(iter);break;}
    for (map<string,Datatype>::iterator iter=m_float.begin();iter!=m_float.end();iter++)
        if (iter->x==s) {m_float.erase(iter);break;}
    if (val.cur==1) m_string[s]=val;
    if (val.cur==2) m_int[s]=val;
    if (val.cur==3) m_float[s]=val;
}

void Get(string s)
{
    bool exist=false;
    for (map<string,Datatype>::iterator iter=m_string.begin();iter!=m_string.end();iter++)
        if (iter->x==s) exist=true,iter->y.print();
    for (map<string,Datatype>::iterator iter=m_int.begin();iter!=m_int.end();iter++)
        if (iter->x==s) exist=true,iter->y.print();
    for (map<string,Datatype>::iterator iter=m_float.begin();iter!=m_float.end();iter++)
        if (iter->x==s) exist=true,iter->y.print();
    if (!exist) puts("None"); puts("");
}

pair<string,Datatype> a[1048];int tot;

void Getalltype(string s)
{
    tot=0;
    if (s=="string")
        for (map<string,Datatype>::iterator iter=m_string.begin();iter!=m_string.end();iter++)
            a[++tot]=mp(iter->x,iter->y);
    if (s=="integer")
        for (map<string,Datatype>::iterator iter=m_int.begin();iter!=m_int.end();iter++)
            a[++tot]=mp(iter->x,iter->y);
    if (s=="float")
        for (map<string,Datatype>::iterator iter=m_float.begin();iter!=m_float.end();iter++)
            a[++tot]=mp(iter->x,iter->y);
    sort(a+1,a+tot+1);
    rep(i,1,tot) cout<<a[i].x<<":",a[i].y.print();
    puts("");
}

void Getall()
{
    tot=0;
    for (map<string,Datatype>::iterator iter=m_string.begin();iter!=m_string.end();iter++)
        a[++tot]=mp(iter->x,iter->y);
    for (map<string,Datatype>::iterator iter=m_int.begin();iter!=m_int.end();iter++)
        a[++tot]=mp(iter->x,iter->y);
    for (map<string,Datatype>::iterator iter=m_float.begin();iter!=m_float.end();iter++)
        a[++tot]=mp(iter->x,iter->y);
    sort(a+1,a+tot+1);
    rep(i,1,tot) cout<<a[i].x<<":",a[i].y.print();
    puts("");
}

string tmp="";

void input(string &s)
{
    if (tmp=="") cin>>tmp;
    s=tmp;tmp="";
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int n;cin>>n;string op,s,val;
    while (n--)
    {
        input(op);
        if (op=="SET") input(s),input(val),Set(s,identify(val));
        if (op=="GET") input(s),Get(s);
        if (op=="GETALL")
        {
            input(s);
            if (s=="WITHIN") input(s),Getalltype(s);
            else tmp=s,Getall();
        }
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}