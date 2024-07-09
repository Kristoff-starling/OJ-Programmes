#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

char s[1048];
int numq[1048],numa[1048];
int q_top,a_top;
int len;

int main ()
{
	int i,j,k;
	int ans=0;
	scanf("%s",s+1);
	len=strlen(s+1);
	for (i=1;i<=len;i++)
		if (s[i]=='Q')
		{
			numq[++q_top]=i;
		}
		else if (s[i]=='A')
		{
			numa[++a_top]=i;
		}
	for (i=1;i<=q_top-1;i++)
		for (j=i+1;j<=q_top;j++)
			for (k=1;k<=a_top;k++)
			{
				if (numq[i]<numa[k] && numa[k]<numq[j]) ans++;
			}
	printf("%d\n",ans);
	return 0;
}
