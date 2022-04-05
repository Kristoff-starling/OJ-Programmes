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

map<pair<char,char>,pair<char,char> > table;

inline void init()
{
    for (register char i='0';i<='1';i++)
        for (register char j='0';j<='3';j++)
            table[mp(i,j)]=mp(i,j);
    table[mp('0','5')]=mp('0','9');
    table[mp('0','7')]=mp('7','F');
    for (register char j='B';j<='F';j++) table[mp('0',j)]=mp('0',j);
    for (register char j='C';j<='F';j++) table[mp('1',j)]=mp('1',j);
    table[mp('1','6')]=mp('0','8');
    for (register char j='8';j<='9';j++) table[mp('1',j)]=mp('1',j);
    table[mp('2','5')]=mp('0','A');
    table[mp('2','6')]=mp('1','7');
    table[mp('2','7')]=mp('1','B');
    for (register char from='D',to='5';from<='F';from++,to++) table[mp('2',from)]=mp('0',to);
    table[mp('3','2')]=mp('1','6');
    table[mp('3','7')]=mp('0','4');
    for (register char from='C',to='4';from<='D';from++,to++) table[mp('3',from)]=mp('1',to);
    table[mp('3','F')]=mp('1','A');
    table[mp('4','0')]=mp('2','0');
    table[mp('4','B')]=mp('2','E');
    table[mp('4','C')]=mp('3','C');
    table[mp('4','D')]=mp('2','8');
    table[mp('4','E')]=mp('2','B');
    table[mp('4','F')]=mp('7','C');
    table[mp('5','0')]=mp('2','6');
    table[mp('5','A')]=mp('2','1');
    table[mp('5','B')]=mp('2','4');
    table[mp('5','C')]=mp('2','A');
    table[mp('5','D')]=mp('2','9');
    table[mp('5','E')]=mp('3','B');
    table[mp('6','0')]=mp('2','D');
    table[mp('6','1')]=mp('2','F');
    table[mp('6','B')]=mp('2','C');
    table[mp('6','C')]=mp('2','5');
    table[mp('6','D')]=mp('5','F');
    table[mp('6','E')]=mp('3','E');
    table[mp('6','F')]=mp('3','F');
    table[mp('7','9')]=mp('6','0');
    table[mp('7','A')]=mp('3','A');
    table[mp('7','B')]=mp('2','3');
    table[mp('7','C')]=mp('4','0');
    table[mp('7','D')]=mp('2','7');
    table[mp('7','E')]=mp('3','D');
    table[mp('7','F')]=mp('2','2');
    for (register char j='1';j<='9';j++) table[mp('8',j)]=mp('6',j);
    for (register char from='1',to='A';from<='6';from++,to++) table[mp('9',from)]=mp('6',to);
    for (register char from='7',to='0';from<='9';from++,to++) table[mp('9',from)]=mp('7',to);
    table[mp('A','1')]=mp('7','E');
    for (register char from='2',to='3';from<='8';from++,to++) table[mp('A',from)]=mp('7',to);
    table[mp('A','9')]=mp('7','A');
    table[mp('B','0')]=mp('5','E');
    table[mp('B','A')]=mp('5','B');
    table[mp('B','B')]=mp('5','D');
    table[mp('C','0')]=mp('7','B');
    for (register char j='1';j<='9';j++) table[mp('C',j)]=mp('4',j);
    table[mp('D','0')]=mp('7','D');
    for (register char from='1',to='A';from<='6';from++,to++) table[mp('D',from)]=mp('4',to);
    for (register char from='7',to='0';from<='9';from++,to++) table[mp('D',from)]=mp('5',to);
    table[mp('E','0')]=mp('5','C');
    for (register char from='2',to='3';from<='8';from++,to++) table[mp('E',from)]=mp('5',to);
    table[mp('E','9')]=mp('5','A');
    for (register char j='0';j<='9';j++) table[mp('F',j)]=mp('3',j); 
}

char s[10000048];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    init();scanf("%s",s+1);int len=strlen(s+1);
    for (register int i=1;i<len;i+=2)
    {
        pair<char,char> res=table[mp(s[i],s[i+1])];
        printf("%c%c",res.x,res.y);
    }
    puts("");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}