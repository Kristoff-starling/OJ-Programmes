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

int n;
char s1[148],s2[148];
int len1,len2;

struct TRANSFORM
{
	char from;
	char to[5];
}a[148];

int dp[148][148];
bool dpa[148][148][30],dpa2[148][148];
bool dpb[148][148][30],dpb2[148][148];

int main ()
{
	int i,j,prei,prej,k,clen,ch;
	scanf("%s",s1+1);scanf("%s",s2+1);
	len1=strlen(s1+1);len2=strlen(s2+1);
	n=getint();string s;
	for (i=1;i<=n;i++)
	{
		cin>>s;
		a[i].from=s[0];a[i].to[1]=s[3];a[i].to[2]=s[4];
	}
	for (clen=1;clen<=len1;clen++)
		for (i=1;i<=len1-clen+1;i++)
			for (ch=1;ch<=26;ch++)
			{
				if (clen==1)
				{
					if (s1[i]-'a'+1==ch) dpa[i][i][ch]=true; else dpa[i][i][ch]=false;
					continue;
				}
				for (j=1;j<=clen-1;j++)
					for (k=1;k<=n;k++)
						if (a[k].from-'a'+1==ch && dpa[i][i+j-1][a[k].to[1]-'a'+1] && dpa[i+j][i+clen-1][a[k].to[2]-'a'+1])
							dpa[i][i+clen-1][ch]=true;
			}
	for (clen=1;clen<=len2;clen++)
		for (i=1;i<=len2-clen+1;i++)
			for (ch=1;ch<=26;ch++)
			{
				if (clen==1)
				{
					if (s2[i]-'a'+1==ch) dpb[i][i][ch]=true; else dpb[i][i][ch]=false;
					continue;
				}
				for (j=1;j<=clen-1;j++)
					for (k=1;k<=n;k++)
						if (a[k].from-'a'+1==ch && dpb[i][i+j-1][a[k].to[1]-'a'+1] && dpb[i+j][i+clen-1][a[k].to[2]-'a'+1])
							dpb[i][i+clen-1][ch]=true;
			}
	for (i=1;i<=len1;i++)
		for (j=1;j<=len2;j++)
		{
			dp[i][j]=INF;
			for (ch=1;ch<=26;ch++)
				if (dpa[1][i][ch] && dpb[1][j][ch]) dp[i][j]=1;
			for (prei=1;prei<=i-1;prei++)
				for (prej=1;prej<=j-1;prej++)
					for (ch=1;ch<=26;ch++)
						if (dpa[prei+1][i][ch] && dpb[prej+1][j][ch])
							dp[i][j]=min(dp[i][j],dp[prei][prej]+1);
		}
	if (dp[len1][len2]>=INF) printf("-1\n"); else printf("%d\n",dp[len1][len2]);
	return 0;
}