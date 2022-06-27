class Solution {
    int d[100048], n;
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        n= int(nums1.size());
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            d[i] = nums2[i] - nums1[i];
            sum1 += nums1[i];
            sum2 += nums2[i];
        }
        int maxn = 0, cur = 0;
        for (int i = 0; i < n; i++)
        {
            cur += d[i];
            maxn = max(maxn, cur);
            if (cur < 0) cur = 0;
        }
        int ans = sum1 + maxn;
        int minn = 0; cur = 0;
        for (int i = 0; i < n; i++)
        {
            cur += d[i];
            minn = min(minn, cur);
            if (cur > 0) cur = 0;
        }
        ans = max(ans, sum2 - minn);
        return ans;
    }
};