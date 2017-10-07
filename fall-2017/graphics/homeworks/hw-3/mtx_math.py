# mtx_math.py
# William Horn
# Oct 2, 2017

import numpy as np
import math


def q1():
    _sum = np.array([1, 3]) + np.array([2, 1])

    return "[1,3] + [2,1] = {}".format(_sum)


def q2():
    _mult = -2 * np.array([0, 1, 3])
    return "-2 * [0,1,3] = {}".format(_mult)


def q3():
    global dist
    dist = math.sqrt(3**2 + 4**2)
    return "dist([3, 4]) = {}".format(dist)


def q4():
    return "uv([3,4]) = {}".format(dist * np.array([3, 4]))


def q5():
    global dot_prod
    dot_prod = np.dot(np.array([2, 1]), np.array([3, -1]))
    return "[2, 1] dot [3,-1] = {}".format(dot_prod)


def q6():
    return "yes" if dot_prod == 0 else "no"


def q7():
    a = np.array([1, 0, 1])
    b = np.array([0, 1, 0])

    return "{} X {} = {}".format(a, b, np.cross(a, b))


def q8():
    return "I_2 =\n {}".format(np.array([[1, 0], [0, 1]]))


def q9():
    trans = np.transpose([[1, 2], [3, 4]])
    return "transpose = \n{}".format(trans)


def q10():
    ma = np.array([[1, 2], [3, 4]])
    va = np.array([[1], [1]])

    return "\n{} *\n {} = \n{}".format(ma, va, ma.dot(va))


def q11():
    a = np.array([[1, 2], [3, 4]])
    b = np.array([[1, 0], [1, 1]])

    return "\n{} \n* {} \n= {}".format(a, b, a.dot(b))


def q12():
    return "inverse"


if __name__ == "__main__":
    for i in range(12):
        index=i + 1
        answer=eval("q{index}".format(index=index))()
        print("{}.) {}".format(index, answer))
