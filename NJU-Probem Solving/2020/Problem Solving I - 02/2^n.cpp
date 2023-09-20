#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

template<typename T> inline void Print(T x)
{
    int a[48],len=0;
    while (x) a[++len]=x%10,x/=10;
    REP(i,len,1) printf("%d",a[i]);puts("");
}

int main ()
{
    int n;scanf("%d",&n);
    __int128 res=1;
    while (n--) res*=2;
    Print(res);return 0;
}