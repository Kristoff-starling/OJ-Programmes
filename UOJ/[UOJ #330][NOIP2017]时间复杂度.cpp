#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB lond double
#define ull unsigned long long
#define uint unsigned int 
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
    char ch;T res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

int n,tar;char s[48];

inline void calc_complexity()
{
    if (s[3]!='n') {tar=0;return;}
    if (s[4]==')') {tar=1;return;}
    int num=0,len=strlen(s+1);
    for (register int i=5;i<=len-1;i++) num=num*10+s[i]-'0';
    tar=num;
}

inline int getnum(char s[])
{
    if (s[1]=='n') return -1;
    int res=0,len=strlen(s+1);
    for (register int i=1;i<=len;i++) res=res*10+s[i]-'0';
    return res;
}

inline int get_complexity(int st,int ed)
{
    if (st==-1 && ed==-1) return 0;
    if (st==-1 && ed!=-1) return -1;
    if (st!=-1 && ed==-1) return 1;
    if (st!=-1 && ed!=-1) return (st<=ed)?0:(-1);
}

inline int judge_complexity(int x,int y)
{
    if (x<0 || y<0) return -1;
    return x+y;
}

bool used[48];

struct FOR
{
    int var,com;
};stack<FOR> sta;

inline void Clear()
{
    memset(used,false,sizeof(used));
    while (!sta.empty()) sta.pop();
}

int main ()
{
    int ca;scanf("%d",&ca);
    char type[10],var[10],st[10],ed[10];
    while (ca--)
    {
        Clear();
        scanf("%d%s",&n,s+1);calc_complexity();
        bool valid=true;int maxn=0;
        for (register int i=1;i<=n;i++)
        {
            scanf("%s",type+1);if (type[1]=='F') scanf("%s%s%s",var+1,st+1,ed+1);
            if (type[1]=='F')
            {
                if (used[var[1]-'a'+1]) valid=false;
                int curc=get_complexity(getnum(st),getnum(ed));
                used[var[1]-'a'+1]=true;
                FOR ins;ins.var=var[1]-'a'+1;ins.com=judge_complexity(sta.empty()?0:sta.top().com,curc);
                check_max(maxn,ins.com);sta.push(ins);
            }
            else
            {
                if (sta.empty()) {valid=false;continue;}
                used[sta.top().var]=false;sta.pop();
            }
        }
        if (!sta.empty()) valid=false;
        if (!valid) puts("ERR"); else puts((maxn==tar)?"Yes":"No");
    }
    return 0;
}