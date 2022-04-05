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

const int MOD=600921647;
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

int cnt[20][20],num[20];
bool trans[20][20];
int gnum,tmax;

struct ShuffledPlaylist
{
	/*---Read Part---*/
	void Clear()
	{
		memset(cnt,0,sizeof(cnt));
		memset(num,0,sizeof(num));
		memset(trans,false,sizeof(trans));
	}
	int STRING_TO_NUM(string s)
	{
		int i,res=0;
		for (i=0;i<int(s.size());i++)
			res=res*10+s[i]-'0';
		return res;
	}
	void doit(string s)
	{
		string s1,s2;int pos=s.find(' ');
		s1=s.substr(0,pos);s2=s.substr(pos+1,int(s.size())-1-pos);
		int genre=STRING_TO_NUM(s1),len=STRING_TO_NUM(s2);++genre;
		cnt[genre][len]++;num[genre]++;
		tmax=max(tmax,len);
	}
	void init_read(vector<string> songs,vector<string> transitions)
	{
		int i,j,ll=0;
		string ss="";
		for (i=0;i<int(songs.size());i++) ss+=songs[i];
		for (i=0;i<int(ss.size());i++)
			if (ss[i]==',')
			{
				doit(ss.substr(ll,i-1-ll+1));
				ll=i+1;
			}
		doit(ss.substr(ll,int(ss.size())-1-ll+1));
		gnum=int(transitions.size());
		for (i=0;i<int(transitions.size());i++)
			for (j=0;j<int(transitions[i].size());j++)
				trans[i+1][j+1]=(transitions[i][j]=='Y'?true:false);
	}
	/*---Matrix Part---*/
	inline int Pair_to_Ind(int x,int y) {return (x-1)*tmax+y;}
	inline Pair Ind_to_Pair(int ind) {return mp(ind%tmax?ind/tmax+1:ind/tmax,ind%tmax?ind%tmax:tmax);}
	struct Matrix
	{
		LL b[90][90];
		inline void Clear()
		{
			memset(b,0,sizeof(b));
		}
		inline void memset_Imatrix()
		{
			int i;
			for (i=1;i<=gnum*tmax;i++)
				b[i][i]=1;
		}
		inline void construct_starter()
		{
			int i,j;
			for (i=1;i<=gnum;i++)
				for (j=1;j<=tmax;j++)
				{
					int ind=(i-1)*tmax+j;
					b[1][ind]=cnt[i][j];
				}
		}
		inline Matrix operator * (Matrix ma)
		{
			Matrix res;res.Clear();
			int i,j,k;
			for (i=1;i<=gnum*tmax;i++)
				for (j=1;j<=gnum*tmax;j++)
					for (k=1;k<=gnum*tmax;k++)
						res.b[i][j]=(res.b[i][j]+(b[i][k]*ma.b[k][j])%MOD)%MOD;
			return res;
		}
		inline Matrix operator + (Matrix ma)
		{
			Matrix res;res.Clear();
			int i,j;
			for (i=1;i<=gnum*tmax;i++)
				for (j=1;j<=gnum*tmax;j++)
					res.b[i][j]=(b[i][j]+ma.b[i][j])%MOD;
			return res;
		}
	}Ma,sMa;
	void print_matrix(Matrix ma)
	{
		int i,j;
		for (i=1;i<=gnum*tmax;i++)
		{
			for (j=1;j<=gnum*tmax;j++)
				cout<<ma.b[i][j]<<' ';
			cout<<endl;
		}
	}
	void init_matrix()
	{
		Ma.Clear();
		int i,j,cur_genre,cur_time;Pair res;
		for (i=1;i<=gnum*tmax;i++)
		{
			res=Ind_to_Pair(i);
			cur_genre=res.x;cur_time=res.y;
			if (cur_time!=tmax) Ma.b[Pair_to_Ind(cur_genre,cur_time+1)][i]++;
			for (j=1;j<=gnum;j++)
				if (trans[j][cur_genre])
					Ma.b[Pair_to_Ind(j,1)][i]+=cnt[cur_genre][cur_time];
		}
	}
	Matrix quick_pow(Matrix ma,LL y)
	{
		Matrix res;
		res.Clear();res.memset_Imatrix();
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
	/*---Solve Part---*/
	Matrix solve(LL left,LL right)
	{
		Matrix res;res.Clear();
		if (left==right)
		{
			res.memset_Imatrix();
			return res;
		}
		LL mid=(left+right)>>1;if ((right-left+1)%2==1) mid--;
		Matrix res1=solve(left,mid);Matrix res2=res1*quick_pow(Ma,mid+1);
		res=res1+res2;
		if ((right-left+1)%2==1) res=res+quick_pow(Ma,right);
		return res;
	}
	int count(vector<string> songs,vector<string> transitions,int minLength,int maxLength)
	{
		Clear();
		init_read(songs,transitions);
		init_matrix();
		sMa.Clear();sMa.construct_starter();
		sMa=sMa*quick_pow(Ma,minLength-1)*solve(0,maxLength-minLength);
		int i;LL ans=0;
		for (i=1;i<=gnum;i++)
			ans=(ans+sMa.b[1][Pair_to_Ind(i,1)])%MOD;
		return int(ans);
	}
};

/*---Debug Part---*/
/*int main ()
{
	ShuffledPlaylist A;
	vector<string> songs,transitions;int minLength,maxLength;string tmp;
	int songs_num,transitions_num;
	while (cin>>songs_num)
	{
		songs.clear();transitions.clear();
		getchar();
		while (songs_num--)
		{
			getline(cin,tmp);
			//cout<<tmp<<endl;
			songs.pb(tmp);
		}
		cin>>transitions_num;getchar();
		while (transitions_num--)
		{
			getline(cin,tmp);
			transitions.pb(tmp);
		}
		cin>>minLength>>maxLength;
		cout<<A.count(songs,transitions,minLength,maxLength)<<endl;
	}
	return 0;
}*/
/*
3
0 3,
1 2,
0 2
2
YY
YY
2 4
3
0 3,
1 2,
0 2
2
YN
NY
2 4
3
0 9,
1 8,
2 3,2 5
3
YYY
NYY
NNY
5 9
25
0 8,
5 6,2
 2,2 3,6 8,5 8,5 3,0 6,0 7,6 5,3 2
,0 9,2 3,3 4,5 4,3 3,3 3,2 8,2 9,5 7,2 8,0 1,5 9,1
 8,2 9,1 6,3 6,2 6,0 4,6 3,1 5,2 7,4 5,3 3,0
 5,6 1,5 6,4 8,5 9,1 4,2 9,5 6,5 6,0 8,3 5,4 6,0 3
,4 2,5 6,6 2,4 3,1 3,6 3,0 8,2 8,3 7,4 2,0 7,0 2,1
 3,4 7,6 3,6 4,3 9,0 2,0 7,0 8,6 4,1 3,2 5,0 6,5 4
,3 2,3 2,1 5,2 1,5 2,4 8,0 5,1
 
7,2 6,5 7
,
6 9,5 5,
4 2
,4
 9,0 5,4 8,6 5,5 9,5 8,3 
2
,5 
6,2 3,0 7,1 7,
2 1,0 4
,2 9
,
3
 
4
7
YYYYYYY
YYYYYYY
YYYYYYY
YYYYYYY
YYYYYYY
YYYYYYY
YYYYYYY
1 10000

Returns: 348387817
*/