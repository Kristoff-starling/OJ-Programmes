#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=2e5;

int n;
vector<int> v[MAXN+48];
int M[MAXN+48];

multiset<int> s[MAXN+48];
int id[MAXN+48];

int seq1[MAXN+48],seq2[MAXN+48];

inline int merge(int root1,int root2)
{
	if (!root1 || !root2) return root1^root2;
	if (int(s[root1].size())<int(s[root2].size())) swap(root1,root2);
	int sz=int(s[root2].size()),cnt=1;
	for (multiset<int>::iterator iter1=s[root1].begin(),iter2=s[root2].begin();cnt<=sz;cnt++,iter1++,iter2++)
		seq1[cnt]=-(*iter1),seq2[cnt]=-(*iter2);
	for (register int i=1;i<=sz;i++) s[root1].erase(s[root1].begin());
	for (register int i=1;i<=sz;i++) s[root1].insert(-max(seq1[i],seq2[i]));
	return root1;
}

inline void dfs(int cur)
{
	if (!int(v[cur].size()))
	{
		id[cur]=cur;
		s[cur].insert(-M[cur]);
		return;
	}
	id[cur]=0;
	for (auto y : v[cur]) dfs(y),id[cur]=merge(id[cur],id[y]);
	s[id[cur]].insert(-M[cur]);
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n);int x;
	for (register int i=1;i<=n;i++) Get(M[i]);
	for (register int i=2;i<=n;i++) Get(x),v[x].pb(i);
	dfs(1);
	LL ans=0;
	for (multiset<int>::iterator iter=s[id[1]].begin();iter!=s[id[1]].end();iter++) ans-=(*iter);
	printf("%lld\n",ans);return 0;
}
