class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        l, r, ans = 1, max(piles), 0
        while l <= r:
            mid, cnt = (l + r) // 2, 0
            for pile in piles:
                cnt += (pile + mid - 1) // mid
            if cnt <= h: ans, r = mid, mid - 1
            else: l = mid + 1
        return ans