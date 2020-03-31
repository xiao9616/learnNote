class GameMap(object):

    CELL_DEAD = 0
    CELL_ALIVE = 1

    @staticmethod
    def check_integer(n, min=None, max=None):
        if not isinstance(n, int) or \
                min and not isinstance(min, int) or \
                max and not isinstance(max, int):
            raise TypeError("Type error:int")
        if min and n < min:
            raise OverflowError("Range error:min")
        if max and n > max:
            raise OverflowError("Range error:min")

    def __init__(self, rows, cols) -> None:
        GameMap.check_integer(rows, 1)
        GameMap.check_integer(cols, 1)
        self.size = (rows, cols,)
        self.map = [[GameMap.CELL_DEAD for _ in range(cols)] for _ in range(rows)]

    @property
    def rows(self):
        return self.size[0]

    @property
    def cols(self):
        return self.size[1]

    def reset(self, possibility=0.5):
        self.map = [[GameMap.CELL_DEAD for _ in range(cols)] for _ in range(rows)]

    def get(self, row, col):
        GameMap.check_integer(row, 0, self.size[0] - 1)
        GameMap.check_integer(col, 0, self.size[1] - 1)
        return self.map[row][col]

    def set(self, row, col, val):
        GameMap.check_integer(row, 0, self.size[0] - 1)
        GameMap.check_integer(col, 0, self.size[1] - 1)
        GameMap.check_integer(val, 0, 1)
        self.map[row][col] = val

    def get_neighbor_count(self,row,col):
        GameMap.check_integer(row, 0, self.size[0] - 1)
        GameMap.check_integer(col, 0, self.size[1] - 1)
        DIRECTION={
            "up":(-1,0),
            "down":(1,0),
            "left":(0,-1),
            "right":(0,1),
            "up_left":(-1,-1),
            "up_right":(-1,1),
            "down_left":(1,-1),
            "down_right":(1,1)
        }
        count=0
        for dir in DIRECTION:
            trow=(row+DIRECTION[dir][0])%self.rows
            tcol=(col+DIRECTION[dir][0])%self.cols
            if self.map[trow][tcol]==GameMap.CELL_ALIVE:
               count+=1
        return count

    def get_neighbor_count_map(self):
        res=[]
        for row in range(self.rows):
            tres=[]
            for col in range(self.cols):
                tres.append(self.get_neighbor_count(row,col))
            res.append(tres)
        return res

    def set_map(self):
        self.map=self.get_neighbor_count_map()

    def print_map(self, cell_maps=['0', '1'], sep=' '):
        if not isinstance(cell_maps, list) or len(cell_maps) != 2:
            raise TypeError("Type error:cell_maps")
        if not isinstance(sep, str):
            raise TypeError("Type error:sep")
        for row in range(self.rows):
            print(sep.join(map(lambda x: cell_maps[x], self.map[row])))


if __name__ == '__main__':
    gamemap = GameMap(5, 5)
    gamemap.print_map()

