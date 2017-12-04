import csv
import sys
import json


def print_cols(cols):
    print("COLUMNS:")
    for col in cols:
        print(f"\t-> {col}")


def load_col(file_path, col_name="Size (MB)"):

    cols_to_delete = set(
        [
            'Beam Mode Description', 'Granule Name',
            'URL', 'Stack ID', 'Acquisition Date',
            'Processing Date', 'Start Time', 'End Time',
            'Stack Size', 'Baseline Perp.', 'Doppler',
            'Absolute Orbit', 'Relative Orbit', 'Path Number'
        ]
    )

    original_data = []
    with open(file_path, "r") as f:
        reader = csv.reader(f)

        pos_clean_row = set()
        row_index = -1
        elements = []
        delete_indexs = set()
        for index, row in enumerate(reader):
            if index == 0:
                for to_del in (c for c in row if c in cols_to_delete):
                    del_index = row.index(to_del)
                    delete_indexs.add(del_index)

                row_index = row.index(col_name)

            cleaned_row = []
            for i in sorted(list(set(range(len(row))) - delete_indexs)):
                cleaned_row.append(row[i])

            original_data.append(cleaned_row)
            pos_clean_row.add(tuple(cleaned_row[-3:]))

            if index != 0:
                elements.append(row[row_index])

    return elements, original_data


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


def print_platform_stats(cells):
    a, b = [], []
    for cell in cells:
        if '1A' in cell:
            a.append(cell)
        elif '1B' in cell:
            b.append(cell)

    print(f'Total: {len(cells)} instances')
    print(f'Sentinal 1A: count {len(a)}, percentage {len(a) / (len(a) + len(b)):4.2f} %')
    print(f'Sentinal 1B: count {len(b)}, percentage {len(b) / (len(a) + len(b)):4.2f} %')

    return cells


def write_back(original, path, elements, col_name):
    with open(path, "w") as f:
        writer = csv.writer(f, delimiter=',')

        row_index = -1
        for index, row in enumerate(original):
            if index == 0:
                row_index = row.index(col_name)
            else:
                row[row_index] = str(elements[index - 1])

            writer.writerow(row)


def get_params():
    try:
        file_path = sys.argv[1]
    except:
        print("csv file not specified.")

    try:
        output = sys.argv[2]
    except:
        output = ''

    return file_path, output


def run(col_name, convert_func):
    file_path, output = get_params()
    sizes, original = load_col(file_path, col_name=col_name)
    converted = convert_func(sizes)

    print("\nEXAMPLE INSTANCE:")
    print("-" * 30)
    print(json.dumps(original[0]))
    print("")
    print(json.dumps(original[1]))
    print("")

    if output == '' or output is None:
        return

    write_back(original, output, converted, col_name=col_name)


def clean_run():
    run('Size (MB)', unit_converter)


def overview_run():
    run('Platform', print_platform_stats)


if __name__ == "__main__":
    overview_run()
