import multiprocessing as mp
from PIL import Image
import numpy as np
import time
import os
import sys
from contextlib import contextmanager


@contextmanager
def timing(output_msg):
    start = time.time()
    yield
    end = time.time()
    print(output_msg.format(end - start))


@contextmanager
def pushd(directory):
    save_dir = os.getcwd()
    os.chdir(directory)
    yield os.getcwd()

    os.chdir(save_dir)


def save_image(arr, path):
    result = Image.fromarray(arr.astype(np.uint8))
    result.save(path)


def open_image(image_path):
    jpgfile = Image.open(image_path)
    pic_colors = np.array(jpgfile)

    return pic_colors


'''
pool = mp.Pool(processes=4)
results = [pool.apply(cube, args=(x,)) for x in range(1,7)]
print(results)
'''


def store_row(result):
    x, row = result
    results[x] = row


def process_img_async(colors, width, height):
    global results
    results = np.empty([width, height, 3])

    pool = mp.Pool()
    for x in range(width):
        pool.apply_async(
            process_row,
            args=(colors[x], x, width, height,),
            callback=store_row
        )

    pool.close()
    pool.join()

    return results


def process_img(colors, width, height):
    for x in range(width):
        process_row_colors(colors, x, width, height)


def clamp(x):
    return max(0, min(x, 255))


def mutate(channel, height, max_height, diff):
    return int(clamp(channel + diff * (height / max_height)))


def process_row_colors(colors, x, width, height):
    for y in range(height):
        colors[x][y][0] = max(0, min(colors[x][y][2] + 100 * (x / width), 255))
        colors[x][y][1] = max(0, min(colors[x][y][1] + 50 * (x / width), 255))
        colors[x][y][2] = max(0, min(colors[x][y][0] - 50 * (x / width), 255))


def process_row(row, x, width, height):
    for y in range(height):
        row[y][0] = max(0, min(row[y][2] + 100 * (x / width), 255))
        row[y][1] = max(0, min(row[y][1] + 50 * (x / width), 255))
        row[y][2] = max(0, min(row[y][0] - 50 * (x / width), 255))

    return (x, row)


def process_img_python(input_img, output_img):
    print ("Processing image python")
    colors = open_image(input_img)

    shape = colors.shape
    width, height, num_channel = shape
    print(shape, colors.dtype)

    with timing('Processing time: {} sec'):
        result = process_img_async(colors, width, height)

    save_image(result, output_img)


def process_img_cpp(input_bin, output_bin):
    print("Processing image c++")
    cpp_exe = 'processor-cpp/img-processor.out'
    if not os.path.exists(cpp_exe):
        print('img-processor executable not found')

        with pushd('processor-cpp'):
            os.system('make')

    with timing('processing time: {} sec'):
        os.system(f'./{cpp_exe} {input_bin} {output_bin}')


def main():
    processor = sys.argv[1]

    if processor == "py":
        input_img, output_img = sys.argv[2:4]
        process_img_python(input_img, output_img)
    elif processor == "cpp":
        input_bin, output_bin = sys.argv[2:4]
        process_img_cpp(input_bin, output_bin)
    else:
        print(f'UNKNOWN PROCESSOR TYPE: {processor}')


if __name__ == '__main__':
    with timing("Total python time: {} sec"):
        main()
