'''
    William Horn
    CS 441 - System Architecture
    Proj0 Rough Draft

    Here is some python 3.6 code to do some dummy image processing. This
    is meant to be the baseline for the quickest thing I could write. I
    plan to write the image to a bin file for easy reading/writing in c++
    where further parallel testing will be done.

    Called from the command line:

        python3 jpgtobin.py <input-img-path> <output-img-path>

    The file name is a big lie at the moment. You might have to install numpy if its
    not installed

    The json files are where I'm storing the some metadata for the images
    along with the dev time/and the runtime for each image. The dev time doesn't
    take into account refactoring time.
'''

from PIL import Image
import numpy as np
import time
import sys
import os
import multiprocessing

ENDIAN = 'little'


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
        if x % 100 == 0:
            print(f"{(x / width) * 100:2.1f} %")
        process_row(x, colors, height, width)


def process_row(x, colors, height, width):
    for y in range(height):
        colors[x][y][0] = mutate(colors[x][y][2], x, width, 100)
        colors[x][y][1] = mutate(colors[x][y][1], x, width, 50)
        colors[x][y][2] = mutate(colors[x][y][0], x, width, -50)


def process_img_python(input_img, output_img):
    colors = open_image(input_img)

    shape = colors.shape
    width, height, num_channel = shape
    print(shape, colors.dtype)

    start = time.time()
    process_img(colors, width, height)
    end = time.time()

    print(end - start)

    save_image(colors, output_img)


def write_img_to_bin_file(input_path, output_path):
    img_np = open_image(input_path)

    write_pixel_data(img_np, output_path)


def write_pixel_data(data, output_path):
    height, width = [
        d.to_bytes(4, byteorder=ENDIAN, signed=False) for d in data.shape[:-1]
    ]
    print(data.shape)

    flat_data = data.flatten()
    int_byte_data = [
        int(i).to_bytes(4, byteorder=ENDIAN, signed=False) for i in flat_data
    ]

    print(f"writing to {output_path}")
    with open(output_path, "wb") as f:
        f.write(width)
        f.write(height)
        [f.write(i) for i in int_byte_data]


def read_bin_pixel_data(file_path):
    pixels = []

    with open(file_path, "rb") as f:
        width = int.from_bytes(f.read(4), byteorder=ENDIAN, signed=False)
        height = int.from_bytes(f.read(4), byteorder=ENDIAN, signed=False)

        byte = f.read(4)
        while byte != b"":
            num = int.from_bytes(byte, byteorder=ENDIAN, signed=False)
            pixels.append(num)
            byte = f.read(4)

    pixels = np.array(pixels).reshape(height, width, 3)
    print(pixels.shape)
    return pixels


dummy_data = np.array([
    [[1, 2, 3], [4, 5, 6]],
    [[3, 2, 3], [4, 5, 4]]
])


def process_img_cpp(input_img, output_img):
    write_img_to_bin_file(input_img, output_img)

    os.system(f"./img-processor.out {output_img}")

    pixels = read_bin_pixel_data(output_img)
    save_image(pixels, 'test-cpp.jpg')


if __name__ == '__main__':
    input_img, output_img = sys.argv[1:3]
    process_img_cpp(input_img, output_img)
    #process_img_python(input_img, output_img)
