from __future__ import annotations
from copy import deepcopy
from math import isclose

# Maybe broken

class vector2:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __str__(self):
        return f"( {self.x} | {self.y} )"
    def __add__(self, addend: vector2):
        return vector2(self.x + addend.x, self.y + addend.y)
    def __sub__(self, addend: vector2):
        return vector2(self.x - addend.x, self.y - addend.y)
    def __mul__(self, multiplier: int):
        return vector2(self.x * multiplier, self.y * multiplier)

class les:
    def __init__(self, vector2_line_1: vector2_line, vector2_line_2: vector2_line):
        self.v1 = deepcopy(vector2_line_1)
        self.v2 = deepcopy(vector2_line_2)
        self.r = ['r', False]
        self.s = ['s', False]
        self.r_val = None
        self.s_val = None
        self.originals = [vector2_line_1, vector2_line_2]
    def __str__(self):
        return f"""
            {self.v1.positional_vector.x} + {self.r[0]} * {self.v1.directional_vector.x} = {self.v2.positional_vector.x} + {self.s[0]} * {self.v2.directional_vector.x}
            {self.v1.positional_vector.y} + {self.r[0]} * {self.v1.directional_vector.y} = {self.v2.positional_vector.y} + {self.s[0]} * {self.v2.directional_vector.y}
            r = {self.r_val}
            s = {self.s_val}
        """
    def __solve_for_r(self):
        self.v2.positional_vector.x -= self.v1.positional_vector.x
        self.v1.positional_vector.x -= self.v1.positional_vector.x
        self.v2.directional_vector.x /= self.v1.directional_vector.x
        self.v1.directional_vector.x /= self.v1.directional_vector.x
    def __insert_r(self):
        pos = self.v2.positional_vector.x * self.v1.directional_vector.y
        dir = self.v2.directional_vector.x * self.v1.directional_vector.y
        self.v1.positional_vector.y += pos
        self.v1.directional_vector.y = dir
        # self.r = 's'
    def __solve_for_s(self):
        self.v2.directional_vector.y -= self.v1.directional_vector.y
        self.v1.directional_vector.y -= self.v1.directional_vector.y
        self.v1.positional_vector.y -= self.v2.positional_vector.y
        self.v2.positional_vector.y -= self.v2.positional_vector.y
        self.v1.positional_vector.y /= self.v2.directional_vector.y
        self.v2.directional_vector.y /= self.v2.directional_vector.y
        self.s_val = self.v1.positional_vector.y
    def __insert_s(self):
        self.v2.directional_vector.x *= self.s_val
        self.r_val = self.v2.positional_vector.x + self.v2.directional_vector.x
    def solve(self):
        self.__solve_for_r()
        self.__insert_r()
        self.__solve_for_s()
        self.__insert_s()
        return self.r_val, self.s_val

class vector2_line:
    def __init__(self, positional_vector, directional_vector):
        self.positional_vector = positional_vector
        self.directional_vector = directional_vector
    def __str__(self):
        return f"{self.positional_vector} + x*{self.directional_vector}"
    def get_point(self, factor):
        return self.positional_vector + (factor * self.directional_vector)
    def intersects(self, line: vector2_line):
        self.les = les(self, line)
        r, s = self.les.solve()
        p1 = self.positional_vector + (self.directional_vector * r)
        p2 = line.positional_vector + (line.directional_vector * s)
        if isclose(p1.x, p2.x) and isclose(p1.y, p2.y):
            return p1
        return False

if __name__ == "__main__":
    pos_vec_1 = vector2(0, -250)
    dir_vec_1 = vector2(424.26406871192853, 424.2640687119285)
    line_1 = vector2_line(pos_vec_1, dir_vec_1)

    pos_vec_2 = vector2(0, 250)
    dir_vec_2 = vector2(424.26406871192853, -424.2640687119285)
    line_2 = vector2_line(pos_vec_2, dir_vec_2)

    print(line_1.intersects(line_2))
