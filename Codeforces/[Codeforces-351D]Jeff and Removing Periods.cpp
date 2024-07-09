#include <bits/stdc++.h>
#include <unordered_map>
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
// #define LOCAL true

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

const int MAXN=1e5;

int n,q,a[MAXN+48];

struct Query
{
	int l,r,ind;
	inline void input(int id) {Get(l);Get(r);ind=id;}
	inline bool operator < (const Query &other) const
	{
		int t1=l/magic,t2=other.l/magic;
		if (t1!=t2) return t1<t2;
		return r<other.r;
	}
}Q[MAXN+48];

int ans[MAXN+48];
int cou[MAXN+48],tnum;
unordered_map<int,int> Mp[MAXN+48];int cnt[MAXN+48];
deque<int> qq[MAXN+48];
int valid;
bool superf;

inline int calc() {return tnum+(valid==0);}

inline void addl(int num,int pos)
{
	cou[num]++;if (cou[num]==1) tnum++;
	if (qq[num].empty()) {valid++;qq[num].pf(pos);return;}
	int d=qq[num].front()-pos;
	Mp[num][d]++;if (Mp[num][d]==1) {cnt[num]++;if (cnt[num]==2) valid--;}
	qq[num].pf(pos);
}

inline void addr(int num,int pos)
{
	cou[num]++;if (cou[num]==1) tnum++;
	if (qq[num].empty()) {valid++;qq[num].pb(pos);return;}
	int d=pos-qq[num].back();
	Mp[num][d]++;if (Mp[num][d]==1) {cnt[num]++;if (cnt[num]==2) valid--;}
	qq[num].pb(pos);
}

inline void dell(int num,int pos)
{
	assert(!qq[num].empty());
	cou[num]--;if (!cou[num]) tnum--;
	if (qq[num].size()==1) {valid--;qq[num].pop_front();return;}
	int tmp=qq[num].front();qq[num].pop_front();int d=qq[num].front()-tmp;
	Mp[num][d]--;if (Mp[num][d]==0) {cnt[num]--;if (cnt[num]==1) valid++;}
}

inline void delr(int num,int pos)
{
	assert(!qq[num].empty());
	cou[num]--;if (!cou[num]) tnum--;
	if (qq[num].size()==1) {valid--;qq[num].pop_back();return;}
	int tmp=qq[num].back();qq[num].pop_back();int d=tmp-qq[num].back();
	Mp[num][d]--;if (Mp[num][d]==0) {cnt[num]--;if (cnt[num]==1) valid++;}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
#endif
	Get(n);for (register int i=1;i<=n;i++) Get(a[i]);
	Get(q);for (register int i=1;i<=q;i++) Q[i].input(i);
	sort(Q+1,Q+q+1);valid=tnum=0;
	memset(cou,0,sizeof(cou));memset(cnt,0,sizeof(cnt));
	int L=Q[1].l,R=Q[1].r;
	for (register int i=L;i<=R;i++) addr(a[i],i);
	ans[Q[1].ind]=calc();
	for (register int i=2;i<=q;i++)
	{
		while (L>Q[i].l) L--,addl(a[L],L);
		while (R<Q[i].r) R++,addr(a[R],R);
		while (L<Q[i].l) dell(a[L],L),L++;
		while (R>Q[i].r) delr(a[R],R),R--;
		ans[Q[i].ind]=calc();
	}
	for (register int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
