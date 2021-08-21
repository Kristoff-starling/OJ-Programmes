#include <bits/stdc++.h>
using namespace std;

int n=300;

int R() {return rand()%1000+1;}

int main ()
{
    freopen ("a.in","w",stdout);
    cout<<n<<endl;
    for (int i=1;i<=n;i++) cout<<R()<<' '<<R()<<' '<<R()<<' '<<R()<<endl;
    return 0;
}