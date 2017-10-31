import numpy as np

def q3():
    print("P(X1 = X2) = {}".format(0.08 + .15 + .1 + .07))
    total = .22
    print("P(at least two more in one line) = {}".format(total))
    print(8 + 7 + 4)
    print(3 + 5 + 3 * 1.4 + 4 * 1.2)

pxy = np.array([[.02, .06, .02, .1 ],
                [.04, .15, .2 , .1 ],
                [.01, .15, .14, .01]])

def q22():
    total = sum([5 * (p1 + p2) * prob for (p2, row) in enumerate(pxy) for (p1, prob) in enumerate(row)])

    print(total)

    total = sum([5 * max(p1, p2) * prob for (p2, row) in enumerate(pxy) for (p1, prob) in enumerate(row)])

    print(total)

def q30():
    Px = [sum(row) for row in pxy]
    Py = [sum(col) for col in pxy.transpose()]

    Ex = sum([5 * p * row for p, row in enumerate(Px)])
    Ey = sum([5 * p * col for p, col in enumerate(Py)])
    exy = [5*x*y*p for x, row in enumerate(pxy) for y, p in enumerate(row)]
    print(exy)
    Exy = sum(exy)

    print(Ex)
    print(Ey)
    print(Exy)



if __name__ == "__main__":
    q30()
