class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    #define REP(i,a,b) for (int i=(a);i>=(b);i--)
    int n,lmax[100048],rmax[100048],h[100048];
public:
    int trap(vector<int>& height) {
        n=int(height.size());
        rep(i,1,n) h[i]=height[i-1];
        lmax[0]=0;rep(i,1,n) lmax[i]=max(lmax[i-1],h[i]);
        rmax[n+1]=0;REP(i,n,1) rmax[i]=max(rmax[i+1],h[i]);
        int ans=0;
        rep(i,1,n)
        {
            int lim=min(lmax[i-1],rmax[i+1]);
            ans+=max(lim-h[i],0);
        }
        return ans;
    }
};