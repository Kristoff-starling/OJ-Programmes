class Solution:
    def validUtf8(self, data: List[int]) -> bool:
        def count(num: int) -> int:
            res, s = 0, bin(num)[2:]
            if len(s) < 8: return 0
            while s != '' and s[0] == '1':
                res += 1
                s = s[1:]
            return res
        def valid(num : int) -> bool:
            s = bin(num)[2:]
            if len(s) < 8: return False
            return (True if s[:2] == '10' else False)
        
        n, pt = len(data), 0
        while pt < n:
            num = count(data[pt])
            print(pt, num)
            if not (0 <= num <= 4 and num != 1): return False
            if n - pt < num: return False
            for _ in range(num - 1):
                pt += 1
                if not valid(data[pt]): return False
            pt += 1
        
        return True