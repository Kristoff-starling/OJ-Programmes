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
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
  
const int MOD=1e9+9;
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
  
inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
int n,m;
 
namespace SegmentTree
{
    int lazy[20000048],lson[20000048],rson[20000048];LL sum[20000048];int tot;
    inline void buildx(int cur,int left,int right)
    {
        lson[cur]=rson[cur]=lazy[cur]=sum[cur]=0;tot=max(tot,cur);
        if (left!=right)
        {
            int mid=(left+right)>>1;
            buildx(cur<<1,left,mid);
            buildx(cur<<1|1,mid+1,right);
        }
    }
    inline void updatey(int &cur,int left,int right,int l,int r)
    {
        if (!cur) cur=++tot;
        if (left<=l && r<=right) {lazy[cur]++;sum[cur]+=(r-l+1);return;}
        int mid=(l+r)>>1;
        if (left<=mid) updatey(lson[cur],left,right,l,mid);
        if (mid+1<=right) updatey(rson[cur],left,right,mid+1,r);
        sum[cur]+=min(r,right)-max(l,left)+1;
    }
    inline void updatex(int cur,int pos,int left,int right,int l,int r)
    {
        int mid;
        while (l<=r)
        {
            updatey(cur,left,right,1,n);
            if (l==r) break;
            mid=(l+r)>>1;
            if (pos<=mid) cur<<=1,r=mid; else cur=(cur<<1|1),l=mid+1;
        }
    }
    inline LL queryy(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return sum[cur];
        int mid=(l+r)>>1;LL res=0;
        if (left<=mid && lson[cur]) res+=queryy(lson[cur],left,right,l,mid);
        if (mid+1<=right && rson[cur]) res+=queryy(rson[cur],left,right,mid+1,r);
        res+=(long long)lazy[cur]*(min(r,right)-max(l,left)+1);
        return res;
    }
    inline int queryx(int cur,int left,int right,int k,int l,int r)
    {
        int mid;LL res;
        while (l!=r)
        {
            mid=(l+r)>>1;res=queryy(cur<<1|1,left,right,1,n);
            if (k>res) k-=res,r=mid,cur<<=1; else l=mid+1,cur=(cur<<1|1);
        }
        return l;
    }
}
 
int main ()
{
    int i,type,A,B,C;n=getint();m=getint();
    SegmentTree::buildx(1,1,100048);
    while (m--)
    {
        type=getint();A=getint();B=getint();C=getLL();
        if (type==1) C+=50001;
        if (type==1) SegmentTree::updatex(1,C,A,B,1,100048); else printf("%d\n",SegmentTree::queryx(1,A,B,C,1,100048)-50001);
    }
    return 0;
}
