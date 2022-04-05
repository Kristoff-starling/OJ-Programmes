#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=1e9+7;
const LL LINF=2e17;
const int INF=1e9;
const int magic=348;
const long double eps=1e-7;
const double pi=3.14159265;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
int n;
int a[100048];
vector<int> v[10048];
int q[300048],starter[10048],head[10048];
int cnt[10048],pos[10048],vpos[100048];
LL dp[100048];
 
inline double calc(int j,int k)
{
    double y1=dp[j-1]*1.0/a[j]-2ll*vpos[j]+(long long)vpos[j]*vpos[j],x1=vpos[j];
    double y2=dp[k-1]*1.0/a[k]-2ll*vpos[k]+(long long)vpos[k]*vpos[k],x2=vpos[k];
    return (y1-y2)*1.0/(x1-x2);
}
 
int main ()
{
    int i;n=getint();
    for (i=1;i<=n;i++)
    {
        a[i]=getint();cnt[a[i]]++;
        vpos[i]=cnt[a[i]];
    }
    starter[1]=1;head[1]=0;
    for (i=2;i<=10000;i++) starter[i]=starter[i-1]+cnt[i-1]+10,head[i]=starter[i]-1;
    for (i=1;i<=n;i++)
    {
        int w=a[i];
        q[++head[w]]=i;
        while (starter[w]+1<head[w] && calc(q[head[w]-2],q[head[w]-1])<calc(q[head[w]-1],q[head[w]])-eps) q[head[w]-1]=q[head[w]],head[w]--;
        while (starter[w]<head[w] && calc(q[head[w]-1],q[head[w]])-eps<2*vpos[i]) head[w]--;
        dp[i]=dp[q[head[w]]-1]+(long long)(vpos[i]-vpos[q[head[w]]]+1)*(long long)(vpos[i]-vpos[q[head[w]]]+1)*a[i];
    }
    printf("%lld\n",dp[n]);
    return 0;
}
