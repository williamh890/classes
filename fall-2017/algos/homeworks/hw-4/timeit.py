
import time
import os
import sys


def run_hsp():
    os.system("./counthsr.out")


if __name__ == "__main__":
    start = time.time()
    run_hsp()
    end = time.time()

    with open("times.txt", "a") as f:
        f.write("-> run  : {}\n".format(sys.argv[1]))
        f.write("   time : {}\n".format(end - start))
        f.write("\n")
