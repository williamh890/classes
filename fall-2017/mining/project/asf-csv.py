import csv
import sys


def load_size_col(file_path):
    original_data = []
    with open(file_path, "r") as f:
        reader = csv.reader(f)

        size_row_index = -1
        sizes = []
        for index, row in enumerate(reader):
            original_data.append(row)
            if index == 0:
                size_row_index = row.index("Size (MB)")
                continue

            sizes.append(row[size_row_index])

    return sizes, original_data


def unit_converter(sizes):
    sizes_mb = []
    for size in sizes:
        amount, unit = size.split()

        try:
            amount = float(amount)
        except:
            continue

        if unit == "GB":
            amount *= 1000.

        sizes_mb.append(amount)

    return sizes_mb


def write_back(original, path, sizes):
    with open(path, "w") as f:
        writer = csv.writer(f, delimiter=',')

        size_row_index = -1
        for index, row in enumerate(original):
            if index == 0:
                size_row_index = row.index("Size (MB)")
            else:
                row[size_row_index] = str(sizes[index - 1])
            writer.writerow(row)


def run():
    try:
        file_path = sys.argv[1]
        output = sys.argv[2]
    except:
        print("file parameter or output not passed")
        return

    sizes, original = load_size_col(file_path)

    sizes_mb = unit_converter(sizes)

    write_back(original, output, sizes_mb)


if __name__ == "__main__":
    run()
