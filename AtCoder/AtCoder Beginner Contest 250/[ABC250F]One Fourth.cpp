#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;

template<typename T> T myabs(T x) {return x>0?x:-x;}

int n;
struct Vector
{
    LL x,y;
    Vector operator - (Vector other) {return Vector{.x=x-other.x,.y=y-other.y};}
}a[MAXN+48];

LL det(Vector a,Vector b) {return myabs(a.x*b.y-a.y*b.x);}

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y),a[i+n]=a[i];
    LL S=0;rep(i,2,n-1) S+=det(a[i]-a[1],a[i+1]-a[1]);
    LL ans=S,curS=0;int ptr=1;
    rep(i,1,n)
    {
        if (ptr>i) curS-=det(a[ptr]-a[i-1],a[i]-a[i-1])*4;
        if (ptr==i) ptr=i+1;
        while (curS+det(a[ptr+1]-a[i],a[ptr]-a[i])*4<=S) curS+=det(a[ptr+1]-a[i],a[ptr]-a[i])*4,ptr++;
        ans=min(ans,S-curS);ans=min(ans,curS+det(a[ptr+1]-a[i],a[ptr]-a[i])*4-S);
    }
    printf("%lld\n",ans);
}