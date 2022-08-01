class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        int n = int(buses.size()), m = int(passengers.size());
        int ptr = 0, cur = 0, i;
        for (i = 0; i < m; i++)
            if (buses[ptr] >= passengers[i])
            {
                cur++;
                if (ptr == n-1 && cur == capacity) break;
                if (cur == capacity) ptr++, cur = 0;
            }
            else
            {
                while (ptr<=n-1 && buses[ptr] < passengers[i]) ptr++;
                if (ptr == n)
                {
                    int ans = buses[n-1], pp = m-1;
                    while (pp >= 0 && passengers[pp] > ans) pp--;
                    while (pp >= 0 && passengers[pp] == ans) ans--, pp--;
                    return ans;
                }
                cur = 1;
                if (ptr == n-1 && cur == capacity) break;
                if (cur == capacity) ptr++, cur = 0;
            }
        int pp;
        if (ptr == n-1 && cur == capacity)
        {
            int pp = i;
            while (pp > 0 && passengers[pp-1] + 1 == passengers[pp]) pp--;
            return passengers[pp] - 1;
        }
        else
        {
            int ans = buses[n-1], pp = m-1;
            while (pp >= 0 && passengers[pp] > ans) pp--;
            while (pp >= 0 && passengers[pp] == ans) ans--, pp--;
            return ans;
        }
    }
};