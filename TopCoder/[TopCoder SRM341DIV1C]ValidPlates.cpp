#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
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
const int MOD=1e9+7;
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

inline LL add(LL x,LL y)
{
	LL res=x+y;
	if (res>2e9) return LINF; else return res;
}

inline LL mul(LL x,LL y)
{
	if (!x || !y) return 0;
	if (x>2e9 || y>2e9) return LINF;
	LL res=x*y;
	if (res>2e9) return LINF; else return res;
}

struct Matrix
{
	LL b[14][14];
	inline void clear() {memset(b,0,sizeof(b));}
	inline void init_I() {clear();for (register int i=0;i<=10;i++) b[i][i]=1;}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();int i,j;
		for (i=0;i<=10;i++)
			for (j=0;j<=10;j++)
				res.b[i][j]=add(res.b[i][j],add(b[i][j],ma.b[i][j]));
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();int i,j,k;
		for (i=0;i<=10;i++)
			for (j=0;j<=10;j++)
				for (k=0;k<=10;k++)
					res.b[i][j]=add(res.b[i][j],mul(b[i][k],ma.b[k][j]));
		return res;
	}
}trans,sta,Ma;

inline Matrix quick_pow(Matrix ma,LL y)
{
	Matrix res;res.init_I();
	while (y)
	{
		if (y&1) res=res*ma,y--;
		ma=ma*ma;y>>=1;
	}
	return res;
}

bool ga[48][48];
vector<int> valid[48];

class ValidPlates
{
	string s,res;
	inline void init_taboo()
	{
		memset(ga,true,sizeof(ga));
		for (register int i=0;i<int(s.size());i+=3)
			ga[s[i]-'0'][s[i+1]-'0']=false;
	}
	inline void getdigit(int len,int lim,int rnk,bool isfirst,int last)
	{
		if (len<lim) return;
		int i,j;LL sum=0,pre=0;
		for (i=(isfirst?1:0);i<=9;i++)
			if (isfirst || ga[last][i])
			{
				sta.clear();sta.b[0][i]=1;Ma=sta*quick_pow(trans,len-1);
				for (j=0;j<=9;j++) sum=add(sum,Ma.b[0][j]);
				if (sum>=rnk) break;
				pre=sum;
			}
		assert(i<=9);
		res+=string(1,'0'+i);rnk-=pre;
		getdigit(len-1,lim,rnk,false,i);
	}
	public:
		inline string getPlate(vector<string> taboo,int rnk)
		{
			int i,j;
			if (rnk<=9) return string(1,'0'+rnk);
			s="";res="";for (i=0;i<int(taboo.size());i++) s+=taboo[i],s+=" ";
			init_taboo();
			sta.clear();for (i=1;i<=9;i++) sta.b[0][i]=1;
			trans.clear();
			for (i=0;i<=9;i++)
				for (j=0;j<=9;j++)
					if (ga[i][j]) trans.b[i][j]++;
			for (i=0;i<=10;i++) trans.b[i][10]=1;
			Ma=sta*quick_pow(trans,2e9-1);LL sum=0;
			for (i=0;i<=10;i++) sum=add(sum,Ma.b[0][i]);
			if (sum<rnk) return "";
			LL l=2,r=2e9,mid,anslen=1,anssum=9;
			while (l<=r)
			{
				mid=(l+r)>>1;
				Ma=sta*quick_pow(trans,mid-1);
				sum=0;for (i=0;i<=10;i++) sum=add(sum,Ma.b[0][i]);
				if (sum<rnk) anslen=mid,l=mid+1,anssum=sum; else r=mid-1;
			}
			anslen++;rnk-=anssum;
			Ma=sta*quick_pow(trans,52);sum=0;
			for (i=0;i<=10;i++) sum=add(sum,Ma.b[0][i]);
			Ma=sta*quick_pow(trans,53);sum=0;
			for (i=0;i<=10;i++) sum=add(sum,Ma.b[0][i]);
			if (anslen>50) getdigit(anslen,anslen-46,rnk,true,0); else getdigit(anslen,1,rnk,true,0);
			if (anslen>50) res+="...";
			return res;
		}
};

/*---Debug Part---*/
int main ()
{
	vector<string> vv;int x,xx;
	ValidPlates A;
	/*while (cin>>xx)
	{
		vv.clear();string ss;
		getchar();
		while (xx--)
		{
			getline(cin,ss);
			vv.pb(ss);
		}
		cin>>x;
		cout<<A.getPlate(vv,x)<<endl;
	}*/
	//vv.pb("00 01 02 03 04 05 07 08 09");
	/*
	vv.pb("10 11 12 13 14 15 16 17 18 19");
	vv.pb("20 21 22 23 24 25 26 27 28 29");
	vv.pb("30 31 32 33 34 35 36 37 38 39");
	vv.pb("40 41 42 43 44 45 46 47 48 49");
	vv.pb("50 51 52 53 54 55 56 57 58 59");
	vv.pb("60 61 62 63 64 65 66 67 68 69");
	vv.pb("70 71 72 73 74 75 76 77 78 79");
	vv.pb("80 81 82 83 84 85 86 87 88 89");
	vv.pb("90 91 92 93 94 95 96 97 98 99");
	x=10;
	*/
	vv.clear();
vv.pb("00 01 02 05 07 08 09");
vv.pb("10 11 13 14 15 17 18 19");
vv.pb("20 21 22 23 24 25 26 27 28 29");
vv.pb("30 32 34 35 36 37 38 39");
vv.pb("40 41 42 44 45 46 47 48 49");
vv.pb("50 52 53 55 56 57 58 59");
vv.pb("60 61 62 63 65 66 67 68 69");
vv.pb("70 73 74 75 77 78 79");
vv.pb("81 82 84 85 86 87 88 89");
vv.pb("90 91 92 93 96 97");
x=2000000000;
	cout<<A.getPlate(vv,x)<<endl;
	return 0;
}
/*
4
00 01 02 03 04 05 06 07 08 09 11 12 13 14 15 16 17
18 19 22 23 24 25 26 27 28 29 33 34 35 36 37 38 39
44 45 46 47 48 49 55 56 57 58 59 66 67 68 69 77 78
79 88 89 99 99 99 99 99
1023
*/
/*
10
00 01 02 03 04 05 07 08 09
10 11 12 13 14 15 17 18 19
20 21 22 24 25 26 27 28 29
30 31 32 33 34 36 37 38 39
41 43 45 46 48
52 53 54 55 56 58 59
60 61 63 64 66 67 68 69
70 72 73 74 75 76 77 78
80 81 82 83 84 86 87 88 89
90 91 92 94 95 96 97 98
2000000000
*/
