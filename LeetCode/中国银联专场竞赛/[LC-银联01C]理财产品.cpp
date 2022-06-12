const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) >> 1;
class Solution {
    int a[100048], n;
public:
    int maxInvestment(vector<int>& product, int limit) {
        for (auto item : product) a[++n] = item;
        sort(a + 1, a + n + 1, [&](int &x, int &y){return x > y;}); a[n + 1] = 0;
        int range = 1, ans = 0;
        while (limit > 0 && range <= n)
        {
            while (range <= n && a[range] == a[range + 1]) range++;
            if (range == n + 1) break;
            int delta = a[range] - a[range + 1];
            if (1ll * range * delta <= 1ll * limit)
            {
                limit -= 1ll * range * delta;
                ans = (ans + 1ll * range * ((a[range] + a[range + 1] + 1) % MOD) % MOD * delta % MOD * inv2 % MOD) % MOD;
                
            }
            else
            {
                int base = limit / range;
                limit -= 1ll * range * base;
                ans = (ans + 1ll * range * ((a[range] + a[range] - base + 1) % MOD) % MOD * base % MOD * inv2 % MOD) % MOD;
                int val = a[range] - base;
                ans = (ans + 1ll * val * limit % MOD) % MOD;
                limit = 0;
            }
            range++;
        }
        return ans;
    }
};