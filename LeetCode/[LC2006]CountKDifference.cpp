class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int myabs(int x) {return (x>=0)?x:-x;};
public:
    int countKDifference(vector<int>& nums, int k) {
        int n=int(nums.size());int ans=0;
        rep(i,0,n-1) rep(j,i+1,n-1)
            if (myabs(nums[i]-nums[j])==k) ans++;
        return ans;
    }
};