import os
import sys
FIFO_PATH = "/tmp/fake_spi"
MODULE_COUNT = 4
DISPLAY_WIDTH = MODULE_COUNT*8
DISPLAY_HEIGHT = 8
BYTES_PER_UPDATE = MODULE_COUNT * 2
display = [[0 for _ in range(DISPLAY_WIDTH)] for _ in range(DISPLAY_HEIGHT)]
module_data = [[0]*8 for _ in range(MODULE_COUNT)]

def reverse_bits(byte):
    return int('{:08b}'.format(byte)[::-1], 2)

def update_display():
    for row in range(8):
        for m in range(MODULE_COUNT):
            byte = reverse_bits(module_data[m][row])  # reverse bits
            for bit in range(8):
                col = m * 8 + bit
                display[7-row][col] = (byte >> (7 - bit)) & 1

def print_display():
    sys.stdout.write("\x1b[H\x1b[2J")  # Clear screen
    for row in range(DISPLAY_HEIGHT):
        line = ""
        for col in range(DISPLAY_WIDTH):
            # if col > 0 and col % 8 == 0:
            #     line += " "  # space between modules
            line += "█" if display[row][col] else " "
        print(line)
    print("=" * (DISPLAY_WIDTH + MODULE_COUNT - 1))

def main():
    if not os.path.exists(FIFO_PATH):
        os.mkfifo(FIFO_PATH)
    print(f"Listening on FIFO {FIFO_PATH}...")
    with open(FIFO_PATH, "rb") as fifo:
        while True:
            packet = fifo.read(BYTES_PER_UPDATE)
            if len(packet) != BYTES_PER_UPDATE:
                continue
            for i in range(MODULE_COUNT):
                addr = packet[i * 2]
                data = packet[i * 2 + 1]
                if 1 <= addr <= 8:
                    module_index = MODULE_COUNT - 1 - i
                    module_data[module_index][addr - 1] = data
            update_display()
            print_display()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nExiting.")
