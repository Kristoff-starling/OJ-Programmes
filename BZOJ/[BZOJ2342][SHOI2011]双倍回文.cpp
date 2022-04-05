#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <functional>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <vector>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

char ss[1200048],s[1200048];int slen,len;
int RL[1200048];
multiset<Pair> S;
Pair valid[500048];int tot;

int main ()
{
	int i,pos,maxright;
	scanf("%d%s",&slen,ss+1);
	init_hash();
	len=1;s[1]='$';
	for (i=1;i<=slen;i++) s[++len]=ss[i],s[++len]='$';
	pos=maxright=0;
	for (i=1;i<=len;i++)
	{
		if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=len && s[i+RL[i]]==s[i-RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
	for (i=1;i<=len;i++)
		if (s[i]=='$') valid[++tot]=mp(i/2-(RL[i]-1)/2+1,i/2);
	sort(valid+1,valid+tot+1);S.clear();
	int ans=0;
	int pt=1;multiset<Pair>::iterator iter,tmp;
	for (i=1;i<=len;i++)
		if (s[i]=='$')
		{
			while (pt<=tot && valid[pt].x<=i/2+1) S.insert(mp(valid[pt].y+(RL[valid[pt].y*2+1]-1)/2,valid[pt].y)),pt++;
			iter=S.lower_bound(mp(i/2+(RL[i]-1)/2+1,-1));--iter;
			bool f=true;
			while (iter->y<=i/2)
			{
				if (iter==S.begin()) f=false;
				tmp=iter;--tmp;
				S.erase(iter);iter=tmp;
				if (!f) break;
			}
			if (f) ans=max(ans,(iter->y-i/2)*4);
		}
	printf("%d\n",ans);
	return 0;
}
