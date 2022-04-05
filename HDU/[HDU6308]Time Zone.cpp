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

int h,m;
int dh,dm;
char s[100];int len;
int sg;

int main ()
{
	int ca;ca=getint();
	while (ca--)
	{
		h=getint();m=getint();
		memset(s,'\0',sizeof(s));
		scanf("%s",s+1);len=strlen(s+1);
		sg=s[4]=='+'?1:-1;
		int i;
		for (i=5;i<=len && s[i]!='.';i++) {}
		dh=dm=0;
		if (i>len)
		{
			dh=0;
			for (i=5;i<=len;i++) dh=dh*10+s[i]-'0';
		}
		else
		{
			dh=0;
			for (int j=5;j<=i-1;j++) dh=dh*10+s[j]-'0';
			dm=60/10*(s[len]-'0');
		}
		if (sg==-1) dh=-dh,dm=-dm;
		dh-=8;
		m+=dm;h+=dh;
		while (m>=60) h++,m-=60;
		while (m<0) h--,m+=60;
		while (h>=24) h-=24;
		while (h<0) h+=24;
		if (h<10) printf("0");
		printf("%d:",h);
		if (m<10) printf("0");
		printf("%d\n",m);
	}
	return 0;
}
