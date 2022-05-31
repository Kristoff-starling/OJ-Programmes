class Solution:
    def makesquare(self, matchsticks: List[int]) -> bool:
        length, n = sum(matchsticks), len(matchsticks)
        if length % 4 != 0: return False
        length //= 4

        dic = {}
        def dfs(step, l1, l2, l3, l4) -> bool:
            if l1 > length or l2 > length or l3 > length or l4 > length: return False
            if step == n: return True
            l1, l2, l3, l4 = sorted([l1, l2, l3, l4])
            if (l1, l2, l3, l4) in dic: return False
            if dfs(step+1, l1+matchsticks[step], l2, l3, l4): return True
            if dfs(step+1, l1, l2+matchsticks[step], l3, l4): return True
            if dfs(step+1, l1, l2, l3+matchsticks[step], l4): return True
            if dfs(step+1, l1, l2, l3, l4+matchsticks[step]): return True
            dic[(l1, l2, l3, l4)] = False
            return False

        return dfs(0, 0, 0, 0, 0)