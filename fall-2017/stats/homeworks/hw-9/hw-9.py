import matplotlib.pyplot as plt


def q33():
    data = [418, 421, 421, 422, 425, 427, 431, 434, 437, 439, 446, 447, 448, 453, 454, 463, 465]
    plt.figure()
    plt.boxplot(data,  0, 'rs', 0)
    plt.savefig('question33a.png')


if __name__ == "__main__":
    q33()
