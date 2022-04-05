#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
    char ch;bool f;T res;
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

const int MAXN=1e5;

int n;
int a[MAXN+48];

priority_queue<Pair> q;
int cnt,ans,delta;

int main ()
{
    Get(n);for (register int i=1;i<=n;i++) Get(a[i]),q.push(mp(-a[i],i));
    a[0]=a[n+1]=-1;
    cnt=1;delta=0;
    while (!q.empty())
    {
        int x=-q.top().x,id=q.top().y;q.pop();
        x-=delta;delta=a[id];
        ans+=cnt*x;
        a[id]=-1;
        if (a[id-1]!=-1 && a[id+1]!=-1) cnt++;
        else if (a[id-1]==-1 && a[id+1]==-1) cnt--;
    }
    printf("%d\n",ans);
    return 0;
}