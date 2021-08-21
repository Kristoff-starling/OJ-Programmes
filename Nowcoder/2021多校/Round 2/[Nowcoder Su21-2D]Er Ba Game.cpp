#include <bits/stdc++.h>
#define F {puts("first");continue;}
#define S {puts("second");continue;}
using namespace std;

int main ()
{
    int ca,a1,b1,a2,b2;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
        if (a1>b1) swap(a1,b1); if (a2>b2) swap(a2,b2);
        if (a1==a2 && b1==b2) {puts("tie");continue;}
        if (a1==2 && b1==8) F
        if (a2==2 && b2==8) S
        if (a1==b1 && a2!=b2) F
        if (a1!=b1 && a2==b2) S
        if (a1==b1 && a2==b2) {if (a1>a2) F else S}
        int res1=(a1+b1)%10,res2=(a2+b2)%10;
        if (res1>res2) F
        if (res1<res2) S
        if (b1>b2) F else S
    }
    return 0;
}