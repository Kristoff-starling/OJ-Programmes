#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,m;
unordered_set<int> s[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

int main ()
{
	Get(n);Get(m);int op,x,y;
	for (register int i=1;i<=n;i++) s[i].clear();
	DSU::init();
	for (register int i=1;i<=m;i++)
	{
		Get(op);Get(x);Get(y);
		x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (op==1)
		{
			if (s[x].find(y)!=s[x].end() || s[y].find(x)!=s[y].end()) {puts("NO");continue;}
			puts("YES");
			if (x==y) continue;
			if (int(s[x].size())>int(s[y].size())) swap(x,y);
			for (auto item : s[x]) s[item].erase(x),s[item].insert(y);
			for (auto item : s[x]) s[y].insert(item);
			DSU::update(x,y);
		}
		else
		{
			if (x==y) {puts("NO");continue;}
			puts("YES");
			s[x].insert(y);s[y].insert(x);
		}
	}
	return 0;
}
