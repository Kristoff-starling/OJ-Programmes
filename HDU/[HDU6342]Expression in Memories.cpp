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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=500;

int len;
char s[MAXN+48];

inline bool isope(char ch) {return ch=='+' || ch=='*';}

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		scanf("%s",s+1);len=strlen(s+1);
		if (isope(s[1]) || isope(s[len])) {puts("IMPOSSIBLE");continue;}
		for (i=1;i<=len-1;i++) if (isope(s[i]) && isope(s[i+1])) break;
		if (i<=len-1) {puts("IMPOSSIBLE");continue;}
		s[0]='+';
		for (i=0;i<=len-2;i++)
			if (isope(s[i]) && s[i+1]=='0')
			{
				if (isdigit(s[i+2])) break;
				if (isope(s[i+2])) continue;
				s[i+2]='+';
				if (i+2==len || isope(s[i+3])) break;
			}
		if (i<=len-2) {puts("IMPOSSIBLE");continue;}
		for (i=1;i<=len;i++) if (s[i]=='?') s[i]='8';
		printf("%s\n",s+1);
	}
	return 0;
}
