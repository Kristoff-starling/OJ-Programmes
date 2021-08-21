#include <bits/stdc++.h>
using namespace std;

int n=500000,q=10000000,seed=1;

int main ()
{
    freopen ("a.in","w",stdout);
    cout<<n<<' '<<q<<' '<<seed<<endl;
    for (int i=1;i<=n;i++) printf("%d\n",rand()*100);
    for (int i=2;i<=n;i++) printf("%d\n",rand()%(i-1)+1);
    return 0;
}