class Solution:
    def arrayNesting(self, nums: List[int]) -> int:
        n = len(nums)
        visited, ans = [False] * n, 0
        for i in range(n):
            cnt, cur = 0, i
            while visited[cur] is False:
                visited[cur] = True
                cnt, cur = cnt + 1, nums[cur]
            ans = max(ans, cnt)
        return ans