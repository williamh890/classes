# hw-1.py
# William Horn
# Homework 1

import numpy as np
import matplotlib.pyplot as plt
import math


def question12():
    partical_freqs = [5, 15, 27, 34, 22, 14, 7, 2, 4, 1]

    partical_samples = []

    for num, freq in zip(np.arange(3.25, 8.0, 0.5), partical_freqs):
        print("{}: {}".format(num, freq))
        partical_samples += [num for _ in range(freq)]

    print(partical_samples)

    plt.hist(partical_samples, histtype="bar")

    plt.xlabel("ceo2 partical size (nm)")
    plt.ylabel("freqency")
    plt.title("partical size histogram")
    plt.savefig('question12c.png')


def group_stems(_list):
    stems = set(s for s, l in _list)
    stems_leafs = {s: [] for s in stems}

    for s, l in _list:
        stems_leafs[s].append(l)

    sorted_leafs = sorted(stems_leafs.items(), key=lambda x: x[0])
    return sorted_leafs


def steam_leaf(_list):
    _list.sort()
    _list = [(t / 10, t % 10) for t in _list]

    return group_stems(_list)


def print_stem_and_leaf(sal_plot, label=""):
    print(label)
    for stem, leafs in sal_plot:
        row = "{:<3} |  ".format(stem)

        for leaf in leafs:
            row += "{} ".format(leaf)
        print(row)
    print("")


def question15():
    american_runtimes = [94, 90, 95, 93, 128, 95, 125, 91, 104, 116, 162,
                         102, 90, 110, 92, 113, 116, 90, 97, 103, 95, 120, 109, 91, 138]
    french_runtimes = [123, 116, 90, 158, 122, 119, 125, 90, 96, 94, 137,
                       102, 105, 106, 95, 125, 122, 103, 96, 111, 81, 113, 128, 93, 92]

    french, american = steam_leaf(
        french_runtimes), steam_leaf(american_runtimes)

    print_stem_and_leaf(american, "America Runtimes")
    print_stem_and_leaf(french, "French Runtimes")


def mean(numbers):
    return sum(numbers) / float(len(numbers))


def median(numbers):
    numbers = sorted(numbers[:])

    length = len(numbers)

    if len(numbers) % 2 == 1:
        return numbers[(length) / 2]
    else:
        n1 = numbers[(length / 2) - 1]
        n2 = numbers[-(length / 2)]
        return mean([n1, n2])


def question33():
    house_prices = [590, 815, 575, 608, 350, 1285, 408, 540, 555, 679]
    prices_mean = mean(house_prices)
    prices_median = median(house_prices)

    print("mean: {}".format(prices_mean))
    print("median: {}".format(prices_median))

    house_prices = [590, 815, 575, 608, 350, 985, 408, 540, 555, 679]
    avg = mean(house_prices)
    middle = median(house_prices)
    print("mean: {}".format(avg))
    print("median: {}".format(middle))


def question34():
    urban_dust = [6.0, 5.0, 11.0, 33.0, 4.0, 5.0, 80.0, 18.0, 35.0, 17.0, 23.0]
    farm_dust = [4.0, 14.0, 11.0, 9.0, 9.0, 8.0, 4.0,
                 20.0, 5.0, 8.9, 21.0, 9.2, 3.0, 2.0, 0.3]
    print("Finding median from urban data {}".format(sorted(urban_dust)))
    print("Finding median from farm data {}".format(sorted(farm_dust)))
    f_mean = mean(farm_dust)
    u_mean = mean(urban_dust)

    print("Farm mean = {}".format(f_mean))
    print("Urban mean = {}".format(u_mean))

    f_median = median(farm_dust)
    u_median = median(urban_dust)

    print("Farm median = {}".format(f_median))
    print("Urban median = {}".format(u_median))


def standard_dev(nums):
    n = float(len(nums))
    sxx = sum([num**2 for num in nums]) - (1 / n) * (sum(nums))**2
    return math.sqrt((1 / (n - 1)) * sxx)


def question46():
    cooler = [1.59, 1.43, 1.88, 1.26, 1.91, 1.86, 1.90,
              1.57, 1.79, 1.72, 2.41, 2.34, 0.83, 1.34, 1.76]
    control = [1.92, 2.00, 2.19, 1.12, 1.78,
               1.84, 2.45, 2.03, 1.52, 0.53, 1.90]
    warmer = [2.57, 2.60, 1.93, 1.58, 2.30, 0.84,
              2.65, 0.12, 2.74, 2.53, 2.13, 2.86, 2.31, 1.91]
    labels = ["cooler", "control", "warmer"]
    for label in labels:
        data = eval(label)
        print("{} : {}".format(label, data))
        avg, med = mean(data), median(data)
        print("mean: {}, median: {}".format(avg, med))
        print("standard dev: {}".format(standard_dev(data)))
    # fake up some more data
    data = [cooler, control, warmer]
    plt.figure()
    plt.boxplot(data)
    plt.savefig('question46d.png')


if __name__ == "__main__":
    question12()
    question15()
    question33()
    question34()
    question46()
