#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define x first
#define y second
using namespace std;

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

typedef unsigned long long ull;
typedef pair<int,int> Pair;

const int MAXN=4e4;

int prime[MAXN+48],tot;bool isprime[MAXN+48];

inline void sieve()
{
	memset(isprime,true,sizeof(isprime));tot=0;
	for (register int i=2;i<=MAXN;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
}

int n;
vector<Pair> v;

inline void Decompose(int n)
{
	v.clear();
	for (register int i=1;i<=tot;i++)
		if (n%prime[i]==0)
		{
			int cnt=0;
			while (n%prime[i]==0) cnt++,n/=prime[i];
			v.pb(mp(prime[i],cnt));
		}
	if (n!=1) v.pb(mp(n,1));
}

int main ()
{
	sieve();
	int t;Get(t);
	while (t--)
	{
		Get(n);Decompose(n);ull sum1=1,sum2=1;
		for (register int i=0;i<int(v.size());i++)
		{
			ull pw=1,tmp=1;
			for (register int j=1;j<=v[i].y;j++) pw=pw*v[i].x*v[i].x,tmp+=pw;
			sum1*=(v[i].y+1);sum2*=tmp;
		}
		cout<<sum2-sum1*n<<endl;
	}
	return 0;
}
