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

namespace DSU
{
	int pre[30],maxn[30];
	inline void init (int coef[]) {for (register int i=1;i<=26;i++) pre[i]=i,maxn[i]=coef[i];}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;maxn[y]=max(maxn[y],maxn[x]);}
}

class GooseTattarrattatDiv1
{
	public:
		char s[148];int len;
		int Mask[148];int cnt[30];
		inline int getmin(string ss)
		{
			len=int(ss.size());int i,j;
			memset(cnt,0,sizeof(cnt));
			for (i=1;i<=len;i++) s[i]=ss[i-1],cnt[s[i]-'a'+1]++;
			DSU::init(cnt);int res=0;
			for (i=1;i<=26;i++)
			{
				for (j=1;j<=len;j++)
					Mask[j]=(s[j]=='a'+i-1);
				for (j=1;j<=len;j++)
					if (Mask[j] && !Mask[len-j+1] && DSU::find_anc(s[j]-'a'+1)!=DSU::find_anc(s[len-j+1]-'a'+1))
						DSU::update(s[j]-'a'+1,s[len-j+1]-'a'+1);
			}
			for (i=1;i<=26;i++) if (DSU::pre[i]==i) res+=DSU::maxn[i];
			res=len-res;
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	GooseTattarrattatDiv1 A;
	string s;
	while (cin>>s) printf("%d\n",A.getmin(s));
	return 0;
}*/
