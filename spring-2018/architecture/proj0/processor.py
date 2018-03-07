
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


def clamp(x):
    return max(0, min(x, 255))


def mutate(channel, height, max_height, diff):
    return int(clamp(channel + diff * (height / max_height)))


def save_image(arr, path):
    result = Image.fromarray(arr.astype(np.uint8))
    result.save(path)


def open_image(image_path):
    jpgfile = Image.open(image_path)
    pic_colors = np.array(jpgfile)

    return pic_colors


def process_img(colors, width, height):
    for x in range(width):
        # if x % 100 == 0:
            # print(f"{(x / width) * 100:2.1f} %")
        for y in range(height):
            colors[x][y][0] = mutate(colors[x][y][2], x, width, 100)
            colors[x][y][1] = mutate(colors[x][y][1], x, width, 50)
            colors[x][y][2] = mutate(colors[x][y][0], x, width, -50)


def process_img_python(input_img, output_img):
    print ("Processing image python")
    colors = open_image(input_img)

    shape = colors.shape
    width, height, num_channel = shape
    print(shape, colors.dtype)

    start = time.time()
    with timing('Processing time: {} sec'):
        process_img(colors, width, height)
    end = time.time()

    save_image(colors, output_img)


def process_img_cpp(input_bin, output_bin):
    print("Processing image c++")

    with timing('processing time: {} sec'):
        os.system(f'./processor-cpp/img-processor.out {input_bin} {output_bin}')


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
