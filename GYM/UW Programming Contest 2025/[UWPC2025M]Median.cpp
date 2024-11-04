#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1e6 + 10;

int n, a[MAXN];
priority_queue<int> q1, q2;

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        if (n == 1)
        {
            printf("%d\n", a[1] / 2);
            continue;
        }
        else if (n == 2)
        {
            printf("%d %d\n", a[1] / 2, a[2] - a[1] / 2);
            continue;
        }
        else
        {
            while (!q1.empty()) q1.pop();
            while (!q2.empty()) q2.pop();
            printf("%d %d ", a[1] / 2, a[2] - a[1] / 2);
            int max_count = 2e9, min_count = -2e9;
            int x = a[1] / 2, y = a[2] - a[1] / 2;
            if (x > y) swap(x, y);
            q1.push(x); q2.push(-y);
            for (int i = 2; i <= n - 1; i++)
            {
                if (!(i & 1))
                {
                    int target = a[i + 1] / 2;
                    if (target == q1.top())
                    {
                        q1.push(min_count);
                        printf("%d ", min_count);
                        min_count++;
                    }
                    else if (target == -q2.top())
                    {
                        q2.push(-max_count);
                        printf("%d ", max_count);
                        q1.push(-q2.top());
                        q2.pop();
                        max_count--;
                    }
                    else
                    {
                        q1.push(target);
                        printf("%d ", target);
                    }
                }
                else
                {
                    int target = a[i + 1];
                    if (q1.top() - q2.top() == target)
                    {
                        q2.push(-max_count);
                        printf("%d ", max_count);
                        max_count--;
                    }
                    else
                    {
                        int x = q1.top(); q1.pop(); int y = q1.top(); q1.push(x);
                        if (x + y == target)
                        {
                            q1.push(min_count);
                            printf("%d ", min_count);
                            q2.push(-q1.top());
                            q1.pop();
                            min_count++;
                        }
                        else
                        {
                                int xx = target - q1.top();
                                if (xx > q1.top())
                                    q2.push(-xx);
                                else
                                {
                                    q2.push(-q1.top());
                                    q1.pop();
                                    q1.push(xx);
                                }
                                printf("%d ", xx);
                        }
                    }
                }
            }
        }
        puts("");
    }
    return 0;
}