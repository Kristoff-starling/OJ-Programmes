class Solution:
    def maximumRequests(self, n: int, requests: List[List[int]]) -> int:
        ans, r = 0, len(requests)
        for Mask in range(2 ** r):
            cnt = defaultdict(int)
            num = 0
            for i in range(r):
                if Mask >> i & 1 == True:
                    cnt[requests[i][0]] -= 1
                    cnt[requests[i][1]] += 1
                    num += 1
            v = list(cnt.values())
            if v.count(0) == len(v):
                ans = max(ans, num)
        return ans