#!/usr/bin/env python3

tile_map = [0, 0x00, 0x02, 0x04, 0x06, 0x08,
               0x20, 0x22, 0x24, 0x26, 0x28,
               0x40, 0x42, 0x44, 0x46, 0x48]

def main():
    values = []
    with open('level.txt') as file:
        for line in file:
            items = line.strip().split(',')
            row = []
            for c in items:
                if not c:
                    continue
                row.append(tile_map[int(c)])
            values = row + values

    with open('level.bin', 'wb+') as file:
        file.write(bytearray(values))

if __name__ == '__main__':
    main()

# eof
