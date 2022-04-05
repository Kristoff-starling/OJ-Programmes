#include <cassert>
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
#include <ctime>
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
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
set<int> s;
char ss[10];
int tot=0,a[48];
int pw2[21];
Pair valid[1048];int vtot;
bool exist[1048];
typedef pair<Pair,int> PII;
PII A[1048],tmp[1048];int atot,ttot;
int suf[1048];int tar;

inline bool cmp(Pair x,Pair y) {return __builtin_popcount(x.x)<__builtin_popcount(y.x);}
int ans=0;
double t;int ca;

int cc=0;
bool Break;

inline void dfs(int step,int Mask,int curans)
{
	if (cc>=100000)
	{
		cc=0;
		if ((clock()-t)/CLOCKS_PER_SEC>double(0.35)/ca) {Break=true;return;}
	}
	++cc;
	if (curans>=ans) return;
	if (Mask==tar) {ans=curans;return;}
	if (step>atot) return;
	if ((Mask|suf[step])!=tar) return;
	dfs(step+1,Mask,curans);
	if (Break) return;
	if ((Mask|A[step].y)!=Mask) dfs(step+1,Mask|A[step].y,curans+__builtin_popcount(A[step].x.x));
}

int main ()
{
	int i,j,Mask,sub;ca=getint();
	pw2[0]=1;for (i=1;i<=20;i++) pw2[i]=pw2[i-1]*2;
	while (ca--)
	{
		t=clock();
		n=getint();m=getint();s.clear();
		for (i=1;i<=m;i++)
		{
			scanf("%s",ss+1);Mask=0;
			for (j=1;j<=n;j++)
				if (isupper(ss[j])) Mask|=(1<<(j-1));
			s.insert(Mask);
		}
	t=clock();
		tot=0;
		for (set<int>::iterator iter=s.begin();iter!=s.end();iter++) a[++tot]=(*iter);
		if (tot==32) {puts("0");continue;}
		vtot=0;
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
			for (sub=Mask;;sub=(sub-1)&Mask)
			{
				int cnt=0;
				for (i=1;i<=tot;i++)
					if ((a[i]&Mask)==sub) cnt++;
				if (cnt==pw2[n-__builtin_popcount(Mask)]) valid[++vtot]=mp(Mask,sub);
				if (!sub) break;
			}
		for (i=1;i<=vtot;i++) exist[i]=true;
		sort(valid+1,valid+vtot+1,cmp);
		for (i=1;i<=vtot-1;i++)
			if (exist[i])
				for (j=i+1;j<=vtot;j++)
					if ((valid[j].x|valid[i].x)==valid[j].x && (valid[j].y&valid[i].x)==valid[i].y) exist[j]=false;
		atot=0;for (i=1;i<=vtot;i++) if (exist[i]) A[++atot].x=valid[i];
		for (i=1;i<=atot;i++)
		{
			A[i].y=0;
			for (j=1;j<=tot;j++)
				if ((a[j]&A[i].x.x)==A[i].x.y) A[i].y|=(1<<(j-1));
		}
		for (i=1;i<=atot;i++) exist[i]=true;
		for (i=1;i<=atot-1;i++)
			for (j=i+1;j<=atot;j++)
				if ((A[i].y|A[j].y)==A[i].y) exist[j]=false;
		ttot=0;
		for (i=1;i<=atot;i++) if (exist[i]) tmp[++ttot]=A[i];
		atot=ttot;for (i=1;i<=atot;i++) A[i]=tmp[i];
		suf[atot]=A[atot].y;
		for (i=atot-1;i>=1;i--) suf[i]=(suf[i+1]|A[i].y);
		ans=INF;tar=(1ll<<tot)-1;
		Break=false;cc=0;dfs(1,0,0);
		printf("%d\n",ans);
	}
	return 0;
}
