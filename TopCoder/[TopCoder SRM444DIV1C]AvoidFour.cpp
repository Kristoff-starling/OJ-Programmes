#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

struct AvoidFour
{
	inline LL mod(LL x)
	{
		while (x>=MOD) x-=MOD;
		while (x<0) x+=MOD;
		return x;
	}
	inline LL gcd(LL x,LL y)
	{
		return y==0?x:gcd(y,x%y);
	}
	inline LL lcm(LL x,LL y)
	{
		return x/gcd(x,y)*y;
	}
	struct Matrix
	{
		LL b[6][6];
		inline Matrix operator * (Matrix ma)
		{
			Matrix res;int i,j,k;
			for (i=1;i<=5;i++)
				for (j=1;j<=5;j++)
				{
					res.b[i][j]=0ll;
					for (k=1;k<=5;k++)
						res.b[i][j]=(res.b[i][j]+(b[i][k]*ma.b[k][j])%MOD)%MOD;
				}
			return res;
		}
		inline Matrix operator + (Matrix ma)
		{
			Matrix res;int i,j;
			for (i=1;i<=5;i++)
				for (j=1;j<=5;j++)
					res.b[i][j]=(b[i][j]+ma.b[i][j])%MOD;
			return res;
		}
	}Ma,sMa;
	void print_matrix(Matrix ma)
	{
		int i,j;
		for (i=1;i<=5;i++)
		{
			for (j=1;j<=5;j++)
				cout<<ma.b[i][j]<<' ';
			cout<<endl;
		}
	}
	inline void clear_matrix(Matrix &ma)
	{
		memset(ma.b,0ll,sizeof(ma.b));
	}
	void memset_Imatrix(Matrix &ma)
	{
		clear_matrix(ma);
		for (int i=1;i<=5;i++)
			ma.b[i][i]=1ll;
	}
	void memset_Smatrix(Matrix &ma)
	{
		clear_matrix(ma);
		ma.b[1][5]=1ll;
	}
	void memset_FSmatrix(Matrix &ma)
	{
		clear_matrix(ma);
		ma.b[1][1]=8ll;ma.b[1][2]=1ll;
	}
	void init_matrix()
	{
		clear_matrix(Ma);
		Ma.b[1][1]=9;Ma.b[1][2]=1;
		Ma.b[2][1]=9;Ma.b[2][3]=1;
		Ma.b[3][1]=9;Ma.b[3][4]=1;
		Ma.b[4][1]=9;
		Ma.b[5][1]=8;Ma.b[5][2]=1;Ma.b[5][5]=1;
	}
	Matrix quick_pow(Matrix ma,LL y)
	{
		Matrix res;memset_Imatrix(res);
		while (y)
		{
			if (y&1)
			{
				res=res*ma;
				y--;
			}
			ma=ma*ma;
			y>>=1;
		}
		return res;
	}
	LL num[20];int tot;
	int init_num(LL lim)
	{
		LL cur=44;int i;
		for (i=1;cur<=lim;i++,cur=cur*10+4)
			num[i]=cur;
		return i-1;
	}
	Matrix solve(LL left,LL right,LL base)
	{
		Matrix res;
		if (left==right)
		{
			memset_Imatrix(res);
			return res;
		}
		LL mid=(left+right)>>1;if ((right-left+1)%2==1) mid--;
		Matrix res1,res2;
		res1=solve(left,mid,base);res2=res1*quick_pow(Ma,base*(mid+1));
		res=res1+res2;
		if ((right-left+1)%2==1) res=res+quick_pow(Ma,base*right);
		return res;
	}
	LL doit(LL digits,LL base)
	{
		memset_FSmatrix(sMa);
		LL rght=digits/base;rght--;
		sMa=sMa*quick_pow(Ma,base-1);
		sMa=sMa*solve(0,rght,base);
		LL res=0;
		for (int i=1;i<=4;i++) res=mod(res+sMa.b[1][i]);
		return res;
	}
	int count(LL digits)
	{
		init_matrix();
		memset_Smatrix(sMa);
		LL ans=0;int i;
		Matrix mul=quick_pow(Ma,digits);
		sMa=sMa*mul;
		for (i=1;i<=4;i++) ans=mod(ans+sMa.b[1][i]);
		if (digits<44) return int(ans);
		tot=init_num(digits);
		LL Mask;
		for (Mask=0;Mask<=(1ll<<tot)-1;Mask++)
		{
			LL Lcm=1;int cnt=0;bool f=true;
			for (i=1;i<=tot;i++)
				if (Mask&(1<<(i-1)))
				{
					cnt++;
					Lcm=lcm(Lcm,num[i]);
					if (Lcm>digits) {f=false;break;}
				}
			if (!f || cnt==0) continue;
			if (cnt%2==0) ans=mod(ans+doit(digits,Lcm)); else ans=mod(ans-doit(digits,Lcm));
		}
		return int(ans);
	}
};

/*---Debug Part---*/
/*int main ()
{
	AvoidFour A;LL digits;
	while (scanf("%lld",&digits)!=EOF)
		cout<<A.count(digits)<<endl;
	return 0;
}*/
