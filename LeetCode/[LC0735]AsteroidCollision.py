class Solution:
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        q, ans = [], []
        for item in asteroids:
            if item > 0: q.append(item)
            else:
                flag = True
                while q:
                    if q[-1] > abs(item):
                        flag = False
                        break
                    elif q[-1] == abs(item):
                        q = q[:-1]
                        flag = False
                        break
                    else:
                        q = q[:-1]
                if flag is True: ans.append(item)
        for item in q: ans.append(item)
        return ans