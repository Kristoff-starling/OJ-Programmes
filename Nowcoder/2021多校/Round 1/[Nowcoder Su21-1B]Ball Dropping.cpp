#include <bits/stdc++.h>
using namespace std;

int main ()
{
    long double r,a,b,h;
    cin>>r>>a>>b>>h;
    if (2*r<=b) {puts("Drop");return 0;}
    long double len=sqrt((a-b)*(a-b)/4+h*h);
    long double sa=h/len,ca=-(a-b)/2/len;
    puts("Stuck");
    printf("%.6Lf\n",(b*sa-2*r)/2/ca);
    return 0;
}