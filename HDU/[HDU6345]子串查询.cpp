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

const int MAXN=1e5;

char s[MAXN+48];int len,q;
int cnt[30][MAXN+48];

int main ()
{
	int i,j,l,r,ca;ca=getint();int cc=0;
	while (ca--)
	{
		len=getint();q=getint();
		scanf("%s",s+1);
		memset(cnt,0,sizeof(cnt));
		for (i=1;i<=26;i++)
			for (j=1;j<=len;j++)
				cnt[i][j]=cnt[i][j-1]+(s[j]=='A'+i-1);
		printf("Case #%d:\n",++cc);
		while (q--)
		{
			l=getint();r=getint();
			for (i=1;i<=26;i++)
				if(cnt[i][r]-cnt[i][l-1]) break;
			printf("%d\n",cnt[i][r]-cnt[i][l-1]);
		}
	}
	return 0;
}
