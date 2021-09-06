#include <bits/stdc++.h>
using namespace std;

long long a,b,m;

int quick_pow(int x,long long y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%m;
        x=1ll*x*x%m;y>>=1;
    }
    return res;
}

int main ()
{
    cin>>a>>b>>m;a%=m;
    cout<<quick_pow(a,b)<<endl;
    return 0;
}