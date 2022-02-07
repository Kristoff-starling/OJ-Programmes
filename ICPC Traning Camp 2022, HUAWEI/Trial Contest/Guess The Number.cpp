#include <bits/stdc++.h>
using namespace std;

int n;

int main ()
{
	scanf("%d",&n);
	int l = 1, r = n, mid; char res[10];
	while (l < r)
    {
    	mid = (l + r + 1) >> 1;
    	printf("? %d\n", mid);
    	fflush(stdout);
    	scanf("%s", res);
    	if (res[0] == '<') r = mid - 1; else l = mid;
    }
	printf("! %d\n", l);
	fflush(stdout);
	return 0;
}