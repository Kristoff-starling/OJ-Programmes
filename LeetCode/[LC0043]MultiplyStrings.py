class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        A = 0 
        for digit in num1: A = A * 10 + int(digit)
        B = 0
        for digit in num2: B = B * 10 + int(digit)
        return str(A * B)