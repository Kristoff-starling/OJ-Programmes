class Solution:
    def canMouseWin(self, grid: List[str], catJump: int, mouseJump: int) -> bool:
        dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        r, c = len(grid), len(grid[0])
        walls, food, cat, mouse = [], (0, 0), (0, 0), (0, 0)
        status = {}
        for i in range(r):
            for j in range(c):
                if grid[i][j] == '#': walls.append((i, j))
                elif grid[i][j] == 'C': cat = (i, j)
                elif grid[i][j] == 'M': mouse = (i, j)
                elif grid[i][j] == 'F': food = (i, j)

        @lru_cache(None)
        def solve(cat, mouse, turn) -> bool:
            if turn > r * c * 2: return False
            if cat == food or cat == mouse: return False
            if mouse == food: return True
            if (cat, mouse, turn) in status: return status[(cat, mouse, turn)]

            Jump = (mouseJump if turn % 2 == 0 else catJump)
            if turn % 2 == 0:
                for d in dirs:
                    for step in range(0, Jump+1):
                        ncat, nmouse = cat, (mouse[0] + d[0] * step, mouse[1] + d[1] * step)
                        if 0 <= nmouse[0] < r and 0 <= nmouse[1] < c and nmouse not in walls:
                            res = solve(ncat, nmouse, turn + 1)
                            if res == True:
                                status[(cat, mouse, turn)] = True
                                return True
                        else: break
                status[(cat, mouse, turn)] = False
                return False
            else:
                for d in dirs:
                    for step in range(0, Jump+1):
                        ncat, nmouse = (cat[0] + d[0] * step, cat[1] + d[1] * step), mouse
                        if 0 <= ncat[0] < r and 0 <= ncat[1] < c and ncat not in walls:
                            res = solve(ncat, nmouse, turn + 1)
                            if res == False:
                                status[(cat, mouse, turn)] = False
                                return False
                        else: break
                status[(cat, mouse, turn)] = True
                return True
            
        return solve(cat, mouse, 0)