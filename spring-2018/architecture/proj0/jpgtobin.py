from PIL import Image
import numpy as np
import time
import sys
import multiprocessing


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

    img_np.astype('uint8').tofile(output_path)


if __name__ == '__main__':
    input_img, output_img = sys.argv[1], sys.argv[2]
    process_img_python(input_img, output_img)
