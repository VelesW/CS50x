def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n >= 1 and n <= 8:
                return n
        except ValueError:
            print("Not an integer")


def main():
    gap_size = 2
    height = get_height()
    for i in range(height):
        # print spaces
        for j in range(height - i - 1):
            print(" ", end="")

        # print left hashes
        for j in range(height - i, height + 1):
            print("#", end="")

        # print gap
        for j in range(gap_size):
            print(" ", end="")

        # print right hashes
        for j in range(i + 1):
            print("#", end="")

        print()


main()
