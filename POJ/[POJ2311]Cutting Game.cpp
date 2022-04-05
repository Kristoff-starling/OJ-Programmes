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
#define DEBUG(...)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m;
int grundy[248][248];

inline int calc_grundy(int w,int h)
{
	if (grundy[w][h]!=-1) return grundy[w][h];
	int i;set<int> s;
	for (i=w-2;i>=2;i--) s.insert(calc_grundy(i,h)^calc_grundy(w-i,h));
	for (i=h-2;i>=2;i--) s.insert(calc_grundy(w,i)^calc_grundy(w,h-i));
	int res=0;
	while (s.count(res)) res++;
	grundy[w][h]=res;
	return res;
}

int main ()
{
	memset(grundy,-1,sizeof(grundy));
	while (scanf("%d%d",&n,&m)!=EOF)
		printf(calc_grundy(n,m)?"WIN\n":"LOSE\n");
	return 0;
}
