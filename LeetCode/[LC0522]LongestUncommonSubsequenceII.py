class Solution:
    def findLUSlength(self, strs: List[str]) -> int:
        
        def check(s1: str, s2: str) -> bool:
            if len(s1) > len(s2): return False
            ptr = 0
            for ch in s1:
                while ptr <= len(s2) - 1 and s2[ptr] != ch: ptr += 1
                if ptr >= len(s2): return False
                ptr += 1
            return True

        ans, n = -1, len(strs)
        for i in range(n):
            flag = True
            for j in range(n):
                if i != j and check(strs[i], strs[j]): flag = False
            if flag == True: ans = max(ans, len(strs[i]))
        return ans