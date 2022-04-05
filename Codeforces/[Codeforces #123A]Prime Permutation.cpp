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

int kcnt[1048];
int prime[1048],tot;bool isprime[1048];
int cnt[30];
int n;char s[1048];
char ans[1048];
priority_queue<Pair> q;
vector<Pair> v;

int pre[1048];
inline int find_anc(int x)
{
	if (pre[x]!=x) pre[x]=find_anc(pre[x]);
	return pre[x];
}
inline void update(int x,int y)
{
	x=find_anc(x);y=find_anc(y);
	pre[x]=y;
}

void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=n;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && prime[j]*i<=n;j++)
		{
			isprime[prime[j]*i]=false;
			if (i%prime[j]==0) break;
		}
	}
}

bool cmp(Pair x,Pair y)
{
	return x.x>y.x;
}

int main ()
{
	int i,j,x;
	scanf("%s",s+1);
	n=strlen(s+1);
	for (i=1;i<=n;i++) pre[i]=i;
	for (i=1;i<=n;i++) cnt[s[i]-'a'+1]++;
	for (i=1;i<=26;i++) q.push(mp(cnt[i],i));
	sieve();
	for (i=1;i<=tot;i++)
		for (j=prime[i]*2;j<=n;j+=prime[i])
			update(prime[i],j);
	for (i=1;i<=n;i++)
	{
		x=find_anc(i);
		kcnt[x]++;
	}
	for (i=1;i<=n;i++) if (kcnt[i]) v.pb(mp(kcnt[i],i));
	sort(v.begin(),v.end(),cmp);
	for (i=0;i<v.size();i++)
	{
		if (q.top().x<v[i].x)
		{
			printf("NO\n");
			return 0;
		}
		Pair ins=q.top();q.pop();
		for (j=1;j<=n;j++)
			if (find_anc(j)==v[i].y) ans[j]='a'+ins.y-1;
		ins.x-=v[i].x;
		if (ins.x) q.push(ins);
	}
	printf("YES\n");
	puts(ans+1);
	return 0;
}
