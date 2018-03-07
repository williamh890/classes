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

from processor import open_image, save_image, timing
import sys
import numpy as np

ENDIAN = 'little'


def main():
    conversion = sys.argv[1]

    if conversion == 'imgtobin':
        input_img, output_bin = sys.argv[2:4]
        write_img_to_bin_file(input_img, output_bin)
    elif conversion == 'bintoimg':
        input_bin, output_img = sys.argv[2:4]
        save_bin_to_image(input_bin, output_img)
    else:
        print(f"UNKNOWN CONVERSION: {conversion}, must be 'imgtobin' or 'bintoimg'")


def write_img_to_bin_file(input_img, output_bin):
    img_np = open_image(input_img)

    write_pixel_data(img_np, output_bin)


def save_bin_to_image(binary, output_image_path):
    pixels = read_bin_pixel_data(binary)

    save_image(pixels, output_image_path)


def write_pixel_data(data, output_bin):
    height, width = [
        d.to_bytes(4, byteorder=ENDIAN, signed=False) for d in data.shape[:-1]
    ]
    print(data.shape)

    flat_data = data.flatten()
    int_byte_data = [
        int(i).to_bytes(4, byteorder=ENDIAN, signed=False) for i in flat_data
    ]

    print(f"writing image binary data to -> {output_bin}")
    with open(output_bin, "wb") as f:
        f.write(width)
        f.write(height)
        [f.write(i) for i in int_byte_data]


def read_bin_pixel_data(file_path):
    pixels = []

    print(f"reading image data from -> {file_path}")
    with open(file_path, "rb") as f:
        width = int.from_bytes(f.read(4), byteorder=ENDIAN, signed=False)
        height = int.from_bytes(f.read(4), byteorder=ENDIAN, signed=False)

        byte = f.read(4)
        while byte != b"":
            num = int.from_bytes(byte, byteorder=ENDIAN, signed=False)
            pixels.append(num)
            byte = f.read(4)

    pixels = np.array(pixels).reshape(height, width, 3)

    return pixels


if __name__ == "__main__":
    with timing('Time to convert: {}'):
        main()
