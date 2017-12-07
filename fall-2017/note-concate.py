from os import listdir as ls
from os.path import join

import sys


def concat(path, outfile):
    data = []
    for f_name in ls(path):
        with open(join(path, f_name), 'r') as f:
            f_data = f.read()
            file_name = str(f_name)
            try:
                note = float(file_name.split('.')[0][4:])
            except:
                continue
            data.append((note, f_data))
    data = sorted(data, key=lambda k: k[0])

    concated_file = ''
    for d in data:
        print(f"adding day {d[0]} notes.")
        concated_file += d[1].strip()
        concated_file += '\n\n'

    with open(outfile, 'w') as f:
        f.write(concated_file)


if __name__ == "__main__":
    concat(sys.argv[1], sys.argv[2])
