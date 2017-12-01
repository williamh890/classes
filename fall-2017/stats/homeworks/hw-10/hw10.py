import numpy as np


def q34a():
    vals = np.array([32.1, 30.6, 31.4, 30.4, 31.9])

    mean = sum(vals) / len(vals)
    stdev = np.std(vals)

    print(f"n: {len(vals)}")
    print(f"stdev: {stdev}")
    print(f"mean: {mean}")


if __name__ == "__main__":
    q34a()
