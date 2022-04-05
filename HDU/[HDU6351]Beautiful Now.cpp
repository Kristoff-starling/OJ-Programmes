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

int n,k,tot;
int num[48];int pw[48];

inline void Decompose()
{
	int tt=n;tot=0;
	while (tt) num[++tot]=tt%10,tt/=10;
	reverse(num+1,num+tot+1);
//	for (int i=1;i<=tot;i++) cout<<num[i]<<' ';
//	cout<<endl;
}

int maxn,minn;

inline void dfs(int cur,int k,int curnum)
{
	if (!k || cur==tot) {maxn=max(maxn,curnum);minn=min(minn,curnum);return;}
	dfs(cur+1,k,curnum);
	for (register int i=cur+1;i<=tot;i++)
		if (num[cur]!=num[i])
		{
			if (cur==1 && !num[i]) continue;
			curnum-=num[cur]*pw[tot-cur];curnum-=num[i]*pw[tot-i];
			swap(num[cur],num[i]);
			curnum+=num[cur]*pw[tot-cur];curnum+=num[i]*pw[tot-i];
			dfs(cur+1,k-1,curnum);
			curnum-=num[cur]*pw[tot-cur];curnum-=num[i]*pw[tot-i];
			swap(num[cur],num[i]);
			curnum+=num[cur]*pw[tot-cur];curnum+=num[i]*pw[tot-i];
		}
}

int main ()
{
	int i,ca;ca=getint();
	pw[0]=1;for (i=1;i<=9;i++) pw[i]=pw[i-1]*10;
	while (ca--)
	{
		n=getint();k=getint();
		Decompose();k=min(k,tot-1);
		maxn=minn=n;
		dfs(1,k,n);
		printf("%d %d\n",minn,maxn);
	}
	return 0;
}
