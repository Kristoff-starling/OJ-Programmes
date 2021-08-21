#include <bits/stdc++.h>
#define LL long long
using namespace std;

int main ()
{
    LL a,b,c;
    cin>>a>>b>>c;
    if (b*2>a+c) printf("%lld\n",b*2-a-c);
    else
    {
        if ((a+c)&1) printf("%lld\n",(a+c+1)/2-b+1);
        else printf("%lld\n",(a+c)/2-b);
    }
    return 0;
}