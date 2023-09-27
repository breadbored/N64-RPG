from PIL import Image
from itertools import product
import os

def tile(filename, dir_in, dir_out, d):
    name, ext = os.path.splitext(filename)
    img = Image.open(os.path.join(dir_in, filename))
    w, h = img.size
    empty_space = h % (d * 8)
    
    grid = product(range(0, h, d * 8), range(0, w, d * 8))
    for i, j in grid:
        box = (j, i, j+(d*8), i+(d*8))
        out = os.path.join(dir_out, f'{name}_{int(i / 256)}{ext}')
        img.crop(box).save(out)

tile("tileset.png", "assets", "tileset_generated_parts", 32)