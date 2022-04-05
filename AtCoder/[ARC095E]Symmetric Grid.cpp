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
const LL LINF=2e16;
const int INF=1e9;
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
char s[48][48];
int r[48][48],c[48][48];
bool ispalindromer[48],ispalindromec[48];
bool samer[48][48],samec[48][48];
int rind,cind;
Pair rpos[48],cpos[48];
bool vr[48],vc[48];

inline bool check_samer(int ind1,int ind2)
{
	for (register int i=1;i<=26;i++) if (r[ind1][i]!=r[ind2][i]) return false;
	return true;
}

inline bool check_samec(int ind1,int ind2)
{
	for (register int i=1;i<=26;i++) if (c[ind1][i]!=c[ind2][i]) return false;
	return true;
}

inline bool check_palindromer(int ind)
{
	int cnt=0;
	for (register int i=1;i<=26;i++) cnt+=(r[ind][i]%2==1);
	if (cnt==0) return true;
	if (cnt==1 && m&1) return true;
	return false;
}

inline bool check_palindromec(int ind)
{
	int cnt=0;
	for (register int i=1;i<=26;i++) cnt+=(c[ind][i]%2==1);
	if (cnt==0) return true;
	if (cnt==1 && n&1) return true;
	return false;
}

inline void init()
{
	int i,j;
	for (i=1;i<=n;i++) ispalindromer[i]=check_palindromer(i);
	for (i=1;i<=m;i++) ispalindromec[i]=check_palindromec(i);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (i!=j) samer[i][j]=check_samer(i,j);
	for (i=1;i<=m;i++)
		for (j=1;j<=m;j++)
			if (i!=j) samec[i][j]=check_samec(i,j);
}

bool superf=false;

inline bool check()
{
	int i,j;
	for (i=1;i<=rind;i++)
		for (j=1;j<=cind;j++)
		{
			if (s[rpos[i].x][cpos[j].x]!=s[rpos[i].y][cpos[j].y]) return false;
			if (s[rpos[i].x][cpos[j].y]!=s[rpos[i].y][cpos[j].x]) return false;
		}
	for (j=1;j<=cind;j++)
		for (i=1;i<=rind;i++)
		{
			if (s[rpos[i].x][cpos[j].x]!=s[rpos[i].y][cpos[j].y]) return false;
			if (s[rpos[i].y][cpos[j].x]!=s[rpos[i].x][cpos[j].y]) return false;
		}
	return true;
}

inline void dfs2(int cur,int fl)
{
	if (cur==m+1)
	{
		if (check()) superf=true;
		return;
	}
	if (vc[cur]) {dfs2(cur+1,fl);return;}
	if (fl==1 && ispalindromec[cur])
	{
		cpos[++cind]=mp(cur,cur);
		vc[cur]=true;
		dfs2(cur+1,0);
		if (superf) return;
		vc[cur]=false;
		cind--;
	}
	for (register int i=cur+1;i<=m;i++)
		if (!vc[i] && samec[i][cur])
		{
			vc[cur]=true;vc[i]=true;
			cpos[++cind]=mp(cur,i);
			dfs2(cur+1,fl);
			if (superf) return;
			vc[cur]=false;vc[i]=false;
			cind--;
		}
}

inline void dfs1(int cur,int fl)
{
	if (cur==n+1) {dfs2(1,m%2);return;}
	if (vr[cur]) {dfs1(cur+1,fl);return;}
	if (fl==1 && ispalindromer[cur])
	{
		rpos[++rind]=mp(cur,cur);
		vr[cur]=true;
		dfs1(cur+1,0);
		if (superf) return;
		vr[cur]=false;
		rind--;
	}
	for (register int i=cur+1;i<=n;i++)
		if (!vr[i] && samer[i][cur])
		{
			rpos[++rind]=mp(cur,i);
			vr[cur]=true;vr[i]=true;
			dfs1(cur+1,fl);
			if (superf) return;
			vr[cur]=false;vr[i]=false;
			rind--;
		}
}

int main ()
{
	int i,j;
	n=getint();m=getint();
	memset(r,0,sizeof(r));memset(c,0,sizeof(c));
	for (i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for (j=1;j<=m;j++) r[i][s[i][j]-'a'+1]++,c[j][s[i][j]-'a'+1]++;
	}
	init();
	dfs1(1,n%2);
	printf(superf?"YES\n":"NO\n");
	return 0;
}
