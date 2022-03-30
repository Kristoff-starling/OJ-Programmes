class Solution:
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:
        def check(num: int) -> bool:
            tmp = num
            while tmp != 0:
                if tmp % 10 == 0: return False
                if num % (tmp % 10) != 0: return False
                tmp //= 10
            return True
        return [i for i in range(left, right + 1) if check(i)]