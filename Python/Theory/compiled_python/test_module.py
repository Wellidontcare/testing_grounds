import numpy as np

def print_three_random_num():
    print(np.random.randint(0, 25, size=3))


if __name__ == "__main__":
    print_three_random_num()
